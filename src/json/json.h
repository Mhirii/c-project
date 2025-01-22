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

/**
 * @brief Parse the start of a JSON object
 * @param json Pointer to a pointer of the JSON string
 * @return 1 if successful, 0 if not a JSON object
 *
 * Takes a pointer to JSON string and advances it past the opening brace.
 * Returns 1 if successful, 0 if not the start of an object.
 */
int parse_json_object(const char **json);

/**
 * @brief Parse the end of a JSON object
 * @param json Pointer to a pointer of the JSON string
 * @return 1 if successful, 0 if not the end of an object
 *
 * Takes a pointer to JSON string and advances it past the closing brace.
 * Returns 1 if successful, 0 if not the end of an object.
 */
int parse_json_object_end(const char **json);

/**
 * @brief Parse a JSON object key
 * @param json Pointer to a pointer of the JSON string
 * @param key Pointer to a string pointer that will be allocated
 * @return 1 if successful, 0 if invalid key
 *
 * Takes a pointer to JSON string and parses an object key.
 * Allocates memory for and returns the key string via key parameter.
 * Returns 1 if successful, 0 if invalid key format.
 */
int parse_json_key(const char **json, char **key);

/**
 * @brief Parse a JSON key-value separator
 * @param json Pointer to a pointer of the JSON string
 * @return 1 if successful, 0 if not a separator
 *
 * Takes a pointer to JSON string and advances it past the colon separator.
 * Returns 1 if successful, 0 if not a valid separator.
 */
int parse_json_key_value_separator(const char **json);

/**
 * @brief Parse a JSON value separator
 * @param json Pointer to a pointer of the JSON string
 * @return 1 if successful, 0 if not a separator
 *
 * Takes a pointer to JSON string and advances it past the comma separator.
 * Returns 1 if successful, 0 if not a valid separator.
 */
int parse_json_value_separator(const char **json);

/**
 * @brief Parse the start of a JSON array
 * @param json Pointer to a pointer of the JSON string
 * @return 1 if successful, 0 if not a JSON array
 *
 * Takes a pointer to JSON string and advances it past the opening bracket.
 * Returns 1 if successful, 0 if not the start of an array.
 */
int parse_json_array(const char **json);

/**
 * @brief Parse the end of a JSON array
 * @param json Pointer to a pointer of the JSON string
 * @return 1 if successful, 0 if not the end of an array
 *
 * Takes a pointer to JSON string and advances it past the closing bracket.
 * Returns 1 if successful, 0 if not the end of an array.
 */
int parse_json_array_end(const char **json);


/**
 * @brief Append a key-value pair to a JSON string
 * @param json Pointer to a pointer of the JSON string that will be modified
 * @param key The key string to append
 * @param value The value string to append
 *
 * Takes a pointer to a JSON string pointer and appends a key-value pair.
 * Allocates or reallocates memory as needed and adds comma separators.
 * The key and value are formatted as a proper JSON pair.
 */
void append_json_pair(char **json, const char *key, const char *value);

/**
 * @brief Append a string key-value pair to a JSON string
 * @param json Pointer to a pointer of the JSON string that will be modified
 * @param key The key string to append
 * @param value The string value to append
 *
 * Formats and appends a key-value pair where the value is a string.
 * The value is properly quoted as a JSON string.
 */
void append_json_string_pair(char **json, const char *key, const char *value);

/**
 * @brief Append a number key-value pair to a JSON string
 * @param json Pointer to a pointer of the JSON string that will be modified
 * @param key The key string to append
 * @param value The integer value to append
 *
 * Formats and appends a key-value pair where the value is an integer number.
 */
void append_json_number_pair(char **json, const char *key, int value);

/**
 * @brief Append a float key-value pair to a JSON string
 * @param json Pointer to a pointer of the JSON string that will be modified
 * @param key The key string to append
 * @param value The double value to append
 *
 * Formats and appends a key-value pair where the value is a floating point number.
 * The float is formatted to 2 decimal places.
 */
void append_json_float_pair(char **json, const char *key, double value);

#endif
