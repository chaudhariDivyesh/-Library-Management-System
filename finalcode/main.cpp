// main.cpp
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include "LibraryManagement.h"
#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"
#include "DataLoader.h"
#include "Save.h"

using namespace std;

// Function to initialize library with default data if not loaded from file
void initializeLibrary(LibraryManagement &library) {
    // If no books exist, add 10 books.
    if(library.getBooks().empty()) {
        library.addBook(new Book("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "Bloomsbury", 1997, "978-0747532699"));
        library.addBook(new Book("1984", "George Orwell", "Secker & Warburg", 1949, "978-0451524935"));
        library.addBook(new Book("The Hobbit", "J.R.R. Tolkien", "Allen & Unwin", 1937, "978-0618968633"));
        library.addBook(new Book("The Great Gatsby", "F. Scott Fitzgerald", "Charles Scribner's Sons", 1925, "978-0743273565"));
        library.addBook(new Book("To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott & Co.", 1960, "978-0061120084"));
        library.addBook(new Book("The Da Vinci Code", "Dan Brown", "Doubleday", 2003, "978-0385504201"));
        library.addBook(new Book("War and Peace", "Leo Tolstoy", "The Russian Messenger", 1869, "978-1400079988"));
        library.addBook(new Book("Adventures of Huckleberry Finn", "Mark Twain", "Chatto & Windus", 1885, "978-0486280615"));
        library.addBook(new Book("Pride and Prejudice", "Jane Austen", "T. Egerton", 1813, "978-1503290563"));
        library.addBook(new Book("The Odyssey", "Homer", "Ancient Greece", -800, "978-0140268867"));

    }
    
    // If no users exist, add 5 students, 3 faculty, and 1 librarian.
    if(library.getUsers().empty()) {
        // Add 5 students.
        library.addUser(new Student("Alice", "S001", "alice123"));
        library.addUser(new Student("Bob", "S002", "bob123"));
        library.addUser(new Student("Charlie", "S003", "charlie123"));
        library.addUser(new Student("Diana", "S004", "diana123"));
        library.addUser(new Student("Ethan", "S005", "ethan123"));
        
        // Add 3 faculty.
        library.addUser(new Faculty("Prof. Smith", "F001", "smith123"));
        library.addUser(new Faculty("Prof. Johnson", "F002", "johnson123"));
        library.addUser(new Faculty("Prof. Williams", "F003", "williams123"));
        
        // Add 1 librarian.
        library.addUser(new Librarian("Librarian Mike", "L001", "mike123"));
    }
}

// Student menu options
void studentMenu(Student* student, LibraryManagement*library) {
    int choice;
    bool loggedIn = true;
    while(loggedIn) {
        //  function to view all books
        //  case for view books details and histroy
        cout << "\n---- Student Menu ----" << endl;
        cout << "1. View All Books" << endl;
        cout << "2. View Available Books" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. View History" << endl;
        cout << "6. View Your currently borrowed books" << endl;
        cout << "7. View Overdue Books" << endl;
        cout << "8. Pay Fines" << endl;
        cout << "9. View Your PaymentHistory" << endl;
        cout << "10. View Book details&History" << endl;
        cout << "11. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        //add here
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;                 // Skip the rest of the loop and ask again

        }
        cin.ignore(); // flush newline
        cout<<endl;
        switch(choice) {
            case 1: {
                //View All Books
                library->printAllBooks();
                break;
            }
            case 2: {
                // View Available Books
                library->printAvailableBooks();
                break;
            }
            case 3: {
                //Borrow Book
                string isbn;
                cout << "Enter ISBN of the book get details: ";
                getline(cin, isbn);
                cout<<endl;
                Book* book = library->getBook(isbn);
                if(!book){
                    break;
                }
                if(book && book->isAvailable()) {
                    student->borrowBook(book);
                }
                else if(student->hasBorrowedBook(book)){
                    cout <<endl<< "You have already Borrowed this Book !" << endl;
                }
                else if(book->isBorrowedBook()){
                    cout <<endl<< "this Book is not available currentley!" << endl;
                }
                else if(book->isReserved()){
                    cout <<endl<< "This Book is Reserved!, You cannot Borrow this Book" << endl;
                }
                break;
            }
            case 4: {
                //Return Book
                // display currently Borrowed books
                student->displayCurrBorrowedBooks();
                string isbn;
                cout << "Enter ISBN of the book to return: ";
                getline(cin, isbn);
                cout<<endl;
                Book* book = library->getBook(isbn);
                if(book) {
                    //book->details();
                    student->returnBook(book);
                    //cout << "Book returned successfully." << endl;
                } else {
                    cout << "Invalid ISBN entered." << endl;
                }
                break;
            }
            case 5: {
                //View History
                student->displayHistory();
                break;
            }
            case 6: {
                //View Your currently borrowed books
                student->displayCurrBorrowedBooks();
                break;
            }
            case 7: {
                //View Overdue Books
                student->displayOverdueBooks();
                break;
            }
            case 8: {
                // check if user have fine 
                if(student->getFine()==0){
                    cout<<"You don't have Overdue"<<endl;
                    break;
                }
                // if user has fine display overdue Books
                student->displayOverdueBooks();
                // enter the ISBN of the book that you want to pay fine
                string isbn;
                cout << "Enter ISBN of the book to payfine: ";
                getline(cin, isbn);
                // enter the amount of the fine
                int amount;
                cout << "Enter amount to pay: ";
                cin >> amount;
                cin.ignore();
                student->payFine(isbn,amount);
                cout << "Payment processed successfully." << endl;
                break;
            }
            case 9: {
                //View Your PaymentHistory
                student->displayPaymentHistory();
                break;
            }
            case 10: {
                //View Book details&History
                //Eneter the ISBN of the book to get details
                string isbn;
                cout << "Enter ISBN of the book to borrow: ";
                getline(cin, isbn);
                cout<<endl;
                Book* book = library->getBook(isbn);
                if(!book){
                    break;
                }
                //print book details
                book->details();
                // print History of Book
                book->printHistory();
                break;
            }
            case 11: {
                loggedIn = false;
                cout << "Logging out..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

// Faculty menu options
void facultyMenu(Faculty* faculty, LibraryManagement *library) {
    int choice;
    bool loggedIn = true;
    while(loggedIn) {
        cout << "\n---- Faculty Menu ----" << endl;
        cout << "1. View All Books" << endl;
        cout << "2. View Available Books" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. View currently borrowed books" << endl;
        cout << "6. View History" << endl;
        cout << "7. View Overdue Books" << endl;
        cout << "8. View Book details&History" << endl;
        cout << "9. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;                 // Skip the rest of the loop and ask again

        }
        cin.ignore();
        cout<<endl;
        
        switch(choice) {
            case 1: {
                // printing all books
                library->printAllBooks();
                break;
            }
            case 2: {
                // printing available Books
                library->printAvailableBooks();
                break;
            }
            case 3: {
                // Borrow Book
                string isbn;
                cout << "Enter ISBN of the book to borrow: ";
                getline(cin, isbn);
                cout<<endl;
                Book* book = library->getBook(isbn);
                if(!book){
                    break;
                }
                if(book && book->isAvailable()) {
                    faculty->borrowBook(book);
                }
                else if(faculty->hasBorrowedBook(book)){
                    cout <<endl<< "You have already Borrowed this Book !" << endl;
                }
                else if(book->isBorrowedBook()){
                    cout <<endl<< "this Book is not available currently!" << endl;
                }
                else if(book->isReserved()){
                    cout <<endl<< "This Book is Reserved!, You cannot Borrow this Book" << endl;
                }
                break;
            }
            case 4: {
                // return Book
                faculty->displayCurrBorrowedBooks();
                string isbn;
                cout << "Enter ISBN of the book to return: ";
                getline(cin, isbn);
                Book* book = library->getBook(isbn);
                if(book) {
                    faculty->returnBook(book);
                } else {
                    cout << "Invalid ISBN entered." << endl;
                }
                break;
            }
            case 5: {
                // View currently borrowed books
                faculty->displayCurrBorrowedBooks();
                break;
            }
            case 6: {
                //View History
                faculty->displayHistory();
                break;
            }
            case 7: {
                //display overduebooks
                faculty->displayOverdueBooks();
                // }
                break;
            }
            case 8: {
                //View Book details&History
                string isbn;
                cout << "Enter ISBN of the book to get details: ";
                getline(cin, isbn);
                cout<<endl;
                Book* book = library->getBook(isbn);
                if(!book){
                    break;
                }
                //print book details
                book->details();
                // print History of Book
                book->printHistory();
                break;
            }
            case 9: {
                loggedIn = false;
                cout << "Logging out..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

// Librarian menu options
void librarianMenu(Librarian* librarian, LibraryManagement *library) {
    int choice;
    bool loggedIn = true;
    while(loggedIn) {
        cout << "\n---- Librarian Menu ----" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Update Book" << endl;
        cout << "4. Add New User" << endl;
        cout << "5. Remove User" << endl;
        cout << "6. Reserve Book" << endl;
        cout << "7. Unreserve Book" << endl;
        cout << "8. View All Books" << endl;
        cout << "9. View Available Books" << endl;
        cout << "10.View All Users"<<endl;
        cout << "11. View Book details&History" << endl;
        cout << "12. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;                 // Skip the rest of the loop and ask again

        }
        cin.ignore();
        cout<<endl;
        switch(choice) {
            case 1: {
                //enter book details
                string title, author, publisher, isbn, year;
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Publisher: ";
                getline(cin, publisher);
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                cout << "Enter Year: ";
                getline(cin, year);
                //add book to library
                librarian->addBook(*library, title, author, publisher,stoi(year) ,isbn);
                break;
            }
            case 2: {
                //remove book
                string isbn;
                cout << "Enter ISBN of the book to remove: ";
                getline(cin, isbn);
                librarian->removeBook(*library, isbn);
                break;
            }
            case 3: {
                //updating book
                string isbn, field, value;
                cout << "Enter ISBN of the book to update: ";
                getline(cin, isbn);
                Book* book=library->getBook(isbn);
                if(!book){
                    cout<<"Book doesnot Exist"<<endl;
                    break;
                }
                book->details();
                // if Book is borrowed then it cannot be updated
                if(book->isBorrowedBook()){
                    cout<<"Book is currently Borrowed! cannot update now"<<endl;
                    break;
                }
                // enter field and value of that field to update book
                cout << "Enter field to update (Title, Author, Publisher, Year,ISBN): ";
                getline(cin, field);
                cout << "Enter new value: ";
                getline(cin, value);
                librarian->updateBook(*library, isbn, field, value);
                break;
            }
            case 4: {
                // add user
                string name, userId, role, password;
                cout << "Enter User Name: ";
                getline(cin, name);
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Role (student/faculty/librarian): ";
                getline(cin, role);
                cout << "Enter Password: ";
                getline(cin, password);
                librarian->addUser(*library, name, role,userId,password);
                //cout << "User added successfully." << endl;
                break;
            }
            case 5: {
                //remove user
                string userId;
                cout << "Enter User ID of the user to remove: ";
                getline(cin, userId);
                librarian->removeUser(*library, userId);
                //cout << "User removed successfully." << endl;
                break;
            }
            case 6: {
                // reserve book
                string isbn;
                cout << "Enter ISBN of the book to reserve: ";
                getline(cin, isbn);
                librarian->reserveBook(library->getBook(isbn));
                //cout << "Book reserved successfully." << endl;
                break;
            }
            case 7: {
                // unreserve book
                string isbn;
                cout << "Enter ISBN of the book to unreserve: ";
                getline(cin, isbn);
                librarian->deReserveBook(library->getBook(isbn));
                //cout << "Book unreserved successfully." << endl;
                break;
            }
            case 8: {
                //printing all books
                library->printAllBooks();
                break;
            }
            case 9: {
                //printing available books
                library->printAvailableBooks();
                break;
            }
            case 10: {
                //printing all users{userID,name,role}
                library->printAllUsers();
                break;
            }
            case 11: {
                string isbn;
                cout << "Enter ISBN of the book get details: ";
                getline(cin, isbn);
                cout<<endl;
                Book* book = library->getBook(isbn);
                if(!book){
                    break;
                }
                //print book details
                book->details();
                // print History of Book
                book->printHistory();
                break;
            }
            case 12: {
                loggedIn = false;
                cout << "Logging out..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void clearAllcsv(){
    // function to clear all csvfile
    clearCSV("books.csv");
    clearCSV("students.csv");
    clearCSV("bookHistory.csv");
    clearCSV("faculty.csv");
    clearCSV("librarians.csv");
}
int main() {
    //clearAllcsv();
    LibraryManagement* library = new LibraryManagement();
    // If no data exists, initialize with default records.
    //initializeLibrary(*library);
    
    loadAllData(library);
    
    int mainChoice;
    bool exitProgram = false;
    
    while(!exitProgram) {
        cout << "\n==== Library Management System ====" << endl;
        cout << "1. Student Login" << endl;
        cout << "2. Faculty Login" << endl;
        cout << "3. Librarian Login" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> mainChoice;
        //add
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;                 // Skip the rest of the loop and ask again

        }
        cin.ignore();
        
        string userId, password;
        User* user = nullptr;
        
        switch(mainChoice) {
            case 1: {
                // Enter User Id and password  for authentication
                cout << "\n-- Student Login --" << endl;
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Password: ";
                getline(cin, password);
                user = library->getUser(userId);
                if(user && dynamic_cast<Student*>(user)) {
                    if(user->getPassword() == password) {
                        studentMenu(dynamic_cast<Student*>(user), library);
                    } else {
                        cout << "Invalid password." << endl;
                    }
                } else {
                    cout << "User not found or not registered as a student." << endl;
                }
                break;
            }
            case 2: {
                // Enter User Id and password  for authentication
                cout << "\n-- Faculty Login --" << endl;
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Password: ";
                getline(cin, password);
                user = library->getUser(userId);
                if(user && dynamic_cast<Faculty*>(user)) {
                    if(user->getPassword() == password) {
                        facultyMenu(dynamic_cast<Faculty*>(user), library);
                    } else {
                        cout << "Invalid password." << endl;
                    }
                } else {
                    cout << "User not found or not registered as faculty." << endl;
                }
                break;
            }
            case 3: {
                // Enter User Id and password  for authentication
                cout << "\n-- Librarian Login --" << endl;
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Password: ";
                getline(cin, password);
                user = library->getUser(userId);
                if(user && dynamic_cast<Librarian*>(user)) {
                    if(user->getPassword() == password) {
                        librarianMenu(dynamic_cast<Librarian*>(user), library);
                    } else {
                        cout << "Invalid password." << endl;
                    }
                } else {
                    cout << "User not found or not registered as a librarian." << endl;
                }
                break;
            }
            case 4: {
                //Exit program
                exitProgram = true;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    // Save current data to files before exiting
    saveAllData(library); 
    
    cout << "Exiting Library Management System. Goodbye!" << endl;
    return 0;
}