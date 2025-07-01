// Account.h - Header file for Account class
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Book.h"
#include "Utils.h"  // For getCurrentDate() and stringifyTime()
#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * @class Account
 * @brief Represents a library account managing borrowed books, overdue records, and payment history.
 */
class Account {
private:
    vector<Book*> borrowedBooks;                           ///< Vector of borrowed books.
    vector<tuple<string, string, string>> history;         ///< History records: {Book Title, Date, Action}.
    vector<tuple<string, string, string, int, int>> bookOverdue;  ///< Overdue records: {ISBN, BorrowDate, ReturnDate, TotalFine, RemainingFine}.
    vector<tuple<string, string, string, string, int, int>> paymentHistory; ///< Payment history: {ISBN, BorrowDate, ReturnDate, PaymentDate, PaymentAmount, RemainingAmount}.

    /**
     * @brief Checks if a given book is overdue.
     * @param book Pointer to the Book.
     * @param overdueLimit Overdue limit in minutes/days.
     * @return true if overdue, false otherwise.
     */
    bool isBookOverdue(Book* book, int overdueLimit) const;

    /**
     * @brief Calculates the number of overdue days for a given book.
     * @param book Pointer to the Book.
     * @param maxDays Maximum allowed days before fine applies.
     * @return Number of overdue days (0 if not overdue).
     */
    int overdueDaysPerBook(Book* book, int maxDays) const;

    /**
     * @brief Updates the history with a new record for the given action.
     * @param book Pointer to the Book.
     * @param action The action performed (e.g., "Borrowed" or "Returned").
     */
    void updateHistory(Book* book, const string &action);

public:
    /// @brief Constructs an Account object.
    Account();

    // Getters for member variables:
    vector<Book*>& getBorrowedBooks();
    vector<tuple<string, string, string>>& getHistory();
    vector<tuple<string, string, string, int, int>>& getBookOverdue();
    const vector<tuple<string, string, string, string, int, int>>& getPaymentHistory() const;
    int getTotalPayment() const;
    int totalBorrowedBooks() const;
    int getTotalRemainingFine() const;
    bool checkOverdue(int overdueLimit);
    vector<Book*>& getCurrOverdueBooks(int overdueLimit);

    // Setters:
    void setPaymentHistory(const vector<tuple<string, string, string, string, int, int>>& newHistory);
    void setBookOverdue(const vector<tuple<string, string, string, int, int>>& overdueRecords);

    // Record addition:
    void addPaymentRecord(const string &isbn, const string &borrowDate, const string &returnDate, const string &paymentDate, int paymentAmount, int remainingAmount);
    void addBookOverdueRecord(const string &isbn, const string &borrowDate, const string &returnDate, int totalFine, int remainingFine);
    void addHistoryRecord(const tuple<string, string, string>& rec);

    // Book operations:
    bool borrowBook(Book* book);
    void addToBorrowedBooks(Book* book);
    void processReturnBook(Book* book);
    void returnBook(Book* book, int maxDays, int finePerDay);

    // Fine handling:
    int getCurrFine(int finePerDay, int maxDays);
    int getFine(int finePerDay, int maxDays);
    void payFineForCurrentBook(Book* book, int currentFinePayment, int maxDays, int finePerDay);
    void payFineForPastOverdueBook(const string &isbn, int currentFinePayment);
    void finePay(const string &isbn, int currentFinePayment, int maxDays, int finePerDay);
    void updateBookOverdueAfterFinePayment(const string &isbn, int currentFinePayment);

    // Display functions:
    void displayOverdueBooks(int maxDays, int finePerDay);
    void displayHistory();
    void displayPaymentHistory() const;

    // Public helper: Checks if the specified book is already borrowed.
    bool hasBorrowedBook(Book* book) const;
};

#endif // ACCOUNT_H
