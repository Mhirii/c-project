#ifndef termcolorpkg
#define termcolorpkg

enum TermColors { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
char *colorize(char *message, enum TermColors color);

#endif
