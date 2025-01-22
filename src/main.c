#include "cli/inventory.c"
#include "config/config.h"
#include "inventory/inventory.c"
#include "inventory/inventory.h"
#include "inventory/inventory_json.c"
#include "lib/lib.c"
#include "json/json.c"
#include <stdio.h>

int main() {
  Log(1, "Starting program");
  // LOG_ERR("hello");

  // struct InventoryItem *item1 = new_inventory_item(1, "test", 10, 10, 0, 1);
  // struct InventoryNode *inventory = inventory_add(NULL, *item1);

  // struct InventoryItem *item2 = read_inventory_item(inventory);

  // inventory_add(inventory, *item2);
  // inventory_display_all(inventory, 1);

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
