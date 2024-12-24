#ifndef inventorypkg
#define inventorypkg

#include "../item/item.h"

struct Inventory {
  int ID;
  struct Item *items;
  int size;
  int lastID;
};

struct Inventory *create_inventory(int ID);

char *delete_inventory(struct Inventory *inventory);

struct Item *add_item(struct Inventory *inventory, int quantity, float price, char *name, char *description);
struct Item *get_item_by_id(struct Inventory *inventory, int ID);
void remove_item(struct Inventory *inventory, int ID);

void inventory_menu(struct Inventory *inventory);

#endif
