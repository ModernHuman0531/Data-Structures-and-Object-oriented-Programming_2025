#define BOOK_H
#ifdef BOOK_H

// Import necessary libraries
#include <iostream>
#include <string>
#include <ctime>

using namespace std;
/*
Book contents:
1. Publish year
2. Author
3. Number of available copies
4. Genre
5. Overview
6. Borrow date
7. Due date
*/
class Book{
    protected:
        int pub_year;
        int copy_number;
        string book_name;
        string author;
        string genre;
        string overview;
        tm borrow_date;
        tm due_date;
    public:
        // Constructor
        Book(int year, int copies,const string& name,  const string& authorName, const string& bookGenre, const string& bookOverview):
            pub_year{year}, copy_number{copies}, book_name{name},author{authorName}, genre{bookGenre}, overview{bookOverview}{}
        
        // Destructor
        ~Book(){}

        // Getters
        int getPubYear() const{return pub_year;}
        int getCopyNumber() const{return copy_number;}
        string getBookName() const{return book_name;}
        string getAuthor() const{return author;}
        string getGenre() const{return genre;}
        string getOverview() const{return overview;}
        const tm getBorrowDate() const{return borrow_date;}
        const tm getDueDate() const{return due_date;}

        // Setters
        void setPubYear(int year) {pub_year = year;}
        void setCopyNumber(int copies) {copy_number = copies;}
        void setBookName(const string& name) {book_name = name;}
        void setAuthor(const string& authorName) {author = authorName;}
        void setGenre(const string& bookGenre) {genre = bookGenre;}
        void setOverview(const string& bookOverview) {overview = bookOverview;}
        void setBorrowDate(const tm& date) {borrow_date = date;}
        void setDueDate(const tm& date) {due_date = date;}

        // Display function to display book's information
        void display() const {
            cout << "\nTitle: " << book_name << endl
            << "Author: " << author << endl
            << "Genre: " << genre << endl
            << "Available Copies: " << copy_number << endl
            << "Book's Overview: " << overview << endl;
        }
};


#endif