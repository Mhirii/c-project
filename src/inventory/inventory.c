#include "inventory.h"
#include "../lib/errors.h"
#include "../lib/terminal.h"
#include <stdio.h>
#include <stdlib.h>

struct Inventory *create_inventory(int ID) {
  struct Inventory *inventory = malloc(sizeof(struct Inventory));
  if (inventory == NULL) {
    struct Error *error = create_error(
        "Could not allocate memory for inventory during it's creation");
    log_error(error);
    return NULL;
  }

  inventory->ID = ID;
  inventory->items = NULL;
  inventory->size = 0;
  inventory->lastID = 0;

  return inventory;
}

char *delete_inventory(struct Inventory *inventory) {
  if (inventory == NULL) {
    struct Error *error =
        create_error("Could not delete inventory because it was NULL");
    if (error != NULL) {
      log_error(error);
      free(error);
    }
    return NULL;
  }

  struct Item *item = inventory->items;
  struct Item *next = NULL;
  while (item != NULL) {
    next = item->next;
    if (item != NULL) {
      delete_item(item);
    }
    item = next;
  }

  inventory->items = NULL;
  inventory->size = 0;
  inventory->lastID = 0;
  free(inventory);
  return NULL;
}

struct Item *add_item(struct Inventory *inventory, int quantity, float price,
                      char *name, char *description) {
  if (quantity < 0 || price < 0.0 || name == NULL || description == NULL) {
    struct Error *error = create_error("Bad arguemnts provided");
    log_error(error);
    return NULL;
  }

  int ID = inventory->lastID + 1;
  struct Item *item = create_item(ID, quantity, price, name, description);

  if (inventory->size == 0) {
    inventory->items = item;
    inventory->size = 1;
    inventory->lastID = item->ID;
    return item;
  }

  struct Item *lastItem = inventory->items;
  while (lastItem->next != NULL) {
    lastItem = lastItem->next;
  }
  lastItem->next = item;
  inventory->size++;
  inventory->lastID = item->ID;

  return item;
}

struct Item *get_item_by_id(struct Inventory *inventory, int ID) {
  if (inventory == NULL) {
    struct Error *error =
        create_error("Could not get item by ID because inventory was NULL");
    log_error(error);
    return NULL;
  }

  struct Item *item = inventory->items;
  while (item != NULL) {
    if (item->ID == ID) {
      return item;
    }
    item = item->next;
  }

  struct Error *error =
      create_error("Could not get item by ID because it was not found");
  log_error(error);
  return NULL;
}

void remove_item(struct Inventory *inventory, int ID) {
  if (inventory == NULL) {
    struct Error *error = create_error(
        "Could not remove item from inventory because inventory was NULL");
    log_error(error);
    return;
  }

  struct Item *item = inventory->items;
  struct Item *previous = NULL;
  while (item != NULL) {
    if (item->ID == ID) {
      if (previous == NULL) {
        inventory->items = item->next;
      } else {
        previous->next = item->next;
      }
      inventory->size--;
      return;
    }
    previous = item;
    item = item->next;
  }

  struct Error *error = create_error(
      "Could not remove item from inventory because it was not found");
  log_error(error);
}

void inventory_menu(struct Inventory *inventory) {
  int choice = 0;
  while (choice != 0) {
    printf("Item Management\n");
    clear_screen();
    move_cursor(1, 1);

    printf("Please enter your choice:\n");
    print_option(1, "Show Items");
    print_option(2, "Add Item");
    print_option(3, "Find Item");
    printf("%s\n", format_option(0, "exit", RED));
    choice = getch() - '0';
    switch (choice) {
    case 1:
      printf("Show items");
      break;
    case 2:
      printf("Show Items");
      break;
    case 3:
      printf("Preferences\n");
      break;
    case 0:
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
    print_bottom_message("Press any key to continue...");
    getch();
  }
}
