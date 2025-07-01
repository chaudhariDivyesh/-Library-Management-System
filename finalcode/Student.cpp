// Student.cpp - Implementation file for Student class
#include "Student.h"
#include "Utils.h"     // For stringifyTime() and getCurrentDate()
#include "Account.h"
#include "Book.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// Constructor: Initializes a Student using the User base class constructor.
Student::Student(string name, string userID, string password) : User(name, "student", userID, password) {}

// Returns the maximum borrowing period for a student.
int Student::getMaxBorrowingPeriod() {
    return maxBorrowingPeriod;
}

// Returns the maximum allowed books for a student.
int Student::getMaxAllowedBooks() {
    return maxAllowedBooks;
}

// Returns the fine per day for a student.
int Student::getFinePerDay() {
    return finePerDay;
}

// Returns the overdue limit for a student.
int Student::getOverdueLimit() {
    return overdueDaysLimit;
}

// Calculates the fine for a specific book.
int Student::getFineOfBook(Book* book) {
    int overdueDays = book->daysBorrowed() - getMaxBorrowingPeriod();
    return (overdueDays > 0) ? (overdueDays * getFinePerDay()) : 0;
}

// Displays the list of overdue books.
void Student::displayOverdueBooks() {
    if (hasPendingDues()) {
        // Use the account's display function.
        getAccount().displayOverdueBooks(getOverdueLimit(), getFinePerDay());
        // display total fine:
        cout<<"Total Fine: "<<getFine()<<endl;
    } else {
        cout << "No overdue books.\n";
    }
}

// Checks if a student can borrow the specified book.
bool Student::canBorrowBook(Book* book) {
    if (hasReachedMaxBorrowedBooks()) {
        cout << "You have borrowed max books.\n";
        return false;
    } else if (hasPendingDues()) {
        cout << "You have not paid fine.\n";
        displayOverdueBooks();
        return false;
    } else {
        return true;
    }
}

// Displays the currently borrowed books in a table format.
void Student::displayCurrBorrowedBooks() {
    int maxDays = getMaxBorrowingPeriod();
    int finePerDayVal = getFinePerDay();
    Account &acc = getAccount();
    vector<Book*> borrowedBooks = acc.getBorrowedBooks();

    if (borrowedBooks.empty()) {
        cout << "No currently borrowed books.\n";
        return;
    }

    // Define column widths
    const int titleWidth = 40;   // Increased for longer book titles
    const int isbnWidth = 20;    // Increased to accommodate longer ISBNs
    const int dateWidth = 25;    // Ensures proper date alignment
    const int overdueWidth = 15; // Added more space for clarity
    const int fineWidth = 10;    // Standard fine column width

    // Print table header
    cout << "Currently Borrowed Books:\n";
    cout << left << setw(titleWidth) << "Title"
         << setw(isbnWidth) << "ISBN"
         << setw(dateWidth) << "Borrow Date"
         << setw(overdueWidth) << "Overdue Days"
         << setw(fineWidth) << "Fine"
         << endl;
    cout << string(titleWidth + isbnWidth + dateWidth + overdueWidth + fineWidth, '-') << endl;

    // Display each borrowed book
    for (Book* book : borrowedBooks) {
        int overdueDays = book->daysBorrowed() - maxDays;
        overdueDays = max(0, overdueDays); // Ensure non-negative
        int fine = overdueDays * finePerDayVal;

        cout << left << setw(titleWidth) << book->getTitle()
             << setw(isbnWidth) << book->getISBN()
             << setw(dateWidth) << stringifyTime(book->getBorrowTime())
             << setw(overdueWidth) << overdueDays
             << setw(fineWidth) << fine
             << endl;
    }
}

// Displays the payment history.
void Student::displayPaymentHistory() {
    getAccount().displayPaymentHistory();
}
