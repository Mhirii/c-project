#include "menu.h"
#include <stdio.h>

void menu();
void main_menu(struct Config *config) {
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

void inventory_management(struct Config *config) {
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
      // add_item(config);
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
