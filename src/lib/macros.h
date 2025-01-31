
#ifndef MACROS_H
#define MACROS_H


#define PRESS_ENTER_TO_CONTINUE()                                              \
  do {                                                                         \
    printf("\nPress enter to continue...");                                    \
    while (getchar() != '\n')                                                  \
      ;                                                                        \
    getchar();                                                                 \
  } while (0)

#endif
