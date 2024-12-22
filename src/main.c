#include "../lib/terminal.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

void clear_screen() {
  printf("\033[H\033[J"); // ANSI escape code to clear the screen
}

void move_cursor(int row, int col) {
  printf("\033[%d;%dH", row, col); // ANSI escape code to move the cursor
}

void print_menu() {
  clear_screen();
  move_cursor(1, 1);
  printf("Please enter your choice:\n");
  print_option(1, "Manage Items");
  print_option(2, "Manage Suppliers");
  print_option(3, "Edit Preferences");
  printf("%s\n", format_option(0, "exit", RED));
}

void print_bottom_message(const char *message) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // Get terminal size
  move_cursor(w.ws_row, 1);             // Move cursor to the bottom row
  printf("%s", message);
}

int main() {
  int exit = 0;
  while (!exit) {
    print_menu();
    int choice =
        getch() - '0'; // Read a single character and convert it to an integer
    clear_screen();
    move_cursor(1, 1);
    switch (choice) {
    case 1:
      printf("Item Management\n");
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

  return EXIT_SUCCESS;
}
