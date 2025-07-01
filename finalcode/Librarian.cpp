// Librarian.cpp - Implementation file for Librarian class
#include "Librarian.h"
#include "Student.h"
#include "Faculty.h"
#include "LibraryManagement.h"
#include "Book.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor: Initializes a Librarian using the User base class constructor.
Librarian::Librarian(string name, string userID, string password)
    : User(name, "librarian", userID, password) {}

// Librarian cannot borrow books, so these functions return default values.
int Librarian::getMaxBorrowingPeriod() {
    return 0;
}

int Librarian::getMaxAllowedBooks() {
    return 0;
}

int Librarian::getFinePerDay() {
    return 0;
}

int Librarian::getOverdueLimit() {
    return 0;
}

bool Librarian::canBorrowBook(Book* book) {
    return false;
}

void Librarian::displayCurrBorrowedBooks() {
    // Librarian typically does not borrow books.
    cout << "Librarian does not borrow books." << endl;
}

// Adds a new book to the library.
void Librarian::addBook(LibraryManagement &library, string title, string author, string publisher, int year, string ISBN) {
    Book* book = new Book(title, author, publisher, year, ISBN);
    if (library.isExistBook(ISBN)) {
        cout << "Provided book already exists." << endl;
        return;
    }
    library.addBook(book);
    cout << "Book added successfully." << endl;
}

// Reserves a book.
void Librarian::reserveBook(Book* book) {
    if (book->isBorrowedBook()) {
        cout << "Book is borrowed! Cannot be reserved." << endl;
        return;
    }
    if (book->isReserved()) {
        cout << "Book is already reserved!" << endl;
        return;
    }
    if (book->isAvailable()) {
        book->setStatus("reserved");
        cout << "Book is reserved successfully." << endl;
    }
}

// Dereserves a book (sets its status to available).
void Librarian::deReserveBook(Book* book) {
    if (book->isBorrowedBook()) {
        cout << "Book is borrowed and cannot be dereserved!" << endl;
        return;
    }
    if (book->isReserved()) {
        book->setStatus("available");
        cout << "Book is dereserved successfully." << endl;
        return;
    }
    if (book->isAvailable()) {
        cout << "Book is already dereserved!" << endl;
        return;
    }
}

// Removes a book from the library.
void Librarian::removeBook(LibraryManagement &library, string ISBN) {
    library.deleteBook(ISBN);
}

// Adds a new user to the library.
void Librarian::addUser(LibraryManagement &library, string name, string role, string userID, string password) {
    if (library.isExistUser(userID)) {
        cout << "Provided userID already exists." << endl;
        return;
    }
    cout<<role<<endl;
    if (role == "student") {
        Student* studentUser = new Student(name, userID, password);
        library.addUser(studentUser);
        cout << "Student added successfully." << endl;
    } else if (role == "faculty") {
        Faculty* facultyUser = new Faculty(name, userID, password);
        library.addUser(facultyUser);
        cout << "Faculty added successfully." << endl;
    } else if(role=="librarian"){
        Librarian* librarianUser = new Librarian(name, userID, password);
        library.addUser(librarianUser);
        cout << "Librarian added successfully." << endl;
    }
    else{
        cout<<"Enter Valid Role!"<<endl;
    }
}

// Removes a user from the library.
void Librarian::removeUser(LibraryManagement &library, string userID) {
    library.deleteUser(userID);
}

// Updates the details of a book.
void Librarian::updateBook(LibraryManagement &library, string ISBN, string attribute, string val) {
    Book* bookToBeUpdated = library.getBook(ISBN);
    if (!bookToBeUpdated) {
        //cout << "Book not found." << endl;
        return;
    }
    if(bookToBeUpdated->isBorrowedBook()){
        cout<<"Book is currently Borrowed, cannot update Now!"<<endl;
        return ;
    }
    if (attribute == "ISBN") {
        if (ISBN == val) {
            cout << "ISBN value to be updated is the same." << endl;
            return;
        } else {
            if (library.isExistBook(val)) {
                cout << "Book with this ISBN already exists." << endl;
                return;
            }
            library.updateISBN(ISBN, val);
        }
    }
    if(bookToBeUpdated->updateBook(attribute, val)){
        cout << "Book updated successfully!" << endl;
    }
}
