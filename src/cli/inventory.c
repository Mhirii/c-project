
#include "../inventory/inventory.h"
#include <stdio.h>
#include <stdlib.h>

struct InventoryItem *read_inventory_item(struct InventoryNode *head) {
  int id;
  int id_available = 0;
  do {
    printf("\nID: ");
    scanf("%d", &id);
    id_available = check_id_availability(head, id);
    if (!id_available) {
      printf("ID already in use. Please enter a different ID.\n");
    }
  } while (!id_available);

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
      new_inventory_item(id, name, price, quantity, reorder_level, supplier_id);

  return item;
}
