#ifndef BOOK_MANAGEMENT_H
#define BOOK_MANAGEMENT_H

#include <string>
#include <vector>

using namespace std;

struct Book {
    string ISBN;
    string title;
    string author;
    string genre;
    int quantity;
    string status; // available, borrowed, lost
};

void addBook(Book& book);
void editBook(const string& ISBN);
void removeBook(const string& ISBN);
vector<Book> listAllBooks();
bool saveBooks();
bool loadBooks();
bool isBookAvailable(const string& ISBN);

    // add ur definitions here

#endif 