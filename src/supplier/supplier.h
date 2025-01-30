
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
int free_supplier_list(SupplierList *list);
int delete_supplier(SupplierList *list, int id);
int update_supplier(SupplierList *list, int id, Supplier supp);
SupplierNode *find_supp_by_id(SupplierList *list, int id);

SupplierList *read_supplier_list();

int get_supplier(SupplierList *list, int id, Supplier *supplier);
SupplierNode *get_supplier_node(SupplierList *list, int id);

int update_supp_metadata(SupplierList *list);
int write_supp_metadata(char *path, SupplierList *list);
int parse_supp_metadata(char *path, SupplierList *list);

void display_supplier(Supplier *supp);
void supplier_display_all(SupplierNode *head, int minimal);
#endif
