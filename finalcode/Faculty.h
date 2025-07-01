// Faculty.h - Header file for Faculty class
#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

/**
 * @class Faculty
 * @brief Represents a faculty user in the library system.
 */
class Faculty : public User {
public:
    static const int maxAllowedBooks = 5;         ///< Maximum number of books a faculty member can borrow.
    static const int maxBorrowingPeriod = 1;        ///< Maximum borrowing period (e.g., in days).
    static const int overdueDaysLimit = 1;          ///< Overdue days limit.
    static const int finePerDay = 0;                ///< Fine per day (faculty members have no fine).

    /**
     * @brief Constructs a Faculty object.
     * @param name Faculty member's name.
     * @param userID Faculty member's unique identifier.
     * @param password Faculty member's password.
     */
    Faculty(string name, string userID, string password);

    // Override pure virtual functions from User
    int getMaxBorrowingPeriod() override;
    int getMaxAllowedBooks() override;
    int getFinePerDay() override;
    int getOverdueLimit() override;
    bool canBorrowBook(Book* book) override;
    void displayCurrBorrowedBooks() override;

    /**
     * @brief Calculates the overdue days for a specific book.
     * @param book Pointer to the Book.
     * @return Overdue days (0 if not overdue).
     */
    int getOverdueOfBook(Book* book);

    /**
     * @brief Displays the list of overdue books.
     */
    void displayOverdueBooks();
};

#endif // FACULTY_H
