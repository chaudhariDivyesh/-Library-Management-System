// DataSaver.cpp - Implementation file for CSV data saving functions
#include "Save.h"
#include "Utils.h"    // For stringifyTime()
#include "Book.h"
#include "User.h"
#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"
#include "LibraryManagement.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void saveBooksToCSV(LibraryManagement* library, const string &filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }
    // Write header
    out << "Title,Author,Publisher,Year,ISBN,Status,BorrowDate,CurrUserID\n";
    for (Book* book : library->getBooks()) {
        out << "\"" << book->getTitle() << "\","
            << "\"" << book->getAuthor() << "\","
            << "\"" << book->getPublisher() << "\","
            << book->getYear() << ","
            << book->getISBN() << ","
            << book->getStatus() << ","
            << stringifyTime(book->getBorrowTime()) << ","
            << "\"" << book->getCurrentUser() << "\"\n";
    }
    out.close();
}

void saveStudentsToCSV(LibraryManagement* library, const string &filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }
    
    // CSV header: Name, UserID, password, BorrowedBooks, History, BookOverdue, PaymentHistory
    out << "Name,UserID,password,BorrowedBooks,History,BookOverdue,PaymentHistory\n";
    
    // Process only student users.
    for (User* u : library->getUsers()) {
        if (u->getRole() == "student") {
            Student* s = dynamic_cast<Student*>(u);
            if (!s) continue;
            
            Account &acc = s->getAccount();
            
            // Serialize BorrowedBooks: list ISBNs separated by semicolons.
            string borrowedBooks;
            for (Book* b : acc.getBorrowedBooks()) {
                borrowedBooks += b->getISBN() + ";";
            }
            if (!borrowedBooks.empty())
                borrowedBooks.pop_back();
            
            // Serialize History: each record "BookTitle|Date|Action" separated by semicolons.
            string history;
            for (const auto &record : acc.getHistory()) {
                history += get<0>(record) + "|" + get<1>(record) + "|" + get<2>(record) + ";";
            }
            if (!history.empty())
                history.pop_back();
            
            // Serialize BookOverdue: each record "ISBN|BorrowDate|ReturnDate|TotalFine|RemainingFine" separated by semicolons.
            string bookOverdueStr;
            for (const auto &record : acc.getBookOverdue()) {
                bookOverdueStr += get<0>(record) + "|" + get<1>(record) + "|" + get<2>(record) + "|" +
                                  to_string(get<3>(record)) + "|" + to_string(get<4>(record)) + ";";
            }
            if (!bookOverdueStr.empty())
                bookOverdueStr.pop_back();
            
            // Serialize PaymentHistory: each record "ISBN|PaymentDate|PaymentAmount|RemainingAmount" separated by semicolons.
            string paymentHistoryStr;
            for (const auto &record : acc.getPaymentHistory()) {
                paymentHistoryStr += get<0>(record) + "|" + get<1>(record) + "|" + get<2>(record) + "|" + get<3>(record) + "|" +
                                     to_string(get<4>(record)) + "|" + to_string(get<5>(record)) + ";";
            }
            if (!paymentHistoryStr.empty())
                paymentHistoryStr.pop_back();
            
            out << "\"" << s->getName() << "\","
                << "\"" << s->getUserID() << "\","
                << "\"" << s->getPassword() << "\","
                << "\"" << borrowedBooks << "\","
                << "\"" << history << "\","
                << "\"" << bookOverdueStr << "\","
                << "\"" << paymentHistoryStr << "\"\n";
        }
    }
    out.close();
}

void saveFacultyToCSV(LibraryManagement* library, const string &filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }
    // CSV header for faculty: Name, UserID, password, BorrowedBooks, History
    out << "Name,UserID,password,BorrowedBooks,History\n";
    
    for (User* u : library->getUsers()) {
        if (u->getRole() == "faculty") {
            Faculty* f = dynamic_cast<Faculty*>(u);
            if (!f) continue;
            Account &acc = f->getAccount();
            
            // Serialize BorrowedBooks.
            string borrowedBooks;
            for (Book* b : acc.getBorrowedBooks()) {
                borrowedBooks += b->getISBN() + ";";
            }
            if (!borrowedBooks.empty())
                borrowedBooks.pop_back();
            
            // Serialize History.
            string history;
            for (const auto &record : acc.getHistory()) {
                history += get<0>(record) + "|" + get<1>(record) + "|" + get<2>(record) + ";";
            }
            if (!history.empty())
                history.pop_back();
            
            out << "\"" << f->getName() << "\","
                << "\"" << f->getUserID() << "\","
                << "\"" << f->getPassword() << "\","
                << "\"" << borrowedBooks << "\","
                << "\"" << history << "\"\n";
        }
    }
    
    out.close();
}

void saveLibrariansToCSV(LibraryManagement* library, const string &filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }
    out << "Name,UserID,password\n";
    for (User* u : library->getUsers()) {
        if (u->getRole() == "Librarian" || u->getRole() == "librarian") {
            out << "\"" << u->getName() << "\","
                << "\"" << u->getUserID() << "\","
                << "\"" << u->getPassword() << "\"\n";
        }
    }
    out.close();
}

void saveBookHistoryToCSV(LibraryManagement* library, const string &filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }
    // Write header: ISBN,UserID,BorrowDate,ReturnDate
    out << "ISBN,UserID,BorrowDate,ReturnDate\n";
    for (Book* book : library->getBooks()) {
        // Get the history records from the book.
        const auto &history = book->getHistory();
        for (const auto &record : history) {
            out << book->getISBN() << ","
                << get<0>(record) << ","
                << stringifyTime(get<1>(record)) << ","
                << stringifyTime(get<2>(record)) << "\n";
        }
    }
    out.close();
}

void saveAllUsersToCSV(LibraryManagement* library) {
    saveStudentsToCSV(library, "students.csv");
    saveFacultyToCSV(library, "faculty.csv");
    saveLibrariansToCSV(library, "librarians.csv");
}

void saveAllData(LibraryManagement* library) {
    // Save books, users, and book history
    saveBooksToCSV(library, "books.csv");
    saveAllUsersToCSV(library);
    saveBookHistoryToCSV(library, "bookHistory.csv");
}

void saveFile(LibraryManagement* library) {
    saveAllData(library);
}

void clearCSV(const string &filename) {
    // Open the file in truncate mode to clear its contents.
    ofstream out(filename, ios::trunc);
    if (!out) {
        cout << "Error clearing file: " << filename << endl;
        return;
    }
    out.close();
}
