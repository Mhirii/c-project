
#ifndef MENU_H
#define MENU_H

#include "../config/config.h"
#include "../inventory/inventory.h"
#include "../lib/vars.h"
#include "../supplier/supplier.h"
#include "../memo/memo.h"

void menu();
void main_menu(Memo *memo);
void inventory_management(InventoryIndex *index);
void supplier_management(SupplierList *list);

#endif
