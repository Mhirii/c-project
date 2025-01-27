#ifndef INVENTORY_H
#define INVENTORY_H

#include <time.h>
#include "../lib/vars.h"
#include "../config/config.h"

struct InventoryItem {
    int id;
    char *name;
    double price;
    int quantity;
    int reorder_level;
    int supplier_id;
    time_t last_updated;
};
struct InventoryNode {
    struct InventoryItem data;
    struct InventoryNode* next;
};

struct InventoryNode* new_inventory();
void delete_inventory(struct InventoryNode *head);

struct InventoryItem *new_inventory_item(int id, char *name, double price,
                                         int quantity, int reorder_level,
                                         int supplier_id);
void delete_inventory_item(struct InventoryItem *item);

struct InventoryNode* inventory_append(struct InventoryNode* head, struct InventoryItem item);
struct InventoryNode* inventory_update(struct InventoryNode* head, int id, struct InventoryItem new_data);
struct InventoryNode* inventory_delete(struct InventoryNode* head, int id);
struct InventoryItem* inventory_find(struct InventoryNode* head, int id);
void inventory_display_all(struct InventoryNode* head, int minimal);
void inventory_display_item(struct InventoryItem* item);
int check_id_availability(struct InventoryNode* head, int id);

void check_low_stock(struct InventoryNode* head, Config* config);
void update_stock_quantity(struct InventoryNode* head, int id, int quantity_change);

/**
 * Loads inventory data from a JSON string and creates a new inventory list
 *
 * @param head      Pointer to the head of the inventory list
 * @param json      JSON string containing inventory data
 * @return          Pointer to the new head of the inventory list
 */
struct InventoryNode* inventory_from_json(struct InventoryNode* head, char* json);

#endif
