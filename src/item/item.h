#ifndef itempkg
#define itempkg

struct Item {
    int ID;
    int quantity;
    float price;
    char *name;
    char *description;
    struct Item *next;
};

struct Item *create_item(int ID, int quantity, float price, char *name, char *description );
char* delete_item(struct Item *item);

#endif
