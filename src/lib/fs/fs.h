
#ifndef FS_H
#define FS_H

#include "../vars.h"

void create_directory_if_not_exists(const char *path);
char *get_data_directory();
char *get_full_path(const char *filename);
void write_to_file(const char *filename, const char *content);
int create_file_if_not_exists(const char *path);

/**
 * @brief Checks if the configured data directory exists
 * @return 1 if directory exists, 0 otherwise
 */
int data_dir_exists();

/**
 * @brief Checks if a directory exists within the data directory
 * @param dirname Name of directory to check for
 * @return 1 if directory exists, 0 otherwise
 */
int data_dir_has_dir(const char *dirname);

/**
 * @brief Checks if a file exists within a directory
 * @param dir_path Path to directory to search in
 * @param filename Name of file to look for
 * @return 1 if file exists, 0 otherwise
 */
int dir_has_file(char *dir_path, char *filename);

/**
 * @brief Creates the data directory if it doesn't exist
 * @return 1 if directory was created, 0 if it already existed
 */
int create_data_dir();

/**
 * @brief Creates a directory within the data directory
 * @param dirname Name of directory to create
 * @return 1 if directory was created, 0 if it already existed
 */
int create_dir_in_data(const char *dirname);

/**
 * @brief Creates a file within a directory
 * @param dirname Path to directory where file should be created
 * @param filename Name of file to create
 * @return 1 if file was created, 0 if it already existed
 */
int create_file(char *dirname, char *filename);

/**
 * @brief Creates a path string by joining two strings with a separator
 * @param str1 First part of the path
 * @param str2 Second part of the path
 * @return Newly allocated string containing joined path, or NULL on error
 */
char *create_path(const char *str1, const char *str2);

/**
 * @brief Sets up the initial data directory structure and files
 *
 * Creates the main data directory if it doesn't exist, then creates subdirectories
 * for inventory, order and supplier data. Also creates a metadata file in each
 * subdirectory.
 *
 * @return 0 on success
 */
int setup_data_files();

#endif
