#include "supplier.h"
#include <time.h>

int check_supp_id_availability(SupplierNode *head, int id) {
  SupplierNode *current = head;
  while (current != NULL) {
    if (current->supplier.id == id) {
      return 0;
    }
    current = current->next;
  }
  return 1;
}
int new_supp_id(SupplierList *index) { return index->last_id + 1; }
