#ifndef LIBRARY_MANAGEMENT_H
#define LIBRARY_MANAGEMENT_H

#include "Book.h"
#include "User.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class LibraryManagement {
private:
    vector<Book*> books;
    vector<User*> users;
    unordered_map<string, int> indexOfISBN;
    unordered_map<string, int> indexOfUserID;

    void swapToLastBook(const string &ISBN);
    void swapToLastUser(const string &userID);

public:
    vector<Book*>& getBooks();
    vector<User*>& getUsers();
    bool isExistBook(const string &ISBN);
    bool isExistUser(const string &userID);
    User* getUser(const string &userID);
    Book* getBook(const string &ISBN);
    void updateISBN(const string &ISBN, const string &newISBN);
    void addBook(Book* book);
    void deleteBook(const string &ISBN);
    void addUser(User* user);
    void deleteUser(const string &userID);
    void printAvailableBooks();
    void printAllBooks();
    void printAllUsers();
};


#endif // LIBRARY_MANAGEMENT_H
