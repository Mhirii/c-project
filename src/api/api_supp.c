
#include "../cli/input.h"
#include "../lib/lib.h"
#include "../lib/macros.h"
#include "../memo/memo.h"
#include "../supplier/supplier.h"

#include "api.h"
#include <stdio.h>
#include <stdlib.h>

int add_supp(Memo *memo) {
  return append_supplier(memo->suppliers, *read_supplier());
};
int del_supp(Memo *memo) {
  printf("Enter supplier id: ");
  int id;
  if (scanf("%d", &id) != 1) {
    return -1;
  }
  return delete_supplier(memo->suppliers, id);
};

int list_supp(Memo *memo) {
  supplier_display_all(memo->suppliers->head, 0);
  PRESS_ENTER_TO_CONTINUE();
  return 0;
};

int list_supplier_items(Memo *memo) {
  printf("Enter supplier id: ");
  int search_id;
  if (scanf("%d", &search_id) != 1) {
    return -1;
  }

  InventoryNode *n = get_products_by_supplier(memo, search_id);
  if (n != NULL) {
    inventory_display_all(n, 0);
  } else {
    LOG_ERR("No products found\n");
  }
  PRESS_ENTER_TO_CONTINUE();
  return 0;
}

int update_supp(Memo *memo) {
  printf("Enter supplier id: ");
  int id;
  if (scanf("%d", &id) != 1) {
    return -1;
  }

  return update_supplier(memo->suppliers, id, *read_supplier());
};

int search_supplier_id(Memo *memo) {
  printf("Enter supplier id: ");
  int id;
  if (scanf("%d", &id) != 1) {
    return -1;
  }
  SupplierNode *s = find_supp_by_id(memo->suppliers, id);
  display_supplier(&s->supplier);
  PRESS_ENTER_TO_CONTINUE();
  return 0;
};

int search_supplier_name(Memo *memo) {
  char name[MAX_STRING_LENGTH];
  printf("Enter supplier name: ");
  if (scanf("%s", name) != 1) {
    return -1;
  }
  SupplierNode **suppliers = find_supp_by_name(memo->suppliers, name);
  if (suppliers == NULL) {
    printf("No items found\n");
    PRESS_ENTER_TO_CONTINUE();
    return -1;
  }

  int i = 0;
  while (suppliers[i] != NULL) {
    display_supplier(&suppliers[i]->supplier);
    i++;
  }
  free(suppliers);

  PRESS_ENTER_TO_CONTINUE();
  return 0;
};
