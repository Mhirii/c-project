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
#include "report/report.c"
#include "report/report.h"
#include "supplier/supplier.c"
#include "supplier/supplier.h"
#include "json/json.c"

void print_usage() {
  printf("\033[1;33m📋 Usage:\033[0m\n");
  printf(" \t \033[1;36m🔍 main -i ls\033[0m \t\t\t\t \033[32mList "
         "all inventory items\033[0m\n");
  printf(" \t \033[1;36m➕ main -i a -n <name> -p <price> -q <quantity> -rs "
         "<reorder_level> "
         "-sp <supplier_id>\033[0m  \033[32mAdd a new item\033[0m\n");
  printf(" \t \033[1;36m🔄 main -i u --id <id> -n <name> -p <price> -q "
         "<quantity> -rs "
         "<reorder_level> -sp <supplier_id>\033[0m  \033[32mUpdate an "
         "item\033[0m\n");
  printf(" \t \033[1;36m❌ main -i d <id>\033[0m \t\t\t\t \033[32mDelete "
         "an item\033[0m\n");
  printf(" \t \033[1;36m👥 main -s ls\033[0m \t\t\t\t\t \033[32mList "
         "all suppliers\033[0m\n");
}

// Parse command line arguments for inventory items
void parse_inventory_args(int argc, char *argv[], char **name, double *price,
                          int *quantity, int *reorder_level, int *supplier_id,
                          int *id) {
  for (int i = 3; i < argc; i += 2) {
    if (strcmp(argv[i], "--id") == 0) {
      *id = atoi(argv[i + 1]);
    } else if (strcmp(argv[i], "-n") == 0) {
      *name = argv[i + 1];
    } else if (strcmp(argv[i], "-p") == 0) {
      *price = atof(argv[i + 1]);
    } else if (strcmp(argv[i], "-q") == 0) {
      *quantity = atoi(argv[i + 1]);
    } else if (strcmp(argv[i], "-rs") == 0) {
      *reorder_level = atoi(argv[i + 1]);
    } else if (strcmp(argv[i], "-sp") == 0) {
      *supplier_id = atoi(argv[i + 1]);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    return 1;
  }

  LOG(1, "Starting program");

  bootstrap();

  Memo *memo = malloc(sizeof(Memo));
  memo_init(memo);

  if (write_report(memo) == -1) {
    LOG_ERR("Error writing report");
    return -1;
  }

  // -i
  if (strcmp(argv[1], "-i") == 0) {
    // -i ls
    if (argc >= 3 && strcmp(argv[2], "ls") == 0) {
      inventory_display_all(memo->inventory->head, 0);
      // -i a
    } else if (argc >= 11 && strcmp(argv[2], "a") == 0) {
      char *name = NULL;
      double price = -1;
      int quantity = -1, reorder_level = -1, supplier_id = -1;

      parse_inventory_args(argc, argv, &name, &price, &quantity, &reorder_level,
                           &supplier_id, NULL);

      if (name && price > 0 && quantity > 0 && reorder_level > 0 &&
          supplier_id >= 0) {

        InventoryItem *item = new_inventory_item(0, name, price, quantity,
                                                 reorder_level, supplier_id);
        append_item(memo->inventory, *item);
      } else {
        LOG_ERR("Invalid arguments for adding an item.\n");
        print_usage();
      }
      // -i u
    } else if (argc >= 11 && strcmp(argv[2], "u") == 0) {
      int id = -1;
      char *name = NULL;
      double price = -1;
      int quantity = -1, reorder_level = -1, supplier_id = -1;

      parse_inventory_args(argc, argv, &name, &price, &quantity, &reorder_level,
                           &supplier_id, &id);

      if (id >= 0) {
        InventoryItem *item = new_inventory_item(0, name, price, quantity,
                                                 reorder_level, supplier_id);
        update_item(memo->inventory, id, *item);
      } else {
        LOG_ERR("Invalid arguments for updating an item.\n");
        print_usage();
      }
      // -i d
    } else if (argc >= 4 && strcmp(argv[2], "d") == 0) {
      int id = atoi(argv[3]);
      del_item(memo->inventory, id);
    } else {
      LOG_ERR("Invalid inventory command.\n");
      print_usage();
    }

    // -s
  } else if (strcmp(argv[1], "-s") == 0) {
    // -s ls
    if (argc >= 3 && strcmp(argv[2], "ls") == 0) {
      supplier_display_all(memo->suppliers->head, 0);
    } else {
      LOG_ERR("Invalid supplier command.\n");
      print_usage();
    }
  } else {
    LOG_ERR("Invalid command.\n");
    print_usage();
  }

  return 0;
}
