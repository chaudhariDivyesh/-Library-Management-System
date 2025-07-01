// DataSaver.h - Header file for CSV data saving functions
#ifndef DATA_SAVER_H
#define DATA_SAVER_H

#include "LibraryManagement.h"  // Ensures LibraryManagement, Book, and User are declared.
#include "Utils.h"              // For stringifyTime()
#include <string>

using namespace std;

/**
 * @brief Saves the list of books to a CSV file.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void saveBooksToCSV(LibraryManagement* library, const string &filename);

/**
 * @brief Saves student data to a CSV file.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void saveStudentsToCSV(LibraryManagement* library, const string &filename);

/**
 * @brief Saves faculty data to a CSV file.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void saveFacultyToCSV(LibraryManagement* library, const string &filename);

/**
 * @brief Saves librarian data to a CSV file.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void saveLibrariansToCSV(LibraryManagement* library, const string &filename);

/**
 * @brief Saves the book history to a CSV file.
 * @param library Pointer to the LibraryManagement object.
 * @param filename The CSV file path.
 */
void saveBookHistoryToCSV(LibraryManagement* library, const string &filename);

/**
 * @brief Saves all user data (students, faculty, librarians) to CSV files.
 * @param library Pointer to the LibraryManagement object.
 */
void saveAllUsersToCSV(LibraryManagement* library);

/**
 * @brief Saves all data (books, users, and book history) to CSV files.
 * @param library Pointer to the LibraryManagement object.
 */
void saveAllData(LibraryManagement* library);

/**
 * @brief A convenience function that saves all data.
 * @param library Pointer to the LibraryManagement object.
 */
void saveFile(LibraryManagement* library);

/**
 * @brief Clears the contents of the specified CSV file.
 * @param filename The CSV file path.
 */
void clearCSV(const string &filename);

#endif // DATA_SAVER_H
