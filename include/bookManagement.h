#ifndef BOOK_MANAGEMENT_H
#define BOOK_MANAGEMENT_H

#include <string>
#include <vector>
#include "book.h"

using namespace std;

struct Book {
    string ISBN;
    string title;
    string author;
    string genre;
    int quantity;
    string status; // available, borrowed, lost
    int borrowCount = 0; // Track number of times book has been borrowed
};

void addBook(Book& book);
void editBook(const string& ISBN);
void removeBook(const string& ISBN);
vector<Book> listAllBooks();
vector<Book> loadBooks();
bool saveBooks(const vector<Book>& books);
bool isBookAvailable(const string& ISBN);

    // add ur definitions here

#endif 