#include "menus.h"
#include "terminal.h"
#include <stdio.h>

void menus_init() {}

// takes array of strings, loops and print them

void main_menu() {
  printf("Please enter your choice:\n");
  printf("%s\n", format_option(1, "Manage Inventories", CYAN));
  printf("%s\n", format_option(2, "Manage Items", CYAN));
  printf("%s\n", format_option(3, "Manage Suppliers", CYAN));
  printf("%s\n", format_option(4, "Edit Preferences", CYAN));
  printf("%s\n", format_option(0, "exit", RED));
}

void inventory_menu() {
  printf("%s\n", format_option(0, "Show Items", CYAN));
  printf("%s\n", format_option(0, "Add Item", CYAN));
  printf("%s\n", format_option(0, "Find Item", CYAN));
  printf("%s\n", format_option(0, "exit", RED));
}

void items_menu() {}
