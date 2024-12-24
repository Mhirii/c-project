#include "terminal.h"
#include <ctype.h>
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

void print_menu(char **options) {
  int i = 0;
  while (options[i] != NULL) {
    printf("%s\n", format_option(i + 1, options[i], CYAN));
    i++;
  }
  printf("%s\n", format_option(0, "exit", RED));
}

void main_menu() {
  char *options[] = {"Items", "Suppliers", "Preferences", NULL};
  clear_screen();
  move_cursor(1, 1);
  printf("Please enter your choice:\n");
  print_menu(options);
}

void print_bottom_message(const char *message) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // Get terminal size
  move_cursor(w.ws_row, 1);             // Move cursor to the bottom row
  printf("%s", message);
}

void print_border(int start_row, int start_col, int width) {
  move_cursor(start_row, start_col);
  for (int i = 0; i < width; i++) {
    printf("=");
  }
  printf("\n");
}

int calculate_max_line_length(const char *message, int len, int max_width) {
  int max_line_len = 0;
  for (int i = 0; i < len; i += max_width) {
    int line_len = 0;
    for (int j = 0; j < max_width && (i + j) < len; j++) {
      line_len++;
    }
    if (line_len > max_line_len) {
      max_line_len = line_len;
    }
  }
  return max_line_len;
}

void print_message_line(const char *message, int start_row, int start_col,
                        int i, int max_width, int len, int max_line_len) {
  int line_len = 0;
  for (int j = 0; j < max_width && (i + j) < len; j++) {
    line_len++;
  }

  move_cursor(start_row + 1 + (i / max_width), start_col);
  printf("  "); // Left padding (2 spaces)
  for (int j = 0; j < max_width && (i + j) < len; j++) {
    printf("%c", message[i + j]);
  }

  for (int j = line_len; j < max_line_len; j++) {
    printf(" ");
  }
  printf("  \n");
}

int get_yn_response(int start_row, int start_col) {
  move_cursor(start_row, start_col);
  printf("Enter [%s]es or [%s]o: ", colorize("Y", GREEN), colorize("N", RED));
  char response;
  do {
    response = toupper(getch());
  } while (response != 'Y' && response != 'N');
  if (response == 'Y') {
    printf("%s\n", colorize("Y", GREEN));
  } else {
    printf("%s\n", colorize("N", RED));
  }

  return response == 'Y';
}

int print_message_with_prompt(const char *message, int prompt_yn) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  const char MARGIN = 30;

  int max_width = w.ws_col - MARGIN;
  int len = strlen(message);
  int lines = (len + max_width - 1) / max_width;

  int max_line_len = calculate_max_line_length(message, len, max_width);
  int start_row = (w.ws_row - lines - 2) / 2;
  int border_width = max_line_len + 4;
  int start_col = (w.ws_col - border_width) / 2;

  print_border(start_row, start_col, border_width);

  for (int i = 0; i < len; i += max_width) {
    print_message_line(message, start_row, start_col, i, max_width, len,
                       max_line_len);
  }

  print_border(start_row + lines + 1, start_col, border_width);

  if (prompt_yn) {
    return get_yn_response(start_row + lines + 2, (w.ws_col - 30) / 2);
  } else {
    getch();
  }
  return 0;
}

void print_message(const char *message) {
  print_message_with_prompt(message, 0);
}

int confirm_quit() {
  return print_message_with_prompt("Are you sure you want to quit?", 1);
}
