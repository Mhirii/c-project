
#ifndef MENU_H
#define MENU_H

#include "../config/config.h"
#include "../inventory/inventory.h"
#include "../lib/vars.h"
#include "../supplier/supplier.h"

void menu();
void main_menu(InventoryIndex *index, SupplierList *list);
void inventory_management(InventoryIndex *index);
void supplier_management(SupplierList *list);

#endif
