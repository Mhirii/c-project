#include "item.h"
#include "../lib/errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item *create_item(int ID, int quantity, float price, char *name,
                         char *description) {
  if (ID < 0 || quantity < 0 || price < 0.0 || name == NULL ||
      description == NULL) {
    struct Error *error = create_error("Bad arguemnts provided");
    log_error(error);
    return NULL;
  }

  struct Item *item = malloc(sizeof(struct Item));
  if (item == NULL) {
    struct Error *error =
        create_error("Could not allocate memory for item during it's creation");
    log_error(error);
    return NULL;
  }

  item->ID = ID;
  item->quantity = quantity;
  item->price = price;

  item->name = strdup(name);
  if (item->name == NULL) {
    free(item);
    struct Error *error = create_error(
        "Could not allocate memory for item name during it's creation");
    log_error(error);
    return NULL;
  }

  item->description = strdup(description);
  if (item->description == NULL) {
    struct Error *error = create_error(
        "Could not allocate memory for item description during it's creation");
    log_error(error);
    free(item->name);
    free(item);
    return NULL;
  }

  return item;
}
char *delete_item(struct Item *item) {
  if (item == NULL) {
    struct Error *error =
        create_error("Could not delete item because it was NULL");
    log_error(error);
    return NULL;
  } else {
    free(item->name);
    free(item->description);
    free(item);
    return NULL;
  }
}

void print_item(struct Item *item) {
  printf("Item ID: %d\n", item->ID);
  printf("Quantity: %d\n", item->quantity);
  printf("Price: %.2f\n", item->price);
  printf("Name: %s\n", item->name);
  printf("Description: %s\n", item->description);
}
