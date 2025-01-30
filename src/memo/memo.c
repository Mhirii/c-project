#include "memo.h"
#include "../lib/lib.h"
#include <stdlib.h>

void memo_init(Memo *memo) {
  memo->inventory = read_inventory_index();
  LOG(1, "Loaded inventory index");
  if (memo->inventory == NULL) {
    LOG(1, "No inventory found");
  }
  memo->suppliers = read_supplier_list();
  if (memo->suppliers == NULL) {
    LOG(1, "No suppliers found");
  }
  LOG(1, "Loaded suppliers list");
}

void memo_free(Memo *memo) {
  free_inventory_index(memo->inventory);
  free_supplier_list(memo->suppliers);
  free(memo);
}
