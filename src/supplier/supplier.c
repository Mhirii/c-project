
#include "supplier.h"
#include "../lib/lib.h"
#include "metadata.c"
#include "node.c"
#include "supp_io.c"
#include "util.c"
#include <stdlib.h>

int validate_supp_string(char *str) {
  if (str == NULL || strlen(str) > MAX_STRING_LENGTH) {
    LOG_ERR("String is not valid");
    return 0;
  }
  return 1;
}

Supplier *new_supplier(int id, char *first_name, char *last_name, char *email,
                       char *phone) {
  Supplier *supp = (Supplier *)malloc(sizeof(Supplier));

  if (supp == NULL) {
    return NULL;
    LOG_ERR("Error allocating memory for new supplier");
  }

  if (!validate_supp_string(first_name)) {
    free(supp);
    return NULL;
  }
  if (!validate_supp_string(last_name)) {
    free(supp);
    return NULL;
  }
  if (!validate_supp_string(email)) {
    free(supp);
    return NULL;
  }
  if (!validate_supp_string(phone)) {
    free(supp);
    return NULL;
  }

  supp->id = id;
  supp->first_name = first_name;
  supp->last_name = last_name;
  supp->email = email;
  supp->phone = phone;
  return supp;
}

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

SupplierList *read_supplier_list() {
  char *path = malloc(strlen(config.data_path) + strlen("/supplier") + 1);
  path = strcpy(path, config.data_path);
  path = strcat(path, "/supplier");

  SupplierList *list = init_supplier_list();

  char *metadata = malloc(strlen(path) + strlen("/metadata") + 1);
  sprintf(metadata, "%s/metadata", path);

  int res = parse_supp_metadata(metadata, list);
  if (res == -1) {
    LOG_ERR("Error occurred while parsing supplier metadata file");
    free_supplier_list(list);
    free(path);
    free(metadata);
    return NULL;
  }

  res = read_suppliers(path, list);
  if (res == -1) {
    LOG_ERR("Error reading items");
    free_supplier_list(list);
    free(metadata);
    free(path);
    free(list);
    return NULL;
  }

  LOG(1, "Supplier list successfully read");
  return list;
}

void display_supplier(Supplier *supp) {
  if (supp == NULL) {
    LOG_ERR("Cannot display NULL item");
    return;
  }

  printf("ID:            %d\n", supp->id);
  printf("First Name:    %s\n", supp->first_name);
  printf("Last Name:     %s\n", supp->last_name);
  printf("Email:         %s\n", supp->email);
  printf("Phone:         %s\n", supp->phone);
}

void supplier_display_all(SupplierNode *head, int minimal) {
  if (head == NULL) {
    LOG_ERR("Cannot display empty list");
    return;
  }

  SupplierNode *current = head;
  while (current != NULL) {
    if (minimal == 0) {
      printf("\n---------------- ----------------\n\n");
      display_supplier(&current->supplier);
      if (current->next == NULL)
        printf("\n---------------- ----------------\n\n");

    } else {
      printf("%d: %s %s\n", current->supplier.id, current->supplier.first_name,
             current->supplier.last_name);
    }
    current = current->next;
  }
}
