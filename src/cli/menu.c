#include "menu.h"
#include "../api/api.h"
#include "../automation/gen_data.c"
#include "../lib/lib.h"
#include "../memo/inv_supp.c"
#include "input.h"
#include <stdio.h>

void menu();
void main_menu(Memo *memo) {
  char choice = '9';
  while (choice != 'q') {
    printf("\n\n");
    printf("Main Menu\n");
    printf("---------\n");
    printf("1. Inventory Management\n");
    printf("2. Supplier Management\n");
    printf("3. Generate Fake Data\n");
    printf("q. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf("%c", &choice);
    switch (choice) {
    case '1':
      inventory_management(memo);
      break;
    case '2':
      supplier_management(memo);
      break;
    case '3':
      gen_fake_data(memo);
      break;
    case 'q':
      choice = 'q';
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}

void inventory_management(Memo *m) {
  InventoryIndex *index = m->inventory;
  char choice = '9';
  while (choice != 'q') {
    printf("\n\n");
    printf("Inventory Management\n");
    printf("--------------------\n");
    printf("1. Add Item\n");
    printf("2. Remove Item\n");
    printf("3. List Items\n");
    printf("4. Update Item\n");
    printf("5. Find Item By ID\n");
    printf("6. Find Item By name\n");
    printf("q. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    switch (choice) {
    case '1':
      add_inv_item(m);
      break;
    case '2':
      del_inv_item(m);
      break;
    case '3':
      list_inv_items(m);
      break;
    case '4':
      update_inv_item(m);
      break;
    case '5':
      search_inv_item_id(m);
      break;
    case '6':
      search_inv_item_name(m);
      break;
    case 'q':
      choice = 'q';
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}

void supplier_management(Memo *m) {
  SupplierList *list = m->suppliers;
  char choice = '9';
  while (choice != 'q') {
    printf("\n\n");
    printf("Supplier Management\n");
    printf("--------------------\n");
    printf("1. Add Supplier\n");
    printf("2. Remove Supplier\n");
    printf("3. List Suppliers\n");
    printf("4. Update Supplier\n");
    printf("5. Find Supplier By ID\n");
    printf("6. Find Supplier By name\n");
    printf("7. Supplier Inventory\n");
    printf("q. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    switch (choice) {
    case '1':
      add_supp(m);
      break;
    case '2':
      del_supp(m);
      break;
    case '3':
      list_supp(m);
      break;
    case '4':
      update_supp(m);
      break;
    case '5':
      search_supplier_id(m);
      break;
    case '6':
      search_supplier_name(m);
      break;
    case '7':
      list_supplier_items(m);
      break;
    case 'q':
      choice = 'q';
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}
