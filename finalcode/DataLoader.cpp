// DataLoader.cpp - Implementation file for CSV data loading functions
#include "DataLoader.h"
#include "Utils.h"  // For parseTimeString() and stringifyTime()
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Account.h"
#include "Book.h"
#include "Faculty.h"
#include "Librarian.h"
#include "Student.h"
#include "User.h"
#include "Utils.h"

using namespace std;

void loadBooksFromCsv(LibraryManagement* library, const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". Starting with empty book list.\n";
        return;
    }
    string line;
    // Read and ignore header line
    getline(in, line);
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        // Split line by commas and remove surrounding quotes
        while (getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"')
                field.erase(0, 1);
            if (!field.empty() && field.back() == '"')
                field.pop_back();
            fields.push_back(field);
        }
        // Expecting at least 8 fields: Title, Author, Publisher, Year, ISBN, Status, BorrowDate, CurrUserID
        if (fields.size() >= 8) {
            string title = fields[0];
            string author = fields[1];
            string publisher = fields[2];
            int year = stoi(fields[3]);
            string ISBN = fields[4];
            string status = fields[5];
            string borrowDate = fields[6];
            string currUserID = fields[7];
            
            Book* book = new Book(title, author, publisher, year, ISBN);
            book->setStatus(status);
            book->setBorrowTime(parseTimeString(borrowDate));
            book->setCurrUserId(currUserID);
            library->addBook(book);
        }
    }
    cout << "Books loaded successfully." << endl;
    in.close();
}

void loadStudentsFromCsv(LibraryManagement* library, const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No students loaded.\n";
        return;
    }
    
    string line;
    getline(in, line); // Skip header

    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        // Split CSV line and remove quotes if present
        while (getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"')
                field.erase(0, 1);
            if (!field.empty() && field.back() == '"')
                field.pop_back();
            fields.push_back(field);
        }
        // Expecting at least 7 fields: Name, UserID, Password, BorrowedBooks, History, BookOverdue, PaymentHistory
        if (fields.size() >= 7) {
            string name = fields[0];
            string userID = fields[1];
            string password = fields[2]; 
            string borrowedBooksStr = fields[3]; // e.g., "ISBN1;ISBN2;ISBN3"
            string historyStr = fields[4];       // e.g., "BookTitle|Date|Action;BookTitle|Date|Action"
            string bookOverdueStr = fields[5];     // e.g., "ISBN|BorrowDate|ReturnDate|TotalFine|RemainingFine;..."
            string paymentHistoryStr = fields[6];  // e.g., "ISBN|PaymentDate|PaymentAmount|RemainingAmount;..."
            
            // Create new student (ensure class is Student with uppercase S)
            Student* newStudent = new Student(name, userID, password);
            
            // Process BorrowedBooks.
            if (!borrowedBooksStr.empty()) {
                stringstream ssBooks(borrowedBooksStr);
                string isbn;
                while (getline(ssBooks, isbn, ';')) {
                    Book* b = library->getBook(isbn);
                    if (b != nullptr)
                        newStudent->getAccount().addToBorrowedBooks(b);
                }
            }
            
            // Process History records.
            if (!historyStr.empty()) {
                stringstream ssHistory(historyStr);
                string record;
                while (getline(ssHistory, record, ';')) {
                    stringstream ssRecord(record);
                    string bookTitle, date, action;
                    getline(ssRecord, bookTitle, '|');
                    getline(ssRecord, date, '|');
                    getline(ssRecord, action, '|');
                    newStudent->getAccount().addHistoryRecord(make_tuple(bookTitle, date, action));
                }
            }
            
            // Process BookOverdue records.
            if (!bookOverdueStr.empty()) {
                stringstream ssOverdue(bookOverdueStr);
                string record;
                while (getline(ssOverdue, record, ';')) {
                    stringstream ssRecord(record);
                    string isbn, borrowDate, returnDate, totalFineStr, remainingFineStr;
                    getline(ssRecord, isbn, '|');
                    getline(ssRecord, borrowDate, '|');
                    getline(ssRecord, returnDate, '|');
                    getline(ssRecord, totalFineStr, '|');
                    getline(ssRecord, remainingFineStr, '|');
                    int totalFine = stoi(totalFineStr);
                    int remainingFine = stoi(remainingFineStr);
                    newStudent->getAccount().addBookOverdueRecord(isbn, borrowDate, returnDate, totalFine, remainingFine);
                }
            }
            
            // Process PaymentHistory records.
            if (!paymentHistoryStr.empty()) {
                stringstream ssPayment(paymentHistoryStr);
                string record;
                while (getline(ssPayment, record, ';')) {
                    stringstream ssRecord(record);
                    string isbn, borrowDate, returnDate, paymentDate, paymentAmountStr, remainingAmountStr;
                    getline(ssRecord, isbn, '|');
                    getline(ssRecord, borrowDate, '|');
                    getline(ssRecord, returnDate, '|');
                    getline(ssRecord, paymentDate, '|');
                    getline(ssRecord, paymentAmountStr, '|');
                    getline(ssRecord, remainingAmountStr, '|');
                    int paymentAmount = stoi(paymentAmountStr);
                    int remainingAmount = stoi(remainingAmountStr);
                    newStudent->getAccount().addPaymentRecord(isbn, paymentDate, borrowDate, returnDate, paymentAmount, remainingAmount);
                }
            }
            library->addUser(newStudent);
        }
    }
    cout << "Students loaded successfully." << endl;
    in.close();
}

void loadFacultyFromCsv(LibraryManagement* library, const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No faculty loaded.\n";
        return;
    }
    string line;
    getline(in, line); // Skip header

    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        // Split CSV line and remove surrounding quotes.
        while(getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"')
                field.erase(0, 1);
            if (!field.empty() && field.back() == '"')
                field.pop_back();
            fields.push_back(field);
        }
        // Expecting at least 5 fields: Name, UserID, Password, BorrowedBooks, History.
        if (fields.size() >= 5) {
            string name = fields[0];
            string userID = fields[1];
            string password = fields[2];
            string borrowedBooksStr = fields[3]; // e.g., "ISBN1;ISBN2;ISBN3"
            string historyStr = fields[4];       // e.g., "BookTitle|Date|Action;BookTitle|Date|Action"

            // Create new faculty (ensure class is Faculty with uppercase F)
            Faculty* newFaculty = new Faculty(name, userID, password);

            // Process BorrowedBooks.
            if (!borrowedBooksStr.empty()) {
                stringstream ssBooks(borrowedBooksStr);
                string isbn;
                while (getline(ssBooks, isbn, ';')) {
                    Book* b = library->getBook(isbn);
                    if (b != nullptr)
                        newFaculty->getAccount().addToBorrowedBooks(b);
                }
            }

            // Process History records.
            if (!historyStr.empty()) {
                stringstream ssHistory(historyStr);
                string record;
                while (getline(ssHistory, record, ';')) {
                    stringstream ssRecord(record);
                    string bookTitle, date, action;
                    getline(ssRecord, bookTitle, '|');
                    getline(ssRecord, date, '|');
                    getline(ssRecord, action, '|');
                    newFaculty->getAccount().addHistoryRecord(make_tuple(bookTitle, date, action));
                }
            }
            library->addUser(newFaculty);
        }
    }
    cout << "Faculty loaded successfully." << endl;
    in.close();
}

void loadLibrariansFromCsv(LibraryManagement* library, const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No librarians loaded.\n";
        return;
    }
    string line;
    getline(in, line); // Skip header
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while(getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"')
                field.erase(0, 1);
            if (!field.empty() && field.back() == '"')
                field.pop_back();
            fields.push_back(field);
        }
        if (fields.size() >= 3) {
            string name = fields[0];
            string userID = fields[1];
            string password = fields[2];
            // Create new librarian (class Librarian with uppercase L)
            User* newUser = new Librarian(name, userID, password);
            library->addUser(newUser);
        }
    }
    cout << "Librarians loaded successfully." << endl;
    in.close();
}

void loadBookHistoryFromCsv(LibraryManagement* library, const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No history loaded.\n";
        return;
    }
    string line;
    getline(in, line); // Skip header
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        // Split line by commas (history CSV may not have quotes)
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        // Expecting 4 fields: ISBN, UserID, BorrowDate, ReturnDate.
        if (fields.size() >= 4) {
            string isbn = fields[0];
            string userID = fields[1];
            time_t borrowTime = parseTimeString(fields[2]);
            time_t returnTime = parseTimeString(fields[3]);
            Book* book = library->getBook(isbn);
            if (book) {
                book->addHistoryRecord(userID, borrowTime, returnTime);
            }
        }
    }
    in.close();
}

void loadAllUsersFromCsv(LibraryManagement* library) {
    loadStudentsFromCsv(library, "students.csv");
    loadFacultyFromCsv(library, "faculty.csv");
    loadLibrariansFromCsv(library, "librarians.csv");
}

void loadAllData(LibraryManagement* library) {
    loadBooksFromCsv(library, "books.csv");
    loadAllUsersFromCsv(library);
    loadBookHistoryFromCsv(library, "bookHistory.csv");
}

void loadFile(LibraryManagement* library) {
    loadAllData(library);
}
