
#include "api/api.h"
#include "api/api_inv.c"
#include "api/api_supp.c"
#include "cli/input.c"
#include "cli/menu.c"
#include "cli/menu.h"
#include "config/config.c"
#include "inventory/inventory.c"
#include "inventory/inventory.h"
#include "inventory/inventory_index.c"
#include "inventory/inventory_index_io.c"
#include "inventory/inventory_json.c"
#include "lib/lib.c"
#include "lib/log.h"
#include "memo/memo.c"
#include "memo/memo.h"
#include "supplier/supplier.c"
#include "supplier/supplier.h"
#include "json/json.c"

int main() {
  LOG(1, "Starting program");

  bootstrap();

  Memo *memo = malloc(sizeof(Memo));
  memo_init(memo);

  main_menu(memo);

  return 0;
}
