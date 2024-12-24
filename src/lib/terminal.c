#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

char *format_option(int num, char *msg, enum TermColors color) {
  char num_str[32];
  sprintf(num_str, "%d. ", num);
  char *colored_num = colorize(num_str, color);
  char *result = malloc(strlen(colored_num) + strlen(msg) + 2);
  sprintf(result, "%s%s", colored_num, msg);
  free(colored_num);
  return result;
}

void print_option(int num, char *msg) {
  printf("%s\n", format_option(num, msg, CYAN));
}

int getch(void) {
  struct termios oldt, newt;
  int ch;
  // gets current terminal attributes
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  // disable canonical mode and echo
  newt.c_lflag &= ~(ICANON | ECHO);
  // set new terminal attributes
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  // read a single character
  ch = getchar();
  // Re-apply old attributes
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

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
