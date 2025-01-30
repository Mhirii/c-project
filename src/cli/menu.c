#include "menu.h"
#include "../lib/lib.h"
#include "input.h"
#include <stdio.h>

#define PRESS_ENTER_TO_CONTINUE()                                              \
  do {                                                                         \
    printf("\nPress enter to continue...");                                    \
    while (getchar() != '\n')                                                  \
      ;                                                                        \
    getchar();                                                                 \
  } while (0)

void menu();
void main_menu(Memo *memo) {
  char choice = '9';
  while (choice != '0') {
    printf("\n\n");
    printf("Main Menu\n");
    printf("---------\n");
    printf("1. Inventory Management\n");
    printf("2. Supplier Management\n");
    printf("3. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf("%c", &choice);
    switch (choice) {
    case '1':
      inventory_management(memo->inventory);
      break;
    case '2':
      supplier_management(memo->suppliers);
    case '3':
      choice = '0';
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}

void inventory_management(InventoryIndex *index) {
  char choice = '9';
  while (choice != '0') {
    printf("\n\n");
    printf("Inventory Management\n");
    printf("--------------------\n");
    printf("1. Add Item\n");
    printf("2. Remove Item\n");
    printf("3. List Items\n");
    printf("4. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    switch (choice) {
    case '1':
      append_item(index, *read_inventory_item());
      break;
    case '2':
      printf("Enter item id: ");
      int id;
      scanf("%d", &id);
      del_item(index, id);
      break;
    case '3':
      inventory_display_all(index->head, 0);
      PRESS_ENTER_TO_CONTINUE();
      break;
    case '4':
      choice = '0';
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}

void supplier_management(SupplierList *list) {
  char choice = '9';
  while (choice != '0') {
    printf("\n\n");
    printf("Supplier Management\n");
    printf("--------------------\n");
    printf("1. Add Supplier\n");
    printf("2. Remove Supplier\n");
    printf("3. List Suppliers\n");
    printf("4. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    switch (choice) {
    case '1':
      append_supplier(list, *read_supplier());
      break;
    case '2':
      printf("Enter item id: ");
      int id;
      scanf("%d", &id);
      delete_supplier(list, id);
      break;
    case '3':
      supplier_display_all(list->head, 0);
      PRESS_ENTER_TO_CONTINUE();
      break;
    case '4':
      choice = '0';
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}
