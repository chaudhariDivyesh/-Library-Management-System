// User.h - Header file for User abstract base class
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Account.h"
#include "Book.h"
#include "Utils.h"  // For getCurrentDate() and stringifyTime()

using namespace std;

/**
 * @class User
 * @brief Abstract base class representing a library user.
 *
 * This class defines the common attributes and operations for a user in the library
 * system, including account management, borrowing, returning, and fine payment.
 */
class User {
protected:
    string name;       ///< User's name.
    string role;       ///< User's role (e.g., Student, Faculty).
    string userID;     ///< Unique identifier for the user.
    string password;   ///< User's password.

    Account userAccount;   ///< Associated account for managing borrowed books, fines, and history.

public:
    /**
     * @brief Constructs a User object.
     * @param name User's name.
     * @param role User's role.
     * @param userID Unique user identifier.
     * @param password User's password.
     */
    User(string name, string role, string userID, string password);

    // Pure virtual functions (must be implemented by derived classes)
    virtual int getMaxBorrowingPeriod() = 0;
    virtual int getMaxAllowedBooks() = 0;
    virtual int getFinePerDay() = 0;
    virtual int getOverdueLimit() = 0;
    virtual bool canBorrowBook(Book* book) = 0;
    virtual void displayCurrBorrowedBooks() = 0;

    /**
     * @brief Retrieves the associated Account object.
     * @return Reference to the user's Account.
     */
    Account& getAccount();

    /**
     * @brief Gets the user's name.
     * @return The user's name.
     */
    string getName();

    /**
     * @brief Gets the user's role.
     * @return The user's role.
     */
    string getRole();

    /**
     * @brief Gets the user's unique identifier.
     * @return The userID.
     */
    string getUserID();

    /**
     * @brief Gets the user's password.
     * @return The password.
     */
    string getPassword();

    /**
     * @brief Displays the user's borrowing history.
     */
    void displayHistory();

    /**
     * @brief Checks whether the user has any overdue books.
     * @return true if there are overdue books; false otherwise.
     */
    bool hasOverdue();
    /**
     * @brief Checks whether the user has any overdue books.
     * @return true if there are overdue books; false otherwise.
     */
    bool hasBorrowedBook(Book* book);

    /**
     * @brief Retrieves the current number of borrowed books.
     * @param book Pointer to the Book to be borrowed.
     * @return The number of currently borrowed books.
     */
    int getCurrBorrowedBook();

    /**
     * @brief Calculates the total fine for the user.
     * @return The total fine amount.
     */
    int getFine();

    /**
     * @brief Determines if the user has any pending dues (fine > 0).
     * @return true if pending dues exist; false otherwise.
     */
    bool hasPendingDues();

    /**
     * @brief Checks if the user has reached the maximum allowed number of borrowed books.
     * @return true if maximum is reached; false otherwise.
     */
    bool hasReachedMaxBorrowedBooks();

    /**
     * @brief Retrieves a list of overdue books.
     * @return A vector of pointers to overdue Book objects.
     */
    vector<Book*>& getOverdueBooks();

    /**
     * @brief Attempts to borrow a book.
     * @param book Pointer to the Book to be borrowed.
     */
    void borrowBook(Book* book);

    /**
     * @brief Returns a borrowed book.
     * @param book Pointer to the Book to be returned.
     */
    void returnBook(Book* book);

    /**
     * @brief Processes the fine payment for a given book.
     * @param isbn The ISBN of the book.
     * @param amount The payment amount.
     */
    void payFine(string isbn, int amount);
};

#endif // USER_H
