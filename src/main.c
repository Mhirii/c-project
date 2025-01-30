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
#include "supplier/supplier.c"
#include "supplier/supplier.h"
#include "json/json.c"

int main() {
  LOG(1, "Starting program");
  Config *config = malloc(sizeof(Config));
  load_config("config.json");
  LOG(1, "Loaded Config");
  InventoryIndex *index = read_inventory_index();
  LOG(1, "Loaded inventory index");
  SupplierList *suppliers = read_supplier_list();
  LOG(1, "Loaded suppliers list");

  main_menu(index, suppliers);

  free(config);
  return 0;
}
