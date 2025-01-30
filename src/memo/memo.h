
#ifndef MEMO_H
#define MEMO_H

#include "../inventory/inventory.h"
#include "../supplier/supplier.h"

typedef struct Memo{
	InventoryIndex *inventory;
	SupplierList *suppliers;
}Memo;

void memo_init(Memo *memo);
void memo_free(Memo *memo);

#endif
