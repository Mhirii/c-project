#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "errors.c"
#include "log.c"
#include "result.c"
#include "termcolor.c"

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
