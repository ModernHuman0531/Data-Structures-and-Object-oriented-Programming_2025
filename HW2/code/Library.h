#define LIBRARY_H
#ifdef LIBRARY_H

// Import necessary libraries
#include "Book.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Library {
    protected:
        vector<Book*> lib;
        vector<Book*> borrowedBooks; // Vector to store the borrowed books

        // Create merge sort function to sort the books by title
        void merge(vector<Book*>& books, int left, int mid, int right){
            // Set number of books in left and right vector
            int num1 = mid - left + 1;
            int num2 = right - mid;

            // Create temporary vectors to store the books
            vector<Book*> leftBooks(num1);
            vector<Book*> rightBooks(num2);

            // Copy the books into the temoprary vectors
            for(int i = 0;i < num1;++i){
                leftBooks[i] = books[left + i];
            }
            for(int i = 0;i < num2;++i){
                rightBooks[i] = books[mid + 1 + i];
            }
            
            int i = 0, j = 0, k = left;
            // Merge the two vectors
            while(i < num1 && j < num2){
                // Compare the titles of the books
                if(leftBooks[i] -> getBookName() <= rightBooks[j] -> getBookName()){
                    books[k] = leftBooks[i];
                    ++i;
                }
                else{
                    books[k] = rightBooks[j];
                    ++j;
                }
                ++k;
            }

            // Copy the remaining books from the left vector
            if(i < num1){
                while(i < num1){
                    books[k] = leftBooks[i];
                    ++i;
                    ++k;
                }
            }

            // Copy the remaining books from the right vector
            if(j < num2){
                while(j < num2){
                    books[k] = rightBooks[j];
                    ++j;
                    ++k;
                }
            }
        }

        // Merge sort function to sort the books by title
        void mergeSort(vector<Book*>& books, int left, int right){
            int mid = left + (right - left) / 2;
            // Left must bigger than right or else the recursion stop 
            if(left < right){
                mergeSort(books, left, mid);
                mergeSort(books, mid + 1, right);

                // Merge the two sorted vectors
                merge(books, left, mid, right);
            }
        }

    public:
        // Constructor
        Library(){}
        // Destructor
        ~Library() {empty_library();}
        void empty_library(){
            for(auto book : lib){
                delete book;
            }
            lib.clear();
        }

        // Function to add a book into the library
        void addBook(Book* book){
            if(book == nullptr){
                throw runtime_error("Invalid book.");
            }
            else{
                // Push the book into the library
                lib.push_back(book);
            }
        }

        // Function to sort the books in the library in  lexicographical order by the book's title from smallest to largest
        void sortBooksByTitle(){
            // Don't need to sort when the library is empty or only have one book
            if(lib.size() <= 1){return;}
            // Call the merge sort function to sort the books by title
            mergeSort(lib, 0, lib.size() - 1);
        }
        /* Function to search book by name or genre or publish_year
        1.We can search book by name, genre or publish year
        2. If the book is found, display the book's informtion
        */
        void searchBook(const string& pubYearfilter = "", const string& genrefilter = "", const string& namefilter = ""){
            // Check if the library is empty
            if(lib.empty()){
                cout << "No books is available in the library." << endl;
                return;
            }
            int count = 0; // Count the number of books that match the filter
            for(auto book : lib){
                // Check if the book matches the filter
                bool pubYearMatch = pubYearfilter.empty() || (book -> getPubYear() == pubYearfilter);
                bool genreMatch = genrefilter.empty() || (book -> getGenre() == genrefilter);
                bool nameMatch = namefilter.empty() || (book -> getBookName() == namefilter);
                // Once the book matches the filter, display the book's information
                if(pubYearMatch && genreMatch && nameMatch){
                    book -> display();
                    ++count; // Increase the count of the matching books
                }
            }
            // If no book matches the filter, display a message
            if(count == 0){
                cout << "No matching books found in the library." << endl;
            }
        }

        /*
        Library support burrrowing book, we can borrow a book if the book is available
        1. Check the books of copy number, if the book is available, we can borrow it
        2. If the book is not available, display a message
        3. If the book is available, we can borrow it, set the borrow date and due date
        4. The borrow date is the current date, and the due date is 14 days after the borrow date
        5. Add the book to the borrowed books vector
        6. Decrease the copy number of the book by 1
        7. Display a message that the book is borrowed successfully
        8. If the book is not found, display a message
        */
        void borrowBook(const string& bookName){
            int count = 0;
            // Search for the book in the library
            for(auto book : lib){
                // If the book is found
                if(book -> getBookName() == bookName){
                    // Check if the book is available(numbers of copies > 0)
                    if(book -> getCopyNumber() > 0){
                        // Set tge borrow date to the current date
                        time_t now = time(0); // Get the current time(in seconds)
                        tm* borrowDate = localtime(&now); // Convert time to tm structure
                        book -> setBorrowDate(*borrowDate); // Set the borrow date of the book
                        
                        //Set the due date to 14 days after the borrow date
                        tm* dueDate = borrowDate; // Copy the borrow date
                        dueDate -> tm_mday += 14; // Add 14 days to the borrow date
                        mktime(dueDate); // Normalize the due date
                        book -> setDueDate(*dueDate); // Set the due date of the book

                        // Add the book to the borrowed books vector
                        borrowedBooks.push_back(book);

                        // Decrease the book's copies by 1
                        book -> setCopyNumber(book -> getCopyNumber() - 1);

                        // Display a message that the book is borrowed successfully
                        cout << "Book '" << bookName << "' borrowed successfully!" << endl;
                        cout << "Borrow Date: " << (book -> getBorrowDate().tm_mon + 1) << "/"
                            << book -> getBorrowDate().tm_mday << "/"
                            << (book -> getBorrowDate().tm_year + 1900) << endl;

                        // Display the due date
                        cout << "Due date: "  << (book -> getDueDate().tm_mon + 1) << "/"
                            << book -> getDueDate().tm_mday << "/"
                            << (book -> getDueDate().tm_year + 1900) << endl;
                        
                        count++;
                    }

                    // If the book is not available, display a message
                    else{
                        cout << "Sorry, the book is currently checked out." << endl;
                    }
                }
            }

            if(count == 0){
                // If the book is not found, display a message
                cout << "Book '" << bookName << "' not found in the library." << endl;
            }
            return;
        }


        /*
        Library also returning books. When a book is returned:
        1. Find all the books in the matching title in borrowedBooks vector
        2. Display all the books with index for selection
        3. Let user choose which copy to return
        4. Increase the copy number of the book in the library by 1
        5. Remove the book from the borrowedBooks vector
        6. Display a message that the book is returned successfully
        */
        void returnBook(const string& bookName){
            // Check if there are any borrowed books
            if(borrowedBooks.empty()){
                cout << "No books have been borrowed." << endl;
                return;
            }

            // Find all the books in the borrowedBooks vector that match the bookName
            // Store the indices of the matching books
            vector<pair<int, Book*>> matchingBooks;
            for(int i = 0; i < borrowedBooks.size(); ++i){
                // If the book's name matches the bookName
                if(borrowedBooks[i] -> getBookName() == bookName){
                    // Add the book and its index to the matchingBooks vector
                    matchingBooks.push_back(make_pair(i, borrowedBooks[i]));
                }
            }

            // If no matching books are found, display a message
            if(matchingBooks.empty()){
                cout << "No book titled ' " << bookName << " ' has been borrowed." << endl;
                return;
            }

            // If only one matching book is found, return it directly
            if(matchingBooks.size() == 1){
                // Increase the copy number of the book in library by 1
                /* Important concept, stuck this concept for a while
                1. When we borrow the book in the borrowBook function, we don't create new Book object pointer.
                2. Instead we directly put the same pointer into the borrowedBooks vector
                3. So when we return the book, we can directly access the book in the library by using the same pointer
                */
               int index = matchingBooks[0].first; // Get the index of the book in the borrowedBooks vector
               Book* book = borrowedBooks[index]; // Get the book pointer from the borrowedBooks vector

               // Increase the copy by one
               book -> setCopyNumber(book -> getCopyNumber() + 1);

               // Remove the book from the borrowedBooks vector
               borrowedBooks.erase(borrowedBooks.begin() + index);

               // Display a message that the book is returned successfully
               cout << "Book '" << bookName << "' returned successfully!" << endl;
               return;
            }

            // Multiple matching books found, display them with indices
            else{
                cout << "Multiple copies of '" << bookName << "' are borrowed. Please select the copy to return:" << endl;

                // List all the matching books with their indices and details
                for(int i = 0; i < matchingBooks.size(); ++i){
                    Book* book = matchingBooks[i].second; // Get the book pointer
                    cout << i + 1 << ". " << book -> getBookName() << endl;
                    cout << "Borrowed on: "
                        << (book -> getBorrowDate().tm_mon + 1) << "/"
                        << (book -> getBorrowDate().tm_mday) << "/"
                        << (book -> getBorrowDate().tm_year + 1900) << endl;
                    cout << "Due date: " 
                        << (book -> getDueDate().tm_mon + 1) << "/"
                        << (book -> getDueDate().tm_mday) << "/"
                        << (book -> getDueDate().tm_year + 1900) << endl;
                }
            }

            int choice;
            cout << "Enter the number of the copy to return: ";
            cin >> choice;

            // Validate the choice
            if(choice < 1 || choice > matchingBooks.size()){
                cout << "Invalid choice. No book returned." << endl;
                return;
            }

            // Process the selected book
            int selectedIndex = matchingBooks[choice - 1].first; // Get the index of the selected book
            Book* selectedBook = borrowedBooks[selectedIndex]; // Get the book pointer

            // Increase the copy number of the book in the library by 1
            selectedBook -> setCopyNumber(selectedBook -> getCopyNumber() + 1);

            // Remove the book from the borrowedBooks vector
            borrowedBooks.erase(borrowedBooks.begin() + selectedIndex);

            // Display a message that the book is returned successfully
            cout << "Book ' " << bookName << " ' returned successfully!" << endl;
            return;
        }

        void ListAllBooks() const{
            // Check if the library is empty
            if(lib.empty()){
                cout << "No books in the library." << endl;
                return;
            }

            // Display all the books in the library
            cout << "Library Books: " << endl;
            for(const auto& book : lib){
                book -> display();
                cout << endl;
            }
        }

};

#endif