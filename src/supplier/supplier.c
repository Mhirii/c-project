
#include "supplier.h"
#include "../lib/lib.h"
#include "metadata.c"
#include "node.c"
#include "supp_io.c"
#include "util.c"
#include <stdlib.h>

SupplierList *init_supplier_list() {
  SupplierList *supp = (SupplierList *)malloc(sizeof(SupplierList));
  supp->head = NULL;
  supp->last_id = 0;
  supp->size = 0;
  return supp;
}

int append_supplier(SupplierList *list, Supplier supplier) {
  if (supplier.id > 0 &&
      (!check_supp_id_availability(list->head, supplier.id))) {
    LOG_ERR("tried to add supplier with id = %d, but it already exists",
            supplier.id);
    return -1;
  }

  if (supplier.id == 0)
    supplier.id = new_supp_id(list);

  SupplierNode *new_node = (SupplierNode *)malloc(sizeof(SupplierNode));
  if (new_node == NULL) {
    LOG_ERR("Error allocating memory for new supplier node");
    return -1;
  }

  new_node->supplier = supplier;
  new_node->next = NULL;

  if (list->head == NULL) {
    list->head = new_node;
  } else {
    SupplierNode *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
  list->size++;
  if (supplier.id > list->last_id)
    list->last_id = supplier.id;

  update_supp_metadata(list);
  write_supp(&supplier);
  return 0;
}

int free_supplier_list(SupplierList *list) {
  if (list == NULL) {
    LOG(2, "Tried to free NULL supplier list");
    return -1;
  }

  SupplierNode *current = list->head;
  free_supp_node(current);
  if (current != NULL) {
    LOG_ERR("Error freeing supplier node holding id = %d",
            current->supplier.id);
    return -1;
  }

  free(list);
  return 0;
}

int delete_supplier(SupplierList *list, int id) {
  int res = delete_supp_by_id(list->head, id);
  if (res == -1) {
    LOG_ERR("Error deleting supplier with id = %d", id);
    return -1;
  }

  list->size--;
  if (update_supp_metadata(list) != 0) {
    LOG_ERR("Error updating supplier metadata");
    return -1;
  }

  char *data_path = malloc(strlen(config.data_path) + strlen("/supplier/") +
                           strlen(".json") + 6);
  strcpy(data_path, config.data_path);
  char *filepath = strcat(data_path, "/supplier/");
  char id_str[32];
  sprintf(id_str, "%d", id);
  strcat(filepath, id_str);
  strcat(filepath, ".json");

  if (!delete_file(filepath)) {
    LOG_ERR("Error deleting file %s", filepath);
  };
  LOG(0, "Deleting supplier with id = %d", id);
  return 0;
}

int update_supplier(SupplierList *list, int id, Supplier supp) {
  if (list == NULL || list->head == NULL) {
    return -1;
  }

  SupplierNode *current = list->head;
  while (current != NULL) {
    if (current->supplier.id == id) {
      supp.id = id;
      current->supplier = supp;
      write_supp(&supp);
      return 0;
    }
    current = current->next;
  }

  return -1;
}

SupplierNode *find_supp_by_id(SupplierList *list, int id) {
  SupplierNode *current = list->head;

  while (current != NULL) {
    if (current->supplier.id == id) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}
