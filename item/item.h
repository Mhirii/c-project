#ifndef itempkg
#define itempkg

struct Item {
    int ID;
    int quantity;
    float price;
    char *name;
    char *description;
};

struct Item *createItem(int ID, int quantity, float price, char *name, char *description );
char* deleteItem(struct Item *item);

#endif
