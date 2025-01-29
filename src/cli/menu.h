
#ifndef MENU_H
#define MENU_H

#include "../config/config.h"
#include "../inventory/inventory.h"
#include "../lib/vars.h"

void menu();
void main_menu(InventoryIndex *index);
void inventory_management(InventoryIndex *index);

#endif
