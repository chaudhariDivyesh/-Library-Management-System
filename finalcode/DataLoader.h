// DataLoader.h - Header file for CSV data loading functions
#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "LibraryManagement.h"
#include <string>

using namespace std;

/**
 * @brief Loads books from a CSV file into the library.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void loadBooksFromCsv(LibraryManagement* library, const string &filename);

/**
 * @brief Loads student data from a CSV file into the library.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void loadStudentsFromCsv(LibraryManagement* library, const string &filename);

/**
 * @brief Loads faculty data from a CSV file into the library.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void loadFacultyFromCsv(LibraryManagement* library, const string &filename);

/**
 * @brief Loads librarian data from a CSV file into the library.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void loadLibrariansFromCsv(LibraryManagement* library, const string &filename);

/**
 * @brief Loads book history from a CSV file.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void loadBookHistoryFromCsv(LibraryManagement* library, const string &filename);

/**
 * @brief Loads all user data (students, faculty, librarians) from their CSV files.
 * @param library Pointer to the LibraryManagement object.
 */
void loadAllUsersFromCsv(LibraryManagement* library);

/**
 * @brief Loads all library data (books, users, and book history) from CSV files.
 * @param library Pointer to the LibraryManagement object.
 */
void loadAllData(LibraryManagement* library);

/**
 * @brief Loads all data by calling loadAllData.
 * @param library Pointer to the LibraryManagement object.
 */
void loadFile(LibraryManagement* library);

#endif // DATA_LOADER_H
