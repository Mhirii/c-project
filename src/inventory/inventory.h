#ifndef INVENTORY_H
#define INVENTORY_H

#include "../config/config.h"
#include "../lib/vars.h"
#include <time.h>

typedef struct InventoryItem {
  int id;
  char *name;
  double price;
  int quantity;
  int reorder_level;
  int supplier_id;
  time_t last_updated;
} InventoryItem;

typedef struct InventoryNode {
  struct InventoryItem data;
  struct InventoryNode *next;
} InventoryNode;

typedef struct InventoryIndex {
  InventoryNode *head;
  int size;
  int last_id;
} InventoryIndex;

InventoryIndex *init_inventory_index();
int free_inventory_index(InventoryIndex *index);
int append_item(InventoryIndex *index, InventoryItem item);
int del_item(InventoryIndex *index, int id);
int update_item(InventoryIndex *index, int id, InventoryItem item);
InventoryNode *find_item_by_id(InventoryIndex *index, int id);
InventoryNode **search_items_by_name(InventoryIndex *index, char *name);
InventoryNode **search_items_by_supplier_id(InventoryIndex *index,
                                            int supplier_id);

InventoryIndex *read_inventory_index();
int parse_metadata(char *path, InventoryIndex *index);
int read_items(char *path, InventoryIndex *index);
int write_items(char *path, InventoryIndex *index);
int read_item(char *path, InventoryItem *item);
int write_item(InventoryItem *item);

InventoryNode *new_inventory();
void delete_inventory(InventoryNode *head);
int delete_inventory_item_by_id(InventoryNode *head, int id);

InventoryItem *new_inventory_item(int id, char *name, double price,
                                  int quantity, int reorder_level,
                                  int supplier_id);
void delete_inventory_item(InventoryItem *item);

InventoryNode *inventory_append(InventoryNode *head, InventoryItem item);
InventoryNode *inventory_update(InventoryNode *head, int id,
                                InventoryItem new_data);
InventoryNode *inventory_delete(InventoryNode *head, int id);
InventoryItem *inventory_find(InventoryNode *head, int id);
void inventory_display_all(InventoryNode *head, int minimal);
void inventory_display_item(InventoryItem *item);
int check_id_availability(InventoryNode *head, int id);

void check_low_stock(InventoryNode *head, Config *config);
void update_stock_quantity(InventoryNode *head, int id, int quantity_change);

/**
 * Loads inventory data from a JSON string and creates a new inventory list
 *
 * @param head      Pointer to the head of the inventory list
 * @param json      JSON string containing inventory data
 * @return          Pointer to the new head of the inventory list
 */
InventoryNode *inventory_from_json(InventoryNode *head, char *json);

#endif
