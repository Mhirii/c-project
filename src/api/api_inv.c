#include "../cli/input.h"
#include "../lib/macros.h"
#include "api.h"
#include <stdio.h>
#include <stdlib.h>

int add_inv_item(Memo *memo) {
  return append_item(memo->inventory, *read_inventory_item());
};

int del_inv_item(Memo *memo) {
  printf("Enter item id: ");
  int id;
  if (scanf("%d", &id) != 1) {
    return -1;
  }
  return del_item(memo->inventory, id);
};

int list_inv_items(Memo *memo) {
  inventory_display_all(memo->inventory->head, 1);
  PRESS_ENTER_TO_CONTINUE();
  return 0;
};

int update_inv_item(Memo *memo) {
  printf("Enter item id: ");
  int id;
  if (scanf("%d", &id) != 1) {
    return -1;
  }

  return update_item(memo->inventory, id, *read_inventory_item());
};

int search_inv_item_id(Memo *memo) {
  printf("Enter item id: ");
  int id;
  if (scanf("%d", &id) != 1) {
    return -1;
  }
  InventoryNode *n = find_item_by_id(memo->inventory, id);
  inventory_display_item(n->data);
  PRESS_ENTER_TO_CONTINUE();
  return 0;
};
int search_inv_item_name(Memo *memo) {
  char name[MAX_STRING_LENGTH];
  printf("Enter item name: ");
  if (scanf("%s", name) != 1) {
    return -1;
  }
  InventoryNode **nodes = search_items_by_name(memo->inventory, name);
  if (nodes == NULL) {
    printf("No items found\n");
    PRESS_ENTER_TO_CONTINUE();
    return -1;
  }

  int i = 0;
  while (nodes[i] != NULL) {
    inventory_display_item_minimal(nodes[i]->data);
    i++;
  }
  free(nodes);

  PRESS_ENTER_TO_CONTINUE();
  return 0;
};
