#include "cli/inventory.c"
#include "config/config.h"
#include "inventory/inventory.c"
#include "inventory/inventory.h"
#include "lib/err.h"
#include "lib/log.c"
#include "lib/log.h"
#include "lib/vars.h"

#include <stdio.h>

int main() {
  Log(1, "Starting program");
  LOG_ERR("hello");

  struct InventoryItem *item1 = new_inventory_item(1, "test", 10, 10, 0, 1);
  struct InventoryNode *inventory = inventory_add(NULL, *item1);

  struct InventoryItem *item2 = read_inventory_item(inventory);

  inventory_add(inventory, *item2);
  inventory_display_all(inventory, 1);

  return 0;
}
