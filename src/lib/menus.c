#include "menus.h"
#include "../item/item.h"
#include "terminal.h"
#include <stdio.h>

void menus_init() {}

// takes array of strings, loops and print them

void inventory_menu() {
  printf("%s\n", format_option(0, "Show Items", CYAN));
  printf("%s\n", format_option(0, "Add Item", CYAN));
  printf("%s\n", format_option(0, "Find Item", CYAN));
  printf("%s\n", format_option(0, "exit", RED));
}

void items_menu() {
  int exit = 0;
  while (!exit) {
    clear_screen();
    printf("Please enter your choice:\n");
    char *options[] = {"Show Items", "Add Item", "Find Item", NULL};
    move_cursor(1, 1);
    printf("Please enter your choice:\n");
    print_menu(options, "Back");
    int inv_choice = getch();
    switch (inv_choice) {
    case '1':
      printf("\nShow items\n");
      getch();
      break;
    case '2':
      printf("Add Item");
      get_user_input_for_item();
      break;
    case '3':
      printf("Preferences\n");
      getch();
      break;
    case '0':
      exit = 1;
      break;
    case 'q':
      exit = 1;
      break;
    case 27:
      exit = 1;
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}
