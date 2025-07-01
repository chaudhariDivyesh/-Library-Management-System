#include "Book.h"
#include "Utils.h"  // Utility functions for date/time handling
#include <bits/stdc++.h>
/**
 * @brief Constructor to initialize a Book object.
 */
Book::Book(string title, string author, string publisher, int year, string isbn) {
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->year = year;
    this->isbn = isbn;
    this->status = "available";
    this->borrowTime = 0;
    this->currUserId = "";
}

// ---------------- Status Check Functions ----------------
bool Book::isAvailable() { return status == "available"; }
bool Book::isReserved() { return status == "reserved"; }
bool Book::isBorrowedBook() { return status == "borrowed"; }

// ---------------- Display Function ----------------
void Book::details() {
    //void Book::details() {
    cout << left << setw(25) << title
            << setw(20) << author
            << setw(20) << publisher
            << setw(6) << year
            << setw(10) << isbn
            << setw(12) << status << endl;
    //}
}

// ---------------- Getters ----------------
string Book::getTitle() { return title; }
string Book::getAuthor() { return author; }
string Book::getPublisher() { return publisher; }
int Book::getYear() { return year; }
string Book::getISBN() { return isbn; }
string Book::getStatus() { return status; }
string Book::getCurrentUser() { return currUserId; }
time_t Book::getBorrowTime() { return borrowTime; }

/**
 * @brief Calculates how many days the book has been borrowed.
 * @return Number of minutes since the book was borrowed.
 */
int Book::daysBorrowed() {
    if (isAvailable()) return 0;
    time_t currTime = system_clock::to_time_t(system_clock::now());
    return ceil((double)(currTime - borrowTime) / (24*60*60));
}

// ---------------- Setters ----------------
void Book::setTitle(string newTitle) { title = newTitle; }
void Book::setAuthor(string newAuthor) { author = newAuthor; }
void Book::setPublisher(string newPublisher) { publisher = newPublisher; }
void Book::setYear(int newYear) { year = newYear; }
void Book::setISBN(string newISBN) { isbn = newISBN; }
void Book::setStatus(string newStatus) { status = newStatus; }
void Book::setCurrUserId(string userId) { currUserId = userId; }
void Book::setBorrowTime(time_t time) { borrowTime = time; }

// ---------------- Book Update Functions ----------------
bool Book::updateBook(string attribute, string val) {
    if (attribute == "Title") setTitle(val);
    else if (attribute == "Author") setAuthor(val);
    else if (attribute == "Publisher") setPublisher(val);
    else if (attribute == "Year") setYear(stoi(val));
    else if (attribute == "ISBN") setISBN(val);
    else {
        cout << "Invalid attribute! please enter valid attribute" << endl;
        return false;
    }
    cout << attribute << " updated successfully" << endl;
    return true;
}

// ---------------- Borrowing History Functions ----------------
const vector<tuple<string, time_t, time_t>>& Book::getHistory() const {
    return bookHistory;
}

void Book::addHistoryRecord(const string& userId, time_t borrowTime, time_t returnTime) {
    bookHistory.push_back(make_tuple(userId, borrowTime, returnTime));
}

void Book::updateHistory() {
    time_t returnTime = system_clock::to_time_t(system_clock::now());
    bookHistory.push_back(make_tuple(currUserId, borrowTime, returnTime));
}

// ---------------- Borrow & Return Operations ----------------
void Book::borrowBook(string userId) {
    if (!isAvailable()) {
        cout << "Book is already borrowed.\n";
        return;
    }
    setStatus("borrowed");
    setBorrowTime(system_clock::to_time_t(system_clock::now()));
    setCurrUserId(userId);
}

void Book::returnBook() {
    setStatus("available");
    updateHistory();
    setBorrowTime(0);
    setCurrUserId("");
}

void Book::updateBorrowTime() {
    borrowTime = system_clock::to_time_t(system_clock::now());
}

// ---------------- Print History ----------------
void Book::printHistory() {
    if (bookHistory.empty() && currUserId.empty()) {
        cout << "No history available for \"" << title << "\".\n";
        return;
    }

    cout << "\nBorrowing History for \"" << title << "\":\n\n";

    // Define column widths
    const int userIDWidth = 15;
    const int borrowWidth = 25;
    const int returnWidth = 25;

    // Print table header
    cout << left << setw(userIDWidth) << "User ID"
         << setw(borrowWidth) << "Borrowed On"
         << setw(returnWidth) << "Returned On"
         << endl;
    
    // Print separator line
    cout << string(userIDWidth + borrowWidth + returnWidth, '-') << endl;

    // Print borrowing history
    for (const auto& entry : bookHistory) {
        string userId = get<0>(entry);
        time_t borrowTime = get<1>(entry);
        time_t returnTime = get<2>(entry);

        cout << left << setw(userIDWidth) << userId
             << setw(borrowWidth) << stringifyTime(borrowTime)
             << setw(returnWidth) << stringifyTime(returnTime)
             << endl;
    }

    // Check if the book is currently borrowed
    if (!currUserId.empty()) {
        cout << "\nCurrently Borrowed By:\n";
        cout << left << setw(userIDWidth) << "User ID"
             << setw(borrowWidth) << "Borrowed On"
             << setw(returnWidth) << "Status"
             << endl;
        cout << string(userIDWidth + borrowWidth + returnWidth, '-') << endl;
        cout << left << setw(userIDWidth) << currUserId
             << setw(borrowWidth) << stringifyTime(borrowTime)
             << setw(returnWidth) << "Borrowed"
             << endl;
    }

    cout << endl;
}
