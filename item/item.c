#include "item.h"
#include "../lib/errors.h"
#include <stdlib.h>
#include <string.h>

struct Item *createItem(int ID, int quantity, float price, char *name,
                        char *description) {
  if (ID < 0 || quantity < 0 || price < 0.0 || name == NULL ||
      description == NULL) {
    struct Error *error = createError("Bad arguemnts provided");
    LogError(error);
    return NULL;
  }

  struct Item *item = malloc(sizeof(struct Item));
  if (item == NULL) {
    struct Error *error =
        createError("Could not allocate memory for item during it's creation");
    LogError(error);
    return NULL;
  }

  item->ID = ID;
  item->quantity = quantity;
  item->price = price;

  item->name = strdup(name);
  if (item->name == NULL) {
    free(item);
    struct Error *error = createError(
        "Could not allocate memory for item name during it's creation");
    LogError(error);
    return NULL;
  }

  item->description = strdup(description);
  if (item->description == NULL) {
    struct Error *error = createError(
        "Could not allocate memory for item description during it's creation");
    LogError(error);
    free(item->name);
    free(item);
    return NULL;
  }

  return item;
}
char *deleteItem(struct Item *item);
