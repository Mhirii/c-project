#include "cli/inventory.c"
#include "cli/menu.c"
#include "config/config.c"
#include "inventory/inventory.c"
#include "inventory/inventory_json.c"
#include "lib/lib.c"
#include "json/json.c"

void example() {
  const char *path = "inv.json";
  struct InventoryNode *head = parse_inventory_node_json(path);

  if (!head) {
    LOG_ERR("Failed to parse inventory from file %s", path);
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
}

int main() {
  LOG(1, "Starting program");
  Config *config = malloc(sizeof(Config));

  load_config("config.json", config);

  LOG(0, "log_file_path %s", config->log_file_path);
  LOG(0, "low_stock_threshold %d", config->low_stock_threshold);
  LOG(0, "auto_reorder %d", config->auto_reorder);
  LOG(0, "report_generation_frequency %d", config->report_generation_frequency);

  main_menu(config);

  free(config);
  return 0;
}
