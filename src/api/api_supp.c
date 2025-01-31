
#include "../cli/input.h"
#include "../lib/lib.h"
#include "../lib/macros.h"
#include "../memo/memo.h"
#include "../supplier/supplier.h"

#include "api.h"
#include <stdio.h>

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

int update_supp(Memo *memo);
int search_supplier_id(Memo *memo);
int search_supplier_name(Memo *memo);
