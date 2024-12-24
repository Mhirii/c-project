#ifndef STORE_H
#define STORE_H

struct Store{
	char *path;
	struct Inventory *inventory;
	struct Items *items;
};

#endif
