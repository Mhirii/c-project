#ifndef INVENTORY_INDEX_IO_C
#define INVENTORY_INDEX_IO_C

#include "../json/json.h"
#include "../lib/lib.h"
#include "inventory.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHK_ERR(condition, message)                                            \
  if (condition) {                                                             \
    LOG_ERR(message);                                                          \
    return -1;                                                                 \
  }

InventoryIndex *read_inventory_index() {
  // TODO: check if path is valid and has the needed files.
  char *path = malloc(strlen(config.data_path) + strlen("/inventory") + 1);
  path = strcpy(path, config.data_path);
  path = strcat(path, "/inventory");

  InventoryIndex *index = init_inventory_index();

  char *metadata = malloc(strlen(path) + strlen("/metadata") + 1);
  sprintf(metadata, "%s/metadata", path);

  int res = parse_metadata(metadata, index);
  if (res == -1) {
    LOG_ERR("Error occurred while parsing metadata file");
    free_inventory_index(index);
    free(path);
    free(metadata);
    return NULL;
  }

  res = read_items(path, index);
  if (res == -1) {
    LOG_ERR("Error reading items");
    free_inventory_index(index);
    free(metadata);
    free(path);
    free(index);
    return NULL;
  }

  LOG(1, "Inventory index read");
  return index;
}

char *parse_metadata_line(char *line) {
  char *key = strtok(line, "=");
  if (!key) {
    LOG_ERR("Failed to parse key");
    return NULL;
  }
  char *value = strtok(NULL, "\n");
  return value;
}

int parse_metadata(char *path, InventoryIndex *index) {
  char *buffer;
  long file_size;
  if (!read_file(path, &buffer, &file_size)) {
    LOG_ERR("Error occurred while opening metadata file");
    return -1;
  }

  char *line = strtok(buffer, "\n");
  while (line != NULL) {
    char *key = parse_metadata_line(line);
    if (strcmp(key, "last_id") == 0) {
      int id = atoi(line);
      index->last_id = id;
    } else if (strcmp(key, "size") == 0) {
      int size = atoi(line);
      index->size = size;
    }
    line = strtok(NULL, "\n");
  }
  free((void *)buffer);
  LOG(1, "Metadata file read");
  return 0;
}

int write_metadata(char *path, InventoryIndex *index) {
  char *buffer = malloc(MAX_NAME_LENGTH);
  sprintf(buffer, "last_id=%d\nsize=%d\n", index->last_id, index->size);
  if (!write_file(path, buffer)) {
    LOG_ERR("Error occurred while writing metadata file");
    return -1;
  }
  free(buffer);
  LOG(1, "Metadata file written");
  return 0;
}

/**
 * @brief Lists all JSON files in a directory
 * @param path The dir path
 * @param files arr that stores paths of JSON files
 * @return -1 on error or Number of JSON files found.
 */
int ls_json_files(const char *path, char **files) {
  DIR *dir;
  struct dirent *entry;
  int i = 0;

  dir = opendir(path);
  if (dir == NULL) {
    LOG_ERR("Unable to open directory at %s", path);
    return -1;
  }

  while ((entry = readdir(dir)) != NULL) {
    const char *ext = strrchr(entry->d_name, '.');
    if (ext && strcmp(ext, ".json") == 0) {
      if (files == NULL) {
        LOG_ERR("files array is NULL");
        continue;
      }

      char *full_path = malloc(strlen(path) + strlen(entry->d_name) +
                               2); // +2 for '/' and null terminator
      if (full_path == NULL) {
        LOG_ERR("Failed to allocate memory for full path");
        continue;
      }

      if (sprintf(full_path, "%s/%s", path, entry->d_name) < 0) {
        LOG_ERR("Error occurred while formatting full_path, name = %s",
                entry->d_name);
        free(full_path);
      } else {
        files[i] = full_path;
        i++;
      };
    }
  }

  closedir(dir);

  return i;
}

int read_items(char *path, InventoryIndex *index) {
  char **json_files = malloc(32 * sizeof(char *));
  int files_count = ls_json_files(path, json_files);
  for (int i = 0; i < files_count; i++) {

    InventoryItem item;
    if (read_item(json_files[i], &item) == -1) {
      LOG_ERR("Failed to read item file %s", json_files[i]);
      continue;
    }
    if (append_item(index, item) != 0) {
      LOG_ERR("Failed to append item to index, file is %s", json_files[i]);
      if (item.name)
        free(item.name);
      continue;
    }
    free(json_files[i]);
  }
  free(json_files);
  return 0;
}

int write_items(char *path, InventoryIndex *index) {
  InventoryNode *head = index->head;
  while (head != NULL) {
    if (!write_item(&head->data)) {
      LOG_ERR("Failed to write item file %s", head->data.name);
      return -1;
    };
    head = head->next;
  }
  return 0;
}

int read_item(char *path, InventoryItem *item) {
  char *buffer = NULL;
  long file_size;
  if (!read_file(path, &buffer, &file_size)) {
    LOG_ERR("Error occurred while opening file %s", path);
    return -1;
  }
  const char *ptr = buffer;

  CHK_ERR((!parse_json_object(&ptr)), "Invalid JSON object")

  while (*ptr != '}') {
    char *key = NULL;
    CHK_ERR((!parse_json_key(&ptr, &key)), "Failed to parse key");

    CHK_ERR((!parse_json_key_value_separator(&ptr)),
            "Failed to parse key-value separator");

    if (strcmp(key, "id") == 0) {
      CHK_ERR((!parse_json_number(&ptr, &(item->id))), "Failed to parse id");

    } else if (strcmp(key, "name") == 0) {

      CHK_ERR((!parse_json_string(&ptr, &(item->name))),
              "Failed to parse name");

    } else if (strcmp(key, "price") == 0) {
      float price;
      CHK_ERR((!parse_json_float(&ptr, &price)), "Failed to parse price");

      item->price = (double)price;
    } else if (strcmp(key, "quantity") == 0) {
      CHK_ERR((!parse_json_number(&ptr, &item->quantity)),
              "Failed to parse quantity");

    } else if (strcmp(key, "reorder_level") == 0) {
      CHK_ERR((!parse_json_number(&ptr, &item->reorder_level)),
              "Failed to parse reorder_level");

    } else if (strcmp(key, "supplier_id") == 0) {
      CHK_ERR((!parse_json_number(&ptr, &item->supplier_id)),
              "Failed to parse supplier_id");

    } else if (strcmp(key, "last_updated") == 0) {
      CHK_ERR((!parse_json_number(&ptr, (int *)&item->last_updated)),
              "Failed to parse last_updated");

    } else {
      LOG_ERR("Unknown key: %s", key);
      return -1;
    }

    free(key);

    skip_whitespace(&ptr);
    if (*ptr != '}') {

      CHK_ERR((!parse_json_value_separator(&ptr)),
              "Failed to parse value separator");
    }
  }

  CHK_ERR((!parse_json_object_end(&ptr)), "Failed to parse object end");

  return 0;
}

char *serialize_inventory_item(InventoryItem item) {
  char *json = NULL;

  // 2 bytes bc 1 lel '{' w 1 lel null
  json = malloc(2);
  strcpy(json, "{");

  append_json_number_pair(&json, "id", item.id);
  append_json_string_pair(&json, "name", item.name);
  append_json_float_pair(&json, "price", item.price);
  append_json_number_pair(&json, "quantity", item.quantity);
  append_json_number_pair(&json, "reorder_level", item.reorder_level);
  append_json_number_pair(&json, "supplier_id", item.supplier_id);
  append_json_number_pair(&json, "last_updated", (int)item.last_updated);

  // +2 5ater kima 9blia
  json = realloc(json, strlen(json) + 2);
  strcat(json, "}");

  return json;
}

int write_item(InventoryItem *item) {

  char filename[64];
  if (sprintf(filename, "%d.json", item->id) < 0) {
    LOG_ERR("Error while formatting filename");
    return -1;
  }

  char *path = malloc(strlen(config.data_path) + strlen("/inventory") +
                      strlen(filename) + 2);
  if (!sprintf(path, "%s/inventory/%s", config.data_path, filename)) {
    LOG_ERR("Error while path to save item");
    return -1;
  }

  char *buffer = serialize_inventory_item(*item);
  if (!buffer) {
    LOG_ERR("Failed to serialize item");
    free(path);
    return -1;
  }

  int result = write_file(path, buffer) ? 0 : -1;
  free(buffer);

  if (result == -1) {
    free(path);
    LOG_ERR("Failed to write item file");
  }
  return result;
}

#endif
