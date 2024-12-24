#include "inventory/inventory.c"
#include "item/item.c"
#include "lib/errors.c"
#include "lib/log.c"
#include "lib/menus.c"
#include "lib/termcolor.c"
#include "lib/terminal.c"
#include "lib/terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int main() {
  int exit = 0;
  while (!exit) {
    main_menu();
    int choice = getch();

    clear_screen();
    move_cursor(1, 1);
    if (choice == 'q' || choice == 27 || choice == '0') {
      if (confirm_quit())
        exit = 1;
    } else
      switch (choice) {
      case '1':
        clear_screen();
        items_menu();
        break;
      case '2':
        printf("Supplier Management\n");
        break;
      case '3':
        printf("Preferences\n");
        break;

      default:
        printf("Invalid choice\n");
        break;
      }
  }

  return EXIT_SUCCESS;
}
