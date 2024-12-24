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
    print_menu();
    int choice =
        getch() - '0'; // Read a single character and convert it to an integer
    clear_screen();
    move_cursor(1, 1);
    switch (choice) {
    case 1:
      printf("Please enter your choice:\n");
      print_option(1, "Show Items");
      print_option(2, "Add Item");
      print_option(3, "Find Item");
      printf("%s\n", format_option(0, "exit", RED));
      int inv_choice = getch() - '0';
      switch (inv_choice) {
      case 1:
        printf("Show items");
        break;
      case 2:
        printf("Show Items");
        break;
      case 3:
        printf("Preferences\n");
        break;
      case 0:
        break;
      default:
        printf("Invalid choice\n");
        break;
      }
      break;
    case 2:
      printf("Supplier Management\n");
      break;
    case 3:
      printf("Preferences\n");
      break;
    case 0:
      exit = 1;
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
    print_bottom_message("Press any key to continue...");
    getch(); // Wait for user input before continuing
  }

  print_item(item);
  delete_inventory(inventory);
  return EXIT_SUCCESS;
}
