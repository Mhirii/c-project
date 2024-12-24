#ifndef TERMINAL_H
#define TERMINAL_H

#include "termcolor.h"
char *format_option(int num, char *msg, enum TermColors color);
void print_option(int num, char *msg);
int getch(void);
void clear_screen();
void move_cursor(int row, int col);
void print_menu(char **options, char *exit_msg);
void print_bottom_message(const char *message);
void print_message(const char *message);

#endif
