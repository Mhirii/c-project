#ifndef JSON_H
#define JSON_H


#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * Skip whitespace characters in the JSON string
 * @param json Pointer to a pointer of the JSON string, will be updated to point
 * after whitespace
 */
void skip_whitespace(const char **json);

/**
 * @brief Parse a JSON string value
 * @param json Pointer to a pointer of the JSON string
 * @param str Pointer to a string pointer that will be allocated
 * @return 1 if successful, 0 if invalid JSON string
 *
 * Takes a pointer to JSON string and advances it past the string value.
 * Allocates memory for and returns the parsed string via str parameter.
 * Returns 1 if successful, 0 if invalid JSON string format.
 */
int parse_json_string(const char **json, char **str);

/**
 * @brief Parse a JSON number value
 * @param json Pointer to a pointer of the JSON string
 * @param num Pointer to integer where parsed number will be stored
 * @return 1 if successful, 0 if invalid JSON number
 *
 * Takes a pointer to JSON string and advances it past the number value.
 * Parses an integer number and stores it via num parameter.
 * Returns 1 if successful, 0 if no valid number found.
 */
int parse_json_number(const char **json, int *num);

/**
 * @brief Parse a JSON float value
 * @param json Pointer to a pointer of the JSON string
 * @param num Pointer to float where parsed number will be stored
 * @return 1 if successful, 0 if invalid JSON float
 *
 * Takes a pointer to JSON string and advances it past the float value.
 * Parses a floating point number and stores it via num parameter.
 * Returns 1 if successful, 0 if no valid float found.
 */
int parse_json_float(const char **json, float *num);

/**
 * @brief Parse a JSON boolean value
 * @param json Pointer to a pointer of the JSON string
 * @param num Pointer to integer where parsed boolean will be stored
 * @return 1 if successful, 0 if invalid JSON boolean
 *
 * Takes a pointer to JSON string and advances it past the boolean value.
 * Parses a boolean value ("true" or "false") and stores 1 or 0 via num
 * parameter. Returns 1 if successful, 0 if no valid boolean found.
 */
int parse_json_bool(const char **json, int *num);

/**
 * @brief Parse a JSON null value
 * @param json Pointer to a pointer of the JSON string
 * @param num Pointer to integer where 0 will be stored if null found
 * @return 1 if successful, 0 if not a null value
 *
 * Takes a pointer to JSON string and advances it past the null value.
 * Sets num to 0 if "null" is found.
 * Returns 1 if successful, 0 if not a null value.
 */
int parse_json_null(const char **json, int *num);

#endif
