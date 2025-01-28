#include "menu.h"
#include "../lib/lib.h"
#include "inventory.h"
#include <stdio.h>

void menu();
void main_menu(Config *config) {
  LOG(0, "log_file_path %s", config->log_file_path);
  char choice = '9';
  while (choice != '0') {
    printf("\n\n");
    printf("Main Menu\n");
    printf("---------\n");
    printf("1. Inventory Management\n");
    printf("2. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf("%c", &choice);
    switch (choice) {
    case '1':
      inventory_management(config);
      break;
    case '2':
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}

void inventory_management(Config *config) {
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
    scanf("%c", &choice);
    switch (choice) {
    case '1':
      // read_inventory_item();
      break;
    case '2':
      // remove_item(config);
      break;
    case '3':
      // list_items(config);
      break;
    case '4':
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}
