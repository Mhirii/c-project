#ifndef ERR_H
#define ERR_H

#define CHECK_ERROR(condition, message) \
  if (condition) {                                  \
    LOG_ERR(message);                               \
    *isErr = 1;                                     \
  }

#define CHECK_ERROR_RETURN(condition, message, return_type) \
  if (condition) {                                  \
    LOG_ERR(message);                               \
    *isErr = 1;                                     \
    return (return_type){0};                        \
  }

// Example usage:
// struct Result {
//   int value;
// };
//
// Result divide(int a, int b, int* isErr) {
//   CHECK_ERROR_RETURN(b == 0, "Division by zero", Result);
//   return (Result){a / b};
// }


#endif
