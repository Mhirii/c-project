#include "memo.h"
#include "../lib/lib.h"
#include <stdlib.h>

void memo_init(Memo *memo) {
  InventoryIndex *index = read_inventory_index();
  LOG(1, "Loaded inventory index");

  SupplierList *suppliers = read_supplier_list();
  LOG(1, "Loaded suppliers list");

  memo->suppliers = suppliers;
  memo->inventory = index;
}

void memo_free(Memo *memo) {
  free_inventory_index(memo->inventory);
  free_supplier_list(memo->suppliers);
  free(memo);
}
