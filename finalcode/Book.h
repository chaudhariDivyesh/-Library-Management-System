#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

/**
 * @class Book
 * @brief Represents a book in a library system.
 */
class Book {
private:
    string title;           ///< Title of the book.
    string author;          ///< Author of the book.
    string publisher;       ///< Publisher of the book.
    int year;               ///< Publication year.
    string isbn;            ///< ISBN number.
    string status;          ///< Status of the book (available, borrowed, reserved).
    time_t borrowTime;      ///< Timestamp when the book was borrowed.
    string currUserId;      ///< ID of the current user who borrowed the book.
    vector<tuple<string, time_t, time_t>> bookHistory; ///< History of borrow/return transactions.

public:    
    // Constructor
    Book(string title, string author, string publisher, int year, string isbn);

    // Status Check Functions
    bool isAvailable();
    bool isReserved();
    bool isBorrowedBook();

    // Display Book Details
    void details();
    
    // Getters
    string getTitle();
    string getAuthor();
    string getPublisher();
    int getYear();
    string getISBN();
    string getStatus();
    string getCurrentUser();
    time_t getBorrowTime();
    int daysBorrowed();
    
    // Setters
    void setTitle(string newTitle);
    void setAuthor(string newAuthor);
    void setPublisher(string newPublisher);
    void setYear(int newYear);
    void setISBN(string newISBN);
    void setStatus(string status);
    void setCurrUserId(string userId);
    void setBorrowTime(time_t time);
    
    // Update Book Details
    bool updateBook(string attribute, string val);

    // Borrowing History
    const vector<tuple<string, time_t, time_t>>& getHistory() const;
    void addHistoryRecord(const string& userId, time_t borrowTime, time_t returnTime);
    void updateHistory();
    
    // Borrow & Return Operations
    void borrowBook(string userId);
    void returnBook();
    void updateBorrowTime();
    
    // Print Borrow History
    void printHistory();
};

#endif
