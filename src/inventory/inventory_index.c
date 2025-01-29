#include "../lib/lib.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOWED_MATCH_ERRS_RATIO 4
#define MAX_FOUND_ITEMS 16

int comp_name(InventoryItem *item, char *name) {

  if (item == NULL || name == NULL) {
    return 0;
  }

  int item_len = strlen(item->name);
  int name_len = strlen(name);
  int min_len = name_len < item_len ? name_len : item_len;
  int max_allowable_errors = min_len / ALLOWED_MATCH_ERRS_RATIO;
  int errors = 0;

  for (int i = 0; i < min_len; i++) {
    if (item->name[i] != name[i]) {
      errors++;
    }
    if (errors > max_allowable_errors) {
      return 0;
    }
  }

  if (name_len <= item_len) {
    return 1;
  }

  return 0;
}

int update_metadata(InventoryIndex *index) {
  char *data_path = malloc(strlen(config.data_path) + strlen("/metadata") + 1);
  strcpy(data_path, config.data_path);
  char *path = strcat(data_path, "/metadata");

  if (write_metadata(path, index) != 0) {
    LOG_ERR("Error writing updated metadata");
    return -1;
  };
  return 0;
}

InventoryIndex *init_inventory_index() {
  InventoryIndex *index = (InventoryIndex *)malloc(sizeof(InventoryIndex));
  index->head = NULL;
  index->last_id = 0;
  index->size = 0;
  return index;
}

int free_inventory_index(InventoryIndex *index) {
  if (index == NULL) {
    LOG(2, "Tried to free NULL inventory index");
    return -1;
  }

  InventoryNode *current = index->head;
  delete_inventory(current);
  if (current != NULL) {
    LOG_ERR("Error freeing inventory node holding id = %d", current->data.id);
    return -1;
  }

  free(index);
  return 0;
}

int append_item(InventoryIndex *index, InventoryItem item) {
  if (item.id >= 0 && (!check_id_availability(index->head, item.id))) {
    LOG_ERR("tried to add item with id = %d, but it already exists", item.id);
    return -1;
  }

  InventoryNode *new_node = (InventoryNode *)malloc(sizeof(InventoryNode));
  if (new_node == NULL) {
    LOG_ERR("Error allocating memory for new node");
    return -1;
  }

  new_node->data = item;
  new_node->next = NULL;

  if (index->head == NULL) {
    index->head = new_node;
  } else {
    InventoryNode *current = index->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
  index->size++;
  index->last_id = item.id;
  update_metadata(index);
  write_item(&item);
  return 0;
};

int del_item(InventoryIndex *index, int id) {
  LOG(0, "Deleting item with id = %d", id);
  InventoryNode *node = find_item_by_id(index, id);
  if (node == NULL) {
    LOG_ERR("Item with id = %d not found", id);
    return -1;
  }
  int res = delete_inventory_item_by_id(index->head, id);
  if (res == -1) {
    LOG_ERR("Error deleting item with id = %d", id);
    return -1;
  }

  index->size--;
  if (update_metadata(index) != 0) {
    LOG_ERR("Error updating metadata");
    return -1;
  }

  char *data_path = malloc(strlen(config.data_path) + strlen("/metadata") + 1);
  strcpy(data_path, config.data_path);
  char *filepath = strcat(data_path, "/");
  char id_str[32];
  sprintf(id_str, "%d", id);
  strcat(filepath, id_str);
  strcat(filepath, ".json");

  if (!delete_file(filepath)) {
    LOG_ERR("Error deleting file %s", filepath);
  };
  return 0;
}

int update_item(InventoryIndex *index, int id, InventoryItem item) {
  if (index == NULL || index->head == NULL) {
    return -1;
  }

  InventoryNode *current = index->head;
  while (current != NULL) {
    if (current->data.id == id) {
      item.id = id;
      current->data = item;
      write_item(&item);
      return 0;
    }
    current = current->next;
  }

  return -1;
}

InventoryNode *find_item_by_id(InventoryIndex *index, int id) {
  InventoryNode *current = index->head;
  int *found = malloc(sizeof(int));

  while (current != NULL) {
    if (current->data.id == id) {
      *found = 1;
      return current;
    }
    current = current->next;
  }
  return NULL;
}

InventoryNode **search_items_by_name(InventoryIndex *index, char *name) {
  InventoryNode **found = malloc(sizeof(InventoryNode *) * MAX_FOUND_ITEMS);
  InventoryNode *current = index->head;
  int found_count = 0;

  while (current != NULL) {
    if (comp_name(&(current->data), name)) {
      found[found_count] = current;
      found_count++;
      if (found_count == MAX_FOUND_ITEMS) {
        break;
      }
    }
    current = current->next;
  }
  return found;
}

// TODO
InventoryNode **search_items_by_supplier_id(InventoryIndex *index,
                                            int supplier_id) {
  LOG_ERR("unimplemented");
  return NULL;
}
