
#ifndef SUPPLIER_H
#define SUPPLIER_H

typedef struct {
  int id;
  char *first_name;
  char *last_name;
  char *email;
  char *phone;
} Supplier;

typedef struct SupplierNode {
  Supplier supplier;
  struct SupplierNode *next;
} SupplierNode;

typedef struct {
  SupplierNode *head;
  int size;
  int last_id;
} SupplierList;

Supplier *new_supplier(int id, char *first_name, char *last_name, char *email,
                       char *phone);

int append_supplier(SupplierList *list, Supplier supplier);
int delete_supplier(SupplierList *list, int id);
int update_suuplier(SupplierList *list, int id, Supplier *supplier);
int get_supplier(SupplierList *list, int id, Supplier *supplier);
SupplierNode *get_supplier_node(SupplierList *list, int id);

int update_supp_metadata(SupplierList *list);
int write_supp_metadata(char *path, SupplierList *list);
int parse_supp_metadata(char *path, SupplierList *list);

void supplier_display_all(SupplierNode *head, int minimal);
#endif
