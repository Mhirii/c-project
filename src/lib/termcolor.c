#include "termcolor.h"
#include <stdlib.h>
#include <string.h>
#define prefix "\033["
#define suffix "\033[0m"

char *match_color(enum TermColors color) {
  switch (color) {
  case BLACK:
    return "30m";
  case RED:
    return "31m";
  case GREEN:
    return "32m";
  case YELLOW:
    return "33m";
  case BLUE:
    return "34m";
  case MAGENTA:
    return "35m";
  case CYAN:
    return "36m";
  case WHITE:
    return "37m";
  default:
    return "";
  }
}

char *colorize(char *message, enum TermColors color) {
  char *color_code = match_color(color);
  char *colorized_message = malloc(strlen(message) + strlen(color_code) +
                                   strlen(prefix) + strlen(suffix) + 1);
  strcpy(colorized_message, prefix);
  strcat(colorized_message, color_code);
  strcat(colorized_message, message);
  strcat(colorized_message, suffix);
  return colorized_message;
}
