
#ifndef SUPPLIER_NODE_C
#define SUPPLIER_NODE_C
#include "supplier.h"
#include <stdlib.h>
#include <time.h>

#define FREE_IF_NOT_NULL(ptr)                                                  \
  if ((ptr) != NULL) {                                                         \
    free(ptr);                                                                 \
  }

void free_supp(Supplier *supp) {
  if (supp != NULL) {
    FREE_IF_NOT_NULL(supp->email);
    FREE_IF_NOT_NULL(supp->first_name);
    FREE_IF_NOT_NULL(supp->last_name);
    FREE_IF_NOT_NULL(supp->phone);
    free(supp);
  }
};

void free_supp_node(SupplierNode *head) {
  SupplierNode *current = head;
  SupplierNode *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

int delete_supp_by_id(SupplierNode *head, int id) {
  int found = -1;
  SupplierNode *current = head;
  SupplierNode *previous = NULL;
  while (current != NULL) {
    if (current->supplier.id == id) {
      if (previous == NULL) {
        head = current->next;
      } else {
        previous->next = current->next;
      }
      free_supp(&current->supplier);
      found = 0;
      break;
    }
    previous = current;
    current = current->next;
  }
  return found;
}

#endif
