#include "LibraryManagement.h"
#include <iostream>

using namespace std;

vector<Book*>& LibraryManagement::getBooks() {
    return books;
}

vector<User*>& LibraryManagement::getUsers() {
    return users;
}

bool LibraryManagement::isExistBook(const string &ISBN) {
    return indexOfISBN.find(ISBN) != indexOfISBN.end();
}

bool LibraryManagement::isExistUser(const string &userID) {
    return indexOfUserID.find(userID) != indexOfUserID.end();
}

void LibraryManagement::swapToLastBook(const string &ISBN) {
    int currIndex = indexOfISBN[ISBN];
    Book* lastBook = books[books.size() - 1];
    books[currIndex] = lastBook;
    indexOfISBN[lastBook->getISBN()] = currIndex;
}

Book* LibraryManagement::getBook(const string &ISBN) {
    if (!isExistBook(ISBN)) {
        cout << "Book does not exist" << endl;
        return nullptr;
    }
    return books[indexOfISBN[ISBN]];
}

User* LibraryManagement::getUser(const string &userID) {
    if (!isExistUser(userID)) {
        cout << "User does not exist" << endl;
        return nullptr;
    }
    return users[indexOfUserID[userID]];
}

void LibraryManagement::updateISBN(const string &ISBN, const string &newISBN) {
    if (isExistBook(newISBN)) {
        cout << "Book with this ISBN already exists" << endl;
        return;
    }
    int currIndex = indexOfISBN[ISBN];
    indexOfISBN.erase(ISBN);
    indexOfISBN[newISBN] = currIndex;
}

void LibraryManagement::addBook(Book* book) {
    if (isExistBook(book->getISBN())) {
        cout << "Book already exists" << endl;
        return;
    }
    books.push_back(book);
    indexOfISBN[book->getISBN()] = books.size() - 1;
}

void LibraryManagement::deleteBook(const string &ISBN) {
    if (!isExistBook(ISBN)) {
        cout << "Book does not exist" << endl;
        return;
    }
    Book* book=getBook(ISBN);
    if(book->isBorrowedBook()){
        cout<<"Book is currently Borrowed, cannot remove Now!"<<endl;
        return ;
    }
    book->details();
    swapToLastBook(ISBN);
    books.pop_back();
    indexOfISBN.erase(ISBN);
    cout << "Book removed successfully" << endl;
}

void LibraryManagement::swapToLastUser(const string &userID) {
    int currIndex = indexOfUserID[userID];
    User* lastUser = users[users.size() - 1];
    users[currIndex] = lastUser;
    indexOfUserID[lastUser->getUserID()] = currIndex;
}

void LibraryManagement::addUser(User* user) {
    if (isExistUser(user->getUserID())) {
        cout << "User already exists" << endl;
        return;
    }
    users.push_back(user);
    indexOfUserID[user->getUserID()] = users.size() - 1;
}

void LibraryManagement::deleteUser(const string &userID) {
    if (!isExistUser(userID)) {
        cout << "User does not exist" << endl;
        return;
    }
    User* user=getUser(userID);
    cout<<"Name: "<<user->getName()<<"  userID: "<<userID<<"  Role: "<<user->getRole()<<endl;
    swapToLastUser(userID);
    users.pop_back();
    indexOfUserID.erase(userID);
    cout << "User removed successfully" << endl;
}

void LibraryManagement::printAvailableBooks() {
    bool found = false;
    cout << "\nAvailable Books in Library:\n\n";

    // Table header with adjusted widths
    cout << left << setw(40) << "Title"
         << setw(25) << "Author"
         << setw(35) << "Publisher"
         << setw(6)  << "Year"
         << setw(15) << "ISBN"   // Increased width for longer ISBNs
         << setw(12) << "Status"
         << endl;
    cout << string(133, '-') << endl;  // Adjusted separator width

    // Print available books
    for (Book* book : books) {
        if (book->isAvailable()) {
            cout << left << setw(40) << book->getTitle()
                 << setw(25) << book->getAuthor()
                 << setw(35) << book->getPublisher()
                 << setw(6)  << book->getYear()
                 << setw(15) << book->getISBN()  // Increased width for longer ISBNs
                 << setw(12) << book->getStatus()
                 << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No available books found.\n";
    }
}

void LibraryManagement::printAllBooks() {
    if (books.empty()) {
        cout << "No books available in the library.\n";
        return;
    }

    cout << "\nAll Books in Library:\n\n";

    // Table header with adjusted widths
    cout << left << setw(40) << "Title"
         << setw(25) << "Author"
         << setw(35) << "Publisher"
         << setw(6)  << "Year"
         << setw(15) << "ISBN"   // Increased width for longer ISBNs
         << setw(12) << "Status"
         << endl;
    cout << string(133, '-') << endl;  // Adjusted separator width

    // Print all books
    for (Book* book : books) {
        cout << left << setw(40) << book->getTitle()
             << setw(25) << book->getAuthor()
             << setw(35) << book->getPublisher()
             << setw(6)  << book->getYear()
             << setw(15) << book->getISBN()  // Increased width for longer ISBNs
             << setw(12) << book->getStatus()
             << endl;
    }
}

void LibraryManagement::printAllUsers() {
    if (users.empty()) {
        cout << "No users registered in the library.\n";
        return;
    }

    // Define column widths
    const int userIDWidth = 25;
    const int nameWidth = 40;
    const int roleWidth = 20;

    // Header for all users
    cout << "\nAll Registered Users:\n\n";

    // Categories to separate users by role
    vector<User*> students, faculty, librarians;

    // Categorizing users
    for (User* user : users) {
        if (user->getRole() == "student") {
            students.push_back(user);
        } else if (user->getRole() == "faculty") {
            faculty.push_back(user);
        } else if (user->getRole() == "librarian") {
            librarians.push_back(user);
        }
    }

    // Function to print users of a specific category
    auto printUsers = [&](const string &category, const vector<User*> &userList) {
        if (userList.empty()) return;
        cout << category << ":\n";
        cout << left << setw(userIDWidth) << "User ID"
             << setw(nameWidth) << "Name"
             << setw(roleWidth) << "Role"
             << endl;
        cout << string(userIDWidth + nameWidth + roleWidth, '-') << endl;

        for (User* user : userList) {
            cout << left << setw(userIDWidth) << user->getUserID()
                 << setw(nameWidth) << user->getName()
                 << setw(roleWidth) << user->getRole()
                 << endl;
        }
        cout << endl;  // Extra spacing for clarity
    };

    // Print each category
    printUsers("Students", students);
    printUsers("Faculty", faculty);
    printUsers("Librarians", librarians);
}
