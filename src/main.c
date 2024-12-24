#include "inventory/inventory.c"
#include "item/item.c"
#include "lib/errors.c"
#include "lib/log.c"
#include "lib/termcolor.c"
#include "lib/terminal.c"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int main() {
  struct Inventory *inventory = create_inventory(1);
  add_item(inventory, 1, 10.0, "Test Item", "This is a test item");
  struct Item *item =
      add_item(inventory, 2, 20.0, "Test Item 2", "This is a test item 2");

  int exit = 0;
  while (!exit) {
    main_menu();
    int choice = getch();
    clear_screen();
    move_cursor(1, 1);
    switch (choice) {
    case '1':
      printf("Please enter your choice:\n");

      char *options[] = {"Show Items", "Add Item", "Find Item", NULL};
      move_cursor(1, 1);
      printf("Please enter your choice:\n");
      print_menu(options);
      int inv_choice = getch();
      switch (inv_choice) {
      case '1':
        printf("Show items");
        break;
      case '2':
        printf("Add Item");
        get_user_input_for_item();
        break;
      case '3':
        printf("Preferences\n");
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
      break;
    case '2':
      printf("Supplier Management\n");
      break;
    case '3':
      printf("Preferences\n");
      break;
    case '0':
      if (confirm_quit())
        exit = 1;
      break;
    case 'q':
      if (confirm_quit())
        exit = 1;
      break;
    case 27:
      if (confirm_quit())
        exit = 1;
      break;

    default:
      printf("Invalid choice\n");
      break;
    }
  }

  delete_inventory(inventory);
  return EXIT_SUCCESS;
}
