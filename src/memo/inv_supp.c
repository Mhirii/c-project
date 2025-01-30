
#include "../lib/lib.h"
#include "memo.h"
#include <stdlib.h>

InventoryNode *get_products_by_supplier(Memo *m, int supplier_id) {
  InventoryNode *n_head = NULL;
  InventoryNode *n_tail = NULL;
  LOG(0, "INIT inv supp");

  if (m == NULL || m->inventory == NULL) {
    return NULL;
  }

  InventoryNode *current = m->inventory->head;

  while (current != NULL) {
    if (current->data.supplier_id == supplier_id) {
      InventoryNode *new_node = malloc(sizeof(InventoryNode));
      if (new_node == NULL) {
        // On allocation failure, clean up and return NULL
        InventoryNode *tmp;
        while (n_head != NULL) {
          tmp = n_head;
          n_head = n_head->next;
          free(tmp);
        }
        return NULL;
      }

      *new_node = *current;
      new_node->next = NULL;

      if (n_head == NULL) {
        n_head = new_node;
        n_tail = new_node;
      } else {
        n_tail->next = new_node;
        n_tail = new_node;
      }
    }
    current = current->next;
  }

  return n_head;
}
