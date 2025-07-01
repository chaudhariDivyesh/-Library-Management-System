// Librarian.h - Header file for Librarian class
#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include "LibraryManagement.h"
#include "Book.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * @class Librarian
 * @brief Represents a librarian user in the library system.
 *
 * Librarians can add or remove books and users, reserve/dereserve books,
 * and update book information.
 */
class Librarian : public User {
public:
    /**
     * @brief Constructs a Librarian object.
     * @param name Librarian's name.
     * @param userID Librarian's unique identifier.
     * @param password Librarian's password.
     */
    Librarian(string name, string userID, string password);

    // Override pure virtual functions from User (librarian does not borrow books).
    int getMaxBorrowingPeriod() override;
    int getMaxAllowedBooks() override;
    int getFinePerDay() override;
    int getOverdueLimit() override;
    bool canBorrowBook(Book* book) override;
    void displayCurrBorrowedBooks() override;

    /**
     * @brief Adds a new book to the library.
     * @param library Reference to the LibraryManagement object.
     * @param title Title of the book.
     * @param author Author of the book.
     * @param publisher Publisher of the book.
     * @param year Publication year.
     * @param ISBN ISBN of the book.
     */
    void addBook(LibraryManagement &library, string title, string author, string publisher, int year, string ISBN);

    /**
     * @brief Reserves a book.
     * @param book Pointer to the Book to reserve.
     */
    void reserveBook(Book* book);

    /**
     * @brief Dereserves a book (sets its status to available).
     * @param book Pointer to the Book to dereserve.
     */
    void deReserveBook(Book* book);

    /**
     * @brief Removes a book from the library.
     * @param library Reference to the LibraryManagement object.
     * @param ISBN ISBN of the book to remove.
     */
    void removeBook(LibraryManagement &library, string ISBN);

    /**
     * @brief Adds a new user to the library.
     * @param library Reference to the LibraryManagement object.
     * @param name Name of the user.
     * @param role Role of the user ("student", "faculty", or "librarian").
     * @param userID Unique user identifier.
     * @param password Password.
     */
    void addUser(LibraryManagement &library, string name, string role, string userID, string password);

    /**
     * @brief Removes a user from the library.
     * @param library Reference to the LibraryManagement object.
     * @param userID The user ID of the user to remove.
     */
    void removeUser(LibraryManagement &library, string userID);

    /**
     * @brief Updates the details of a book.
     * @param library Reference to the LibraryManagement object.
     * @param ISBN ISBN of the book to update.
     * @param attribute The attribute to update.
     * @param val The new value for the attribute.
     */
    void updateBook(LibraryManagement &library, string ISBN, string attribute, string val);
};

#endif // LIBRARIAN_H
