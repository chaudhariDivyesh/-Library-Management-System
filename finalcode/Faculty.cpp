// Faculty.cpp - Implementation file for Faculty class
#include "Faculty.h"
#include "Utils.h"     // For stringifyTime() and getCurrentDate()
#include "Account.h"
#include "Book.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// Constructor: Initializes a Faculty using the User base class constructor.
Faculty::Faculty(string name, string userID, string password) : User(name, "faculty", userID, password) {}

// Returns the maximum borrowing period for a faculty member.
int Faculty::getMaxBorrowingPeriod() {
    return maxBorrowingPeriod;
}

// Returns the maximum allowed books for a faculty member.
int Faculty::getMaxAllowedBooks() {
    return maxAllowedBooks;
}

// Returns the fine per day for a faculty member.
int Faculty::getFinePerDay() {
    return finePerDay;
}

// Returns the overdue limit for a faculty member.
int Faculty::getOverdueLimit() {
    return overdueDaysLimit;
}

// Calculates the overdue days for a specific book.
int Faculty::getOverdueOfBook(Book* book) {
    int overdue = book->daysBorrowed() - getOverdueLimit();
    return (overdue < 0) ? 0 : overdue;
}

// Displays the list of overdue books for the faculty member.
void Faculty::displayOverdueBooks() {
    if (hasOverdue()) {
        cout << "Books with pending dues:\n";
        cout << setw(25) << left << "Title"
             << setw(25) << left << "ISBN"
             << setw(25) << left << "Borrow Date & Time"
             << setw(25) << left << "Overdue Days"
             << endl;
        cout << "---------------------------------------------------------------\n";
        vector<Book*> books = getOverdueBooks();
        for (auto* book : books) {
            int overdueDays = getOverdueOfBook(book);
            if (overdueDays > 0) {
                cout << setw(25) << left << book->getTitle()
                     << setw(25) << left << book->getISBN()
                     << setw(25) << left << stringifyTime(book->getBorrowTime())
                     << setw(25) << left << overdueDays
                     << endl;
            }
        }
    } else {
        cout << "No overdue books.\n";
    }
}

// Displays the currently borrowed books for the faculty member.
void Faculty::displayCurrBorrowedBooks() {
    int maxDays = getMaxBorrowingPeriod();
    Account &acc = getAccount();
    vector<Book*> borrowedBooks = acc.getBorrowedBooks();

    if (borrowedBooks.empty()) {
        cout << "No currently borrowed books.\n";
        return;
    }

    // Define column widths
    const int titleWidth = 40;   // Increased for long book titles
    const int isbnWidth = 20;    // Increased for long ISBNs
    const int dateWidth = 25;    // Ensures proper date alignment
    const int overdueWidth = 15; // Added more space for clarity

    // Print table header
    cout << "Currently Borrowed Books:\n";
    cout << left << setw(titleWidth) << "Title"
         << setw(isbnWidth) << "ISBN"
         << setw(dateWidth) << "Borrow Date"
         << setw(overdueWidth) << "Overdue Days"
         << endl;
    cout << string(titleWidth + isbnWidth + dateWidth + overdueWidth, '-') << endl;

    // Display each borrowed book
    for (Book* book : borrowedBooks) {
        int overdueDays = book->daysBorrowed() - maxDays;
        overdueDays = max(0, overdueDays); // Ensure non-negative

        cout << left << setw(titleWidth) << book->getTitle()
             << setw(isbnWidth) << book->getISBN()
             << setw(dateWidth) << stringifyTime(book->getBorrowTime())
             << setw(overdueWidth) << overdueDays
             << endl;
    }
}

// Checks if a faculty member can borrow a book.
bool Faculty::canBorrowBook(Book* book) {
    if (hasReachedMaxBorrowedBooks()) {
        cout << "You have borrowed max books.\n";
        return false;
    } else if (hasPendingDues()) {
        cout << "You have pending dues.\n";
        displayOverdueBooks();
        return false;
    } else {
        return true;
    }
}
