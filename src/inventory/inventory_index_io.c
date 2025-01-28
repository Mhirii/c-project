#ifndef INVENTORY_INDEX_IO_C
#define INVENTORY_INDEX_IO_C

#include "../json/json.h"
#include "../lib/lib.h"
#include "inventory.h"
#include <stdlib.h>
#include <string.h>

#define CHK_ERR(condition, message)                                            \
  if (condition) {                                                             \
    LOG_ERR(message);                                                          \
    return -1;                                                                 \
  }

InventoryIndex *read_inventory_index(char *path) {
  // TODO: check if path is valid and has the needed files.

  InventoryIndex *index = init_inventory_index();
  int res = parse_metadata(path, index);
  if (res == -1) {
    LOG_ERR("Error occurred while parsing metadata file");
    free_inventory_index(index);
    return NULL;
  }

  res = read_items(path, index);
  if (res == -1) {
    LOG_ERR("Error reading items");
    free_inventory_index(index);
    return NULL;
  }

  LOG(1, "Inventory index read");
  return index;
}

char *parse_metadata_line(char *line) {
  char *key = strtok(line, "=");
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

int read_items(char *path, InventoryIndex *index) { return -1; }
int write_items(char *path, InventoryIndex *index) { return -1; }

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

int write_item(char *path, InventoryItem *item) { return -1; }

#endif
