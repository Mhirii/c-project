#include "../json/json.h"
#include "../lib/lib.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

InventoryItem parse_inventory_item(const char **json, int *isErr) {
  InventoryItem item = {0};

  CHECK_ERROR_RETURN((!parse_json_object(json)), "Invalid JSON object\n",
                     InventoryItem);

  while (**json != '}') {
    char *key = NULL;
    CHECK_ERROR_RETURN((!parse_json_key(json, &key)), "Failed to parse key",
                       InventoryItem);

    CHECK_ERROR_RETURN((!parse_json_key_value_separator(json)),
                       "Failed to parse key-value separator", InventoryItem);

    if (strcmp(key, "id") == 0) {
      CHECK_ERROR_RETURN((!parse_json_number(json, &item.id)),
                         "Failed to parse id", InventoryItem);

    } else if (strcmp(key, "name") == 0) {

      CHECK_ERROR_RETURN((!parse_json_string(json, &item.name)),
                         "Failed to parse name", InventoryItem);

    } else if (strcmp(key, "price") == 0) {
      float price;
      CHECK_ERROR_RETURN((!parse_json_float(json, &price)),
                         "Failed to parse price", InventoryItem);

      item.price = (double)price;
    } else if (strcmp(key, "quantity") == 0) {
      CHECK_ERROR_RETURN((!parse_json_number(json, &item.quantity)),
                         "Failed to parse quantity", InventoryItem);

    } else if (strcmp(key, "reorder_level") == 0) {
      CHECK_ERROR_RETURN((!parse_json_number(json, &item.reorder_level)),
                         "Failed to parse reorder_level", InventoryItem);

    } else if (strcmp(key, "supplier_id") == 0) {
      CHECK_ERROR_RETURN((!parse_json_number(json, &item.supplier_id)),
                         "Failed to parse supplier_id", InventoryItem);

    } else if (strcmp(key, "last_updated") == 0) {
      CHECK_ERROR_RETURN((!parse_json_number(json, (int *)&item.last_updated)),
                         "Failed to parse last_updated", InventoryItem);

    } else {
      LOG_ERR("Unknown key: %s", key);
      *isErr = 1;
      return (InventoryItem){0};
    }

    free(key);

    skip_whitespace(json);
    if (**json != '}') {

      CHECK_ERROR_RETURN((!parse_json_value_separator(json)),
                         "Failed to parse value separator", InventoryItem);
    }
  }

  CHECK_ERROR_RETURN((!parse_json_object_end(json)),
                     "Failed to parse object end", InventoryItem);

  return item;
}

InventoryNode *parse_inventory_node(const char **json, int *isErr) {
  InventoryNode *node = (InventoryNode *)malloc(sizeof(InventoryNode));

  CHECK_ERROR_RETURN((!node), "Memory allocation failed", InventoryNode *);

  node->data = parse_inventory_item(json, isErr);

  printf("\n--->>>> %s\n", node->data.name);

  printf("isErr %d\n", *isErr);
  if (*isErr) {
    printf("isErr %d\n", *isErr);

    printf("\n--->>>> %s\n", "IS  ERROR");

    LOG_ERR("Error parsing inventory item");
    free(node);
    return NULL;
  }
  node->next = NULL;

  return node;
}

InventoryNode *parse_inventory_node_json(const char *path) {
  int *isErr = malloc(sizeof(int));
  *isErr = 0;

  FILE *file = fopen(path, "r");
  if (!file) {
    LOG_ERR("Failed to open file %s, Aborting parsing it", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *json = (char *)malloc(file_size + 1);
  if (!json) {
    LOG_ERR("Memory allocation failed, Aborting parsing file %s", path);
    fclose(file);
    return NULL;
  }

  fread(json, 1, file_size, file);
  json[file_size] = '\0';

  fclose(file);

  const char *json_ptr = json;

  if (!parse_json_array(&json_ptr)) {
    LOG_ERR("Failed to parse array start");
    free(json);
    return NULL;
  }

  InventoryNode *head = NULL;
  InventoryNode *tail = NULL;

  while (*json_ptr != ']') {
    InventoryNode *node = parse_inventory_node(&json_ptr, isErr);
    if (*isErr) {
      LOG_ERR("Error parsing inventory node, Aborting parsing file %s", path);
      free(json);
      while (head) {
        InventoryNode *temp = head;
        head = head->next;
        free(temp->data.name);
        free(temp);
      }
      return NULL;
    }

    if (!head) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      tail = node;
    }

    skip_whitespace(&json_ptr);
    if (*json_ptr != ']') {
      if (!parse_json_value_separator(&json_ptr)) {
        LOG_ERR("Failed to parse value separator");
        free(json);
        return NULL;
      }
    }
  }

  if (!parse_json_array_end(&json_ptr)) {
    LOG_ERR("Failed to parse array end");
    free(json);
    return NULL;
  }

  free(json);
  return head;
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

  Log(1, json);

  return json;
}

char *serialize_inventory_list(InventoryNode *head) {
  char *json = NULL;

  json = malloc(2);
  strcpy(json, "[");

  InventoryNode *current = head;
  while (current) {
    char *item_json = serialize_inventory_item(current->data);
    if (json[1] != '\0') {
      json = realloc(json, strlen(json) + strlen(item_json) + 2);
      strcat(json, ",");
    } else {
      json = realloc(json, strlen(json) + strlen(item_json) + 1);
    }
    strcat(json, item_json);
    free(item_json);

    current = current->next;
  }

  json = realloc(json, strlen(json) + 2);
  strcat(json, "]");

  return json;
}

void write_inventory_list_to_file(InventoryNode *head, const char *path) {
  char *json = serialize_inventory_list(head);
  if (!json) {
    LOG_ERR("Failed to serialize inventory list");
    return;
  }

  FILE *file = fopen(path, "w");
  if (!file) {
    LOG_ERR("Failed to open file %s for writing", path);
    free(json);
    return;
  }

  fwrite(json, 1, strlen(json), file);
  fclose(file);

  free(json);
}
