// User.cpp - Implementation file for User abstract base class
#include "User.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor: initializes user details.
User::User(string name, string role, string userID, string password) {
    this->name = name;
    this->role = role;
    this->userID = userID;
    this->password = password;
}

// Returns the associated account.
Account& User::getAccount() {
    return userAccount;
}

// Returns the user's name.
string User::getName() {
    return name;
}

// Returns the user's role.
string User::getRole() {
    return role;
}

// Returns the user's unique identifier.
string User::getUserID() {
    return userID;
}

// Returns the user's password.
string User::getPassword() {
    return password;
}

// Displays the borrowing history by invoking the account's displayHistory().
void User::displayHistory() {
    userAccount.displayHistory();
}

// Checks if the user has any overdue books.
bool User::hasOverdue() {
    return userAccount.checkOverdue(getOverdueLimit());
}

// Returns the number of currently borrowed books.
int User::getCurrBorrowedBook() {
    return userAccount.totalBorrowedBooks();
}

// Calculates the total fine: current fine plus previous overdue fines.
int User::getFine() {
    return userAccount.getFine(getFinePerDay(), getMaxBorrowingPeriod());
}

// Returns true if the user has pending fines.
bool User::hasPendingDues() {
    return getFine() > 0;
}
// check if user has Borrowed Books
bool User::hasBorrowedBook(Book* book){
    return userAccount.hasBorrowedBook(book);
}
// Checks if the user has reached the maximum allowed borrowed books.
bool User::hasReachedMaxBorrowedBooks() {
    return getCurrBorrowedBook() >= getMaxAllowedBooks();
}

// Retrieves the list of overdue books.
vector<Book*>& User::getOverdueBooks() {
    return userAccount.getCurrOverdueBooks(getOverdueLimit());
}

// Attempts to borrow a book.
// Checks if the user is allowed to borrow and if the book is available.
void User::borrowBook(Book* book) {
    if (!canBorrowBook(book)) {
        cout << "Cannot borrow this book.\n";
        return;
    }
    if (!book->isAvailable()) {
        if (book->isReserved()) {
            cout << "This book is reserved and cannot be borrowed.\n";
        } else {
            cout << "This book is not available.\n";
        }
    } else {
        //cout<<"x";
        // Borrow the book and update the account history.
        
        userAccount.borrowBook(book);
        book->borrowBook(getUserID());
    }
}

// Returns a book if it was borrowed by this account.
void User::returnBook(Book* book) {
    if (!userAccount.hasBorrowedBook(book)) {
        cout << "This book was not borrowed by this account!\n";
        return;
    } else {
        userAccount.returnBook(book, getMaxBorrowingPeriod(), getFinePerDay());
        cout << "Book returned successfully!\n";
    }
}

// Processes fine payment for a book.
// Verifies that the payment amount is valid before processing.
void User::payFine(string isbn, int amount) {
    int dues = getFine();
    if (amount > dues) {
        cout << "Amount is greater than the fine.\n";
        return;
    }  
    else if(amount < 0) {
        cout << "Cannot pay a negative amount.\n";
        return;
    } else {
        userAccount.finePay(isbn, amount, getOverdueLimit(), getFinePerDay());
    }
}
