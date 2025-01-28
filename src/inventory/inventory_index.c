#include "../lib/lib.h"
#include "inventory.h"
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
  inventory_append(index->head, item);
  index->last_id = item.id;
  index->size++;
  return 0;
};

int del_item(InventoryIndex *index, int id) {
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
  return 0;
}

int update_item(InventoryIndex *index, int id, InventoryItem item);

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

InventoryNode **search_items_by_supplier_id(InventoryIndex *index,
                                            int supplier_id);
