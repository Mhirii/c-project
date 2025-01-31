#include "inventory.h"
#include "../lib/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    head = new_node;
    return head;
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
int delete_inventory_item_by_id(InventoryNode *head, int id) {
  int found = -1;
  InventoryNode *current = head;
  InventoryNode *previous = NULL;
  while (current != NULL) {
    if (current->data.id == id) {
      if (previous == NULL) {
        head = current->next;
      } else {
        previous->next = current->next;
      }
      delete_inventory_item(&current->data);
      found = 0;
      break;
    }
    previous = current;
    current = current->next;
  }
  return found;
}

void inventory_display_item_minimal(InventoryItem item) {
  int stock_is_low = item.quantity < config.low_stock_threshold;
  printf("\n╭─────────────────╮\n");
  printf("\033[1m%s #%d\033[0m: %s%s\033[0m \n"
         "   💰 $%.2f\033[0m \n"
         "   📦 Qty: %d\033[0m \n"
         "   ⚠️  Min: %d\033[0m \n"
         "   🏢 Sup: %d\033[0m\n",
         stock_is_low ? "⚠️" : "✨", item.id, stock_is_low ? "\033[1;31m" : "",
         item.name, item.price, item.quantity, item.reorder_level,
         item.supplier_id);
  printf("╰─────────────────╯\n");
}

void inventory_display_item(InventoryItem item) {
  int stock_is_low = item.quantity < config.low_stock_threshold;
  printf("\n╭────────────────────────────────────╮\n");
  printf("\033[1m%s #%d\033[0m: %s%s\033[0m \n"
         "   💰 Price: \033[1;33m$%.2f\033[0m \n"
         "   📦 Quantity: \033[1;32m%d\033[0m \n"
         "   ⚠️  Reorder Level: \033[1;31m%d\033[0m \n"
         "   🏢 Supplier ID: \033[1;35m%d\033[0m\n",
         stock_is_low ? "⚠️" : "✨", item.id, stock_is_low ? "\033[1;31m" : "",
         item.name, item.price, item.quantity, item.reorder_level,
         item.supplier_id);
  printf("╰────────────────────────────────────╯\n");
}

void inventory_display_all(InventoryNode *head, int minimal) {
  if (head == NULL) {
    LOG_ERR("Cannot display empty inventory");
    return;
  }

  InventoryNode *current = head;
  while (current != NULL) {
    if (minimal == 0) {
      printf("\n---------------- ----------------\n\n");
      inventory_display_item(current->data);
      if (current->next == NULL)
        printf("\n---------------- ----------------\n\n");

    } else {
      inventory_display_item_minimal(current->data);
    }
    current = current->next;
  }
}

void inventory_display_item_boring(InventoryItem *item) {
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

/**
 * @brief Checks if a given ID is already in use in the inventory
 *
 * @param head Pointer to the head of the inventory linked list
 * @param id ID to check for availability
 * @return int Returns 1 if ID is available (not found), 0 if ID already exists
 */
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

InventoryNode get_last_node(InventoryNode *head) {
  InventoryNode *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  return *current;
}

InventoryNode *inventory_from_json(InventoryNode *head, char *json) {
  LOG_ERR("Not implemented");
  return NULL;
}
