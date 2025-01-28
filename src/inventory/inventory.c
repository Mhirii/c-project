#include "inventory.h"
#include "../lib/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InventoryNode *new_inventory() {
  InventoryNode *node = (InventoryNode *)malloc(sizeof(InventoryNode));

  if (node == NULL) {
    LOG_ERR("Error allocating memory for new node");
    return NULL;
  }
  node->next = NULL;
  return node;
}

void delete_inventory(InventoryNode *head) {
  InventoryNode *current = head;
  InventoryNode *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

InventoryNode *inventory_append(InventoryNode *head, InventoryItem item) {
  InventoryNode *new_node = (InventoryNode *)malloc(sizeof(InventoryNode));
  if (new_node == NULL) {
    LOG_ERR("Error allocating memory for new node");
    return NULL;
  }

  new_node->data = item;
  new_node->next = NULL;

  if (head == NULL) {
    return new_node;
  }

  InventoryNode *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = new_node;

  return head;
}

InventoryItem *new_inventory_item(int id, char *name, double price,
                                  int quantity, int reorder_level,
                                  int supplier_id) {
  InventoryItem *item = (InventoryItem *)malloc(sizeof(InventoryItem));

  if (item == NULL) {
    return NULL;
    LOG_ERR("Error allocating memory for new node");
  }

  if (id <= 0) {
    LOG_ERR("id is not valid");
    free(item);
    return NULL;
  }
  item->id = id;

  if (name == NULL || strlen(name) > MAX_NAME_LENGTH) {

    LOG_ERR("name is not valid");
    free(item);
    return NULL;
  }
  item->name = name;

  if (price <= 0) {

    LOG_ERR("price is not valid");
    free(item);
    return NULL;
  }
  if (quantity < 0) {
    LOG_ERR("quantity cannot be negative");
    free(item);
    return NULL;
  }
  item->quantity = quantity;

  if (reorder_level < 0) {
    LOG_ERR("reorder level cannot be negative");
    free(item);
    return NULL;
  }
  item->reorder_level = reorder_level;

  if (supplier_id <= 0) {
    LOG_ERR("supplier id is not valid");
    free(item);
    return NULL;
  }
  item->supplier_id = supplier_id;

  item->price = price;
  item->last_updated = time(NULL);
  return item;
}

void delete_inventory_item(InventoryItem *item) {
  free(item->name);
  free(item);
};

InventoryNode *inventory_update(InventoryNode *head, int id,
                                InventoryItem new_data);

InventoryNode *inventory_delete(InventoryNode *head, int id);

InventoryItem *inventory_find(InventoryNode *head, int id);

void inventory_display_all(InventoryNode *head, int minimal) {
  if (head == NULL) {
    LOG_ERR("Cannot display empty inventory");
    return;
  }

  InventoryNode *current = head;
  while (current != NULL) {
    if (minimal == 0) {
      inventory_display_item(&current->data);
    } else {
      printf("%d: %s\n", current->data.id, current->data.name);
    }
    current = current->next;
  }
}

void inventory_display_item(InventoryItem *item) {
  if (item == NULL) {
    LOG_ERR("Cannot display NULL item");
    return;
  }

  printf("ID:            %d\n", item->id);
  printf("Name:          %s\n", item->name);
  printf("Price:         %.2f\n", item->price);
  printf("Quantity:      %d\n", item->quantity);
  printf("Reorder Level: %d\n", item->reorder_level);
  printf("Supplier ID:   %d\n", item->supplier_id);
  printf("Last Updated:  %ld\n", item->last_updated);
}

void check_low_stock(InventoryNode *head, Config *config);

void update_stock_quantity(InventoryNode *head, int id, int quantity_change);

int check_id_availability(InventoryNode *head, int id) {
  InventoryNode *current = head;
  while (current != NULL) {
    if (current->data.id == id) {
      return 0;
    }
    current = current->next;
  }
  return 1;
}

InventoryNode *inventory_from_json(InventoryNode *head, char *json) {
  LOG_ERR("Not implemented");
  return NULL;
}
