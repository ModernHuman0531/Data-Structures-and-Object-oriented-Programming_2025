#define HW2
#ifdef HW2

#include "Book.h"
#include "Library.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void displayMenu(){
    cout << "\nLibrary Management System" << endl;
    cout << "1. Add a new book" << endl;
    cout << "2. Search for a book" << endl;
    cout << "3. Check out a book" << endl;
    cout << "4. Return a book" << endl;
    cout << "5. List all books" << endl;
    cout << "6. Check borrowed books" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

void addBook(Library& library){
    int copies;
    string bookName, author, genre, overview, pubYear;
    cout << "---------------------- Add New Book ---------------------" << endl;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookName); // Use getline for the input to allow spaces in the book title
    cout << "Enter author: ";
    getline(cin, author); // Use getline for the input to allow spaces in the author's name
    cout << "Enter genre: ";
    getline(cin, genre); // Use getline for the input to allow spaces in the genre
    cout << "Enter overview: ";
    getline(cin, overview); // Use getline for the input to allow spaces in the overview
    cout << "Enter publication year: ";
    cin >> pubYear;
    cout << "Enter number of copies: ";
    cin >> copies;
    try{
        Book* book = new Book(copies, pubYear, bookName, author, genre, overview);
        library.addBook(book);
        cout << "Book added to the library." << endl;
    }
    catch(const runtime_error& e){
        cout << "Error: " << e.what() << endl;
    }
    // Sort the books by title after every addition
    library.sortBooksByTitle();
}

void searchBook(Library& library){
    cout << "--------------------- Search Book ---------------------" << endl;
    cout << "1. Search by name" << endl;
    cout << "2. Search by genre" << endl;
    cout << "3. Search by publication year" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch(choice){
        case 1: {
            string name;
            cout << "Enter book name: ";
            cin.ignore();
            getline(cin, name); // Use getline for the input to allow spaces in the book name
            library.searchBook("", "", name);
            break;
        }
        case 2: {
            string genre;
            cout << "Enter genre of the book: ";
            cin.ignore();
            getline(cin, genre); // Use getline for the input to allow spaces in the genre
            library.searchBook("", genre, "");
            break;
        }
        case 3: {
            string pubYear;
            cout << "Enter the publication year of the book: ";
            cin >> pubYear;
            library.searchBook(pubYear, "", "");
            break;
        }
        default:
        cout << "Invalid choice." << endl;
        break;
    }
    return;
}

void checkOutBook(Library& library){
    string bookName;
    cout << "--------------------- Check Out Book ---------------------" << endl;
    cout << "Enter the title of the book to check out: ";
    cin.ignore();
    getline(cin, bookName); // Use getline for the input to allow spaces in the book title
    try{
        library.borrowBook(bookName);
    }
    catch(const runtime_error& e){
        cout << "Error: " << e.what() << endl;
    }
    library.sortBorrowedBooksByTitle();
    return;
}

void returnBook(Library& library){
    string bookName;
    cout << "--------------------- Return Book ---------------------" << endl;
    cout << "Enter the title of the book to return: ";
    cin.ignore();
    getline(cin, bookName); // Use getline for the input to allow spaces in the book title
    try{
        library.returnBook(bookName);
    }
    catch(const runtime_error& e){
        cout << "Error: " << e.what() << endl;
    }
    library.sortBorrowedBooksByTitle();    
    return;
}

void listAllBooks(const Library& library){
    cout << "--------------------- List All Books ---------------------" << endl;
    library.ListAllBooks();
    return;
}

void checkBorrowedBooks(const Library& library){
    cout << "--------------------- Borrowed Books ---------------------" << endl;
    // Want to list all the borrowed books by the book's title from smallest to largest
    try{
        library.ListBorrowedBooks();
    }
    catch(const runtime_error& e){
        cout << "Error: " << e.what() << endl;
    }
}

int main(){
    Library library;
    int choice;

    do{
        displayMenu();
        cin >> choice;

        switch(choice){
            case 1:
                addBook(library);
                break;

            case 2:
                searchBook(library);
                break;
            
            case 3:
                checkOutBook(library);
                break;
            
            case 4:
                returnBook(library);
                break;

            case 5:
                listAllBooks(library);
                break;

            case 6:
                checkBorrowedBooks(library);
                break;
            
            case 7:
                cout << "Exit library management system. Thank you!!!" << endl;
                break;
        }
    }
    while(choice != 7);
    return 0;
} 


#endif