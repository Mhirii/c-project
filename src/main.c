#include "cli/inventory.c"
#include "config/config.h"
#include "inventory/inventory.c"
#include "inventory/inventory.h"
#include "inventory/inventory_json.c"
#include "lib/lib.c"
#include "json/json.c"
#include <stdio.h>

int main() {
  LOG(1, "Starting program");
  const char *path = "inv.json";
  struct InventoryNode *head = parse_inventory_node_json(path);

  if (!head) {
    LOG_ERR("Failed to parse inventory from file %s", path);
    return 1;
  }

  struct InventoryItem item1 = {1, "Product C", 19.99, 100, 20, 123, 1};
  struct InventoryItem item2 = {2, "Product D", 29.99, 50, 10, 456, 1};

  inventory_append(head, item1);
  inventory_append(head, item2);

  LOG(1, "Inventory successfully parsed");

  write_inventory_list_to_file(head, "output.json");

  struct InventoryNode *current = head;
  inventory_display_all(current, 1);

  // Free the linked list
  while (head) {
    struct InventoryNode *temp = head;
    head = head->next;
    if (temp) {
      free(temp->data.name);
      free(temp);
    }
  }

  return 0;
}
