
#include "../inventory/inventory.h"
#include <stdio.h>
#include <stdlib.h>

InventoryItem *read_inventory_item() {
  char *name = malloc(MAX_NAME_LENGTH);
  printf("\nName: ");
  scanf(" %99[^\n]", name);

  double price;
  printf("\nPrice: ");
  scanf("%lf", &price);

  int quantity;
  printf("\nQuantity: ");
  scanf("%d", &quantity);

  int reorder_level;
  printf("\nReorder level: ");
  scanf("%d", &reorder_level);

  int supplier_id;
  printf("\nSupplier ID: ");
  scanf("%d", &supplier_id);

  struct InventoryItem *item =
      new_inventory_item(0, name, price, quantity, reorder_level, supplier_id);

  return item;
}
