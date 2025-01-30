
#include "../inventory/inventory.h"
#include "../supplier/supplier.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 128

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

Supplier *read_supplier() {
  char *first_name = malloc(MAX_STRING_LENGTH);
  char *last_name = malloc(MAX_STRING_LENGTH);
  char *email = malloc(MAX_STRING_LENGTH);
  char *phone = malloc(MAX_STRING_LENGTH);

  printf("\nFirst name: ");
  scanf(" %99[^\n]", first_name);

  printf("\nLast name: ");
  scanf(" %99[^\n]", last_name);

  printf("\nEmail: ");
  scanf(" %99[^\n]", email);

  printf("\nPhone: ");
  scanf(" %99[^\n]", phone);

  Supplier *supp = new_supplier(0, first_name, last_name, email, phone);

  return supp;
}
