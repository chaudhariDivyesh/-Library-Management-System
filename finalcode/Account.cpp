// Account.cpp - Implementation file for Account class
#include "Account.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor
Account::Account() {}

// Get borrowed books
vector<Book*>& Account::getBorrowedBooks() {
    return borrowedBooks;
}

// Get borrowing history
vector<tuple<string, string, string>>& Account::getHistory() {
    return history;
}

// Get overdue records
vector<tuple<string, string, string, int, int>>& Account::getBookOverdue() {
    return bookOverdue;
}

// Get payment history (constant reference)
const vector<tuple<string, string, string, string, int, int>>& Account::getPaymentHistory() const {
    return paymentHistory;
}

// Get total payment amount (summing payment amounts)
int Account::getTotalPayment() const {
    int total = 0;
    for (const auto &record : paymentHistory) {
        total += get<4>(record);
    }
    return total;
}

// Get total number of borrowed books
int Account::totalBorrowedBooks() const {
    return borrowedBooks.size();
}

// Get total remaining fine from overdue records
int Account::getTotalRemainingFine() const {
    int totalRemainingFine = 0;
    for (const auto &record : bookOverdue) {
        totalRemainingFine += get<4>(record);
    }
    return totalRemainingFine;
}

// Set payment history
void Account::setPaymentHistory(const vector<tuple<string, string, string, string, int, int>>& newHistory) {
    paymentHistory = newHistory;
}

// Set overdue records
void Account::setBookOverdue(const vector<tuple<string, string, string, int, int>>& overdueRecords) {
    bookOverdue = overdueRecords;
}

// Add a payment record
void Account::addPaymentRecord(const string &isbn, const string &borrowDate, const string &returnDate, const string &paymentDate, int paymentAmount, int remainingAmount) {
    paymentHistory.push_back(make_tuple(isbn, borrowDate, returnDate, paymentDate, paymentAmount, remainingAmount));
}

// Add an overdue record
void Account::addBookOverdueRecord(const string &isbn, const string &borrowDate, const string &returnDate, int totalFine, int remainingFine) {
    bookOverdue.push_back(make_tuple(isbn, borrowDate, returnDate, totalFine, remainingFine));
}

// Add a history record
void Account::addHistoryRecord(const tuple<string, string, string>& rec) {
    history.push_back(rec);
}

// Public helper: Check if a book is already borrowed.
bool Account::hasBorrowedBook(Book* book) const {
    return (find(borrowedBooks.begin(), borrowedBooks.end(), book) != borrowedBooks.end());
}

// Add a book to the borrowedBooks vector.
void Account::addToBorrowedBooks(Book* book) {
    borrowedBooks.push_back(book);
}

// Update history with a new record using current date.
void Account::updateHistory(Book* book, const string &action) {
    history.push_back(make_tuple(book->getTitle(), getCurrentDate(), action));
    cout << "Book \"" << book->getTitle() << "\" " << action << " on " << getCurrentDate() << ".\n";
}

// Calculate overdue days for a given book.
int Account::overdueDaysPerBook(Book* book, int maxDays) const {
    int overdue = book->daysBorrowed() - maxDays;
    return (overdue <= 0) ? 0 : overdue;
}

// Check if a book is overdue based on the limit.
bool Account::isBookOverdue(Book* book, int overdueLimit) const {
    return (book->daysBorrowed() > overdueLimit);
}

// *** Missing functions added below ***

// Checks if any borrowed book is overdue based on the given limit.
bool Account::checkOverdue(int overdueLimit) {
    for (Book* book : borrowedBooks) {
        if (isBookOverdue(book, overdueLimit)) {
            return true;
        }
    }
    return false;
}

// Returns a vector of borrowed books that are overdue.
vector<Book*>& Account::getCurrOverdueBooks(int overdueLimit) {
    static vector<Book*> overdueBooks;
    overdueBooks.clear();
    for (Book* book : borrowedBooks) {
        if (isBookOverdue(book, overdueLimit)) {
            overdueBooks.push_back(book);
        }
    }
    return overdueBooks;
}

// Borrow a book: adds the book to borrowedBooks and updates history if not already borrowed.
bool Account::borrowBook(Book* book) {
    if (book->isAvailable() == false) {
        cout<<book->getStatus()<<endl;
        cout << "xBook already borrowed!\n";
        return false;
    }
    if (!hasBorrowedBook(book)) {
        addToBorrowedBooks(book);
        updateHistory(book, "Borrowed");
        return true;
    }
    return false;
}

// Process returning a book: removes the book from borrowedBooks and calls its return function.
void Account::processReturnBook(Book* book) {
    book->returnBook();
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    }
}

// Return a book: if overdue, calculates fine and adds an overdue record; then updates history.
void Account::returnBook(Book* book, int maxDays, int finePerDay) {
    if (isBookOverdue(book, maxDays)) {
        int fineOnBook = overdueDaysPerBook(book, maxDays) * finePerDay;
        addBookOverdueRecord(book->getISBN(), stringifyTime(book->getBorrowTime()), getCurrentDate(), fineOnBook, fineOnBook);
    }
    processReturnBook(book);
    history.push_back(make_tuple(book->getTitle(), getCurrentDate(), "Returned"));
}

// Get current fine on currently borrowed books.
int Account::getCurrFine(int finePerDay, int maxDays) {
    int currFine = 0;
    for (auto* book : borrowedBooks) {
        int overdueDays = overdueDaysPerBook(book, maxDays);
        currFine += overdueDays * finePerDay;
    }
    return currFine;
}

// Get total fine: current fine plus previously recorded overdue fines.
int Account::getFine(int finePerDay, int maxDays) {
    int currFine = getCurrFine(finePerDay, maxDays);
    int prevFine = getTotalRemainingFine();
    return currFine + prevFine;
}

// Pay fine for a currently borrowed book.
void Account::payFineForCurrentBook(Book* book, int currentFinePayment, int maxDays, int finePerDay) {
    int overdueDays = overdueDaysPerBook(book, maxDays);
    int totalFine = overdueDays * finePerDay;
    if (overdueDays <= 0) {
        cout << "No fine on this book. It is not overdue.\n";
        return;
    }
    //Fcout<<totalFine<<" "<<currentFinePayment<<endl;
    int remainingFine;
    // if (remainingFine < 0) remainingFine = 0;
    if(totalFine<currentFinePayment){
        //cout<<"xyz"<<endl;
        int change=currentFinePayment-totalFine;
        currentFinePayment=totalFine;
        remainingFine = 0;
        cout<<"Finepayment is greater than Fine on Book"<<endl;
        cout<<"You have paid:"<<currentFinePayment<<endl;
        cout<<"Your change is:"<<change<<endl;
    }
    else{
        remainingFine =totalFine-currentFinePayment;  
    } 
    addPaymentRecord(book->getISBN(), stringifyTime(book->getBorrowTime()), getCurrentDate(), getCurrentDate(), currentFinePayment, remainingFine);
    if (remainingFine > 0) {
        addBookOverdueRecord(book->getISBN(), stringifyTime(book->getBorrowTime()), getCurrentDate(), totalFine, remainingFine);
    }
    cout << "Fine paid: " << currentFinePayment << ". ";
    if (remainingFine > 0) {
        cout << "Remaining fine: " << remainingFine << ". Book is returned and fine is recorded.\n";
    } else {
        cout << "No remaining fine. Book is returned successfully.\n";
    }
    processReturnBook(book);
    history.push_back(make_tuple(book->getTitle(), getCurrentDate(), "Returned"));
}

// Pay fine for a past overdue book (not currently borrowed).
void Account::payFineForPastOverdueBook(const string &isbn, int currentFinePayment) {
    for (auto &record : bookOverdue) {
        if (get<0>(record) == isbn) {
            int remainingFine = get<4>(record);
            if (remainingFine == 0) {
                cout << "This book has no remaining fine.\n";
                return;
            }
            if(remainingFine<currentFinePayment){
                int change=currentFinePayment-remainingFine;
                currentFinePayment=remainingFine;
                remainingFine = 0;
                cout<<"Finepayment is greater than Fine on Book"<<endl;
                cout<<"You have paid:"<<currentFinePayment<<endl;
                cout<<"Your change is:"<<change<<endl;
            }
            else{
                remainingFine -= currentFinePayment;
                
            } 
            get<4>(record) = remainingFine;
            addPaymentRecord(isbn, get<1>(record), get<2>(record), getCurrentDate(), currentFinePayment, remainingFine);
            cout << "Fine payment successful. Remaining fine: " << remainingFine << "\n";
            return;
        }
    }
    cout << "Error: No fine record found for this book.\n";
}

// Determine fine payment method based on whether the book is currently borrowed.
void Account::finePay(const string &isbn, int currentFinePayment, int maxDays, int finePerDay) {
    for (Book* book : borrowedBooks) {
        if (book->getISBN() == isbn) {
            payFineForCurrentBook(book, currentFinePayment, maxDays, finePerDay);
            return;
        }
    }
    payFineForPastOverdueBook(isbn, currentFinePayment);
}

// Update overdue record after a fine payment.
void Account::updateBookOverdueAfterFinePayment(const string &isbn, int currentFinePayment) {
    for (auto &record : bookOverdue) {
        if (get<0>(record) == isbn) {
            int remainingFine = get<4>(record) - currentFinePayment;
            if (remainingFine < 0) remainingFine = 0;
            get<4>(record) = remainingFine;
            break;
        }
    }
}

// Display overdue records and currently overdue books.
void Account::displayOverdueBooks(int maxDays, int finePerDay) {
    // Define column widths
    const int isbnWidth = 20;       // Increased width for long ISBNs
    const int borrowDateWidth = 25; // Standard width for dates
    const int returnDateWidth = 25; // Standard width for return dates
    const int overdueDaysWidth = 15;
    const int fineWidth = 15;

    // Display overdue records for returned books
    cout << "\nOverdue Books (Returned):\n";
    cout << left << setw(isbnWidth) << "ISBN"
         << setw(borrowDateWidth) << "Borrow Date"
         << setw(returnDateWidth) << "Return Date"
         << setw(fineWidth) << "Total Fine"
         << setw(fineWidth) << "Remaining Fine"
         << endl;
    cout << string(isbnWidth + borrowDateWidth + returnDateWidth + fineWidth * 2, '-') << endl;

    for (auto it = bookOverdue.begin(); it != bookOverdue.end();) {
        string isbn = get<0>(*it);
        string borrowDate = get<1>(*it);
        string returnDate = get<2>(*it);
        int totalFine = get<3>(*it);
        int remainingFine = get<4>(*it);

        if (remainingFine == 0) {
            it = bookOverdue.erase(it);
        } else {
            cout << left << setw(isbnWidth) << isbn
                 << setw(borrowDateWidth) << borrowDate
                 << setw(returnDateWidth) << returnDate
                 << setw(fineWidth) << totalFine
                 << setw(fineWidth) << remainingFine
                 << endl;
            ++it;
        }
    }

    // Display overdue info for currently borrowed books
    cout << "\nOverdue Books (Currently Borrowed):\n";
    cout << left << setw(isbnWidth) << "ISBN"
         << setw(borrowDateWidth) << "Borrow Date"
         << setw(overdueDaysWidth) << "Overdue Days"
         << setw(fineWidth) << "Fine"
         << endl;
    cout << string(isbnWidth + borrowDateWidth + overdueDaysWidth + fineWidth, '-') << endl;

    for (Book* book : borrowedBooks) {
        int overdueDays = overdueDaysPerBook(book, maxDays);
        if (overdueDays > 0) {
            int fineOnBook = overdueDays * finePerDay;

            cout << left << setw(isbnWidth) << book->getISBN()
                 << setw(borrowDateWidth) << stringifyTime(book->getBorrowTime())
                 << setw(overdueDaysWidth) << overdueDays
                 << setw(fineWidth) << fineOnBook
                 << endl;
        }
    }
}


// Display borrowing history.
void Account::displayHistory() {
    if (history.empty()) {
        cout << "No borrowing history available.\n";
        return;
    }

    // Define column widths
    const int titleWidth = 40;  // Increased to accommodate long book titles
    const int dateWidth = 25;   // Increased for better readability
    const int actionWidth = 15; // Standard width for action column

    // Print table header
    cout << left << setw(titleWidth) << "Book Title"
         << setw(dateWidth) << "Date"
         << setw(actionWidth) << "Action" << endl;
    cout << string(titleWidth + dateWidth + actionWidth, '-') << endl;

    // Print history entries
    for (const auto &entry : history) {
        cout << left << setw(titleWidth) << get<0>(entry)   // Book Title
             << setw(dateWidth) << get<1>(entry)           // Date
             << setw(actionWidth) << get<2>(entry) << endl;  // Action
    }
}

// Display payment history.
void Account::displayPaymentHistory() const {
    if (paymentHistory.empty()) {
        cout << "No payment history available.\n";
        return;
    }

    // Define column widths
    const int isbnWidth = 15;
    const int borrowDateWidth = 25;
    const int returnDateWidth = 25;
    const int paymentDateWidth = 25;
    const int paidAmountWidth = 15;
    const int remainingAmountWidth = 20;

    // Print table header
    cout << "\nPayment History:\n";
    cout << left << setw(isbnWidth) << "ISBN"
         << setw(borrowDateWidth) << "Borrow Date"
         << setw(returnDateWidth) << "Return Date"
         << setw(paymentDateWidth) << "Payment Date"
         << setw(paidAmountWidth) << "Paid Amount"
         << setw(remainingAmountWidth) << "Remaining Amount"
         << endl;
    cout << string(isbnWidth + borrowDateWidth + returnDateWidth + paymentDateWidth + paidAmountWidth + remainingAmountWidth, '-') << endl;

    // Print payment history records
    for (const auto &record : paymentHistory) {
        cout << left << setw(isbnWidth) << get<0>(record)      // ISBN
             << setw(borrowDateWidth) << get<1>(record)       // Borrow Date
             << setw(returnDateWidth) << get<2>(record)       // Return Date
             << setw(paymentDateWidth) << get<3>(record)      // Payment Date
             << setw(paidAmountWidth) << get<4>(record)       // Paid Amount
             << setw(remainingAmountWidth) << get<5>(record)  // Remaining Amount
             << endl;
    }
}

