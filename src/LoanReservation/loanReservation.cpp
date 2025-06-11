#include "../../include/loanReservation.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool borrowBook(const Member& member, const string& ISBN) {
    clearScreen();
    // put ur implementation here
}

bool returnBook(const Member& member, const string& ISBN) {
    clearScreen();

    vector<Book> books = listAllBooks();
    
    for (const auto& book : books) {
        if (book.ISBN == ISBN) {
            // Check if the book's status is "available"
            return book.status == "available";
        }
    }
    
    return false;
}
 

vector<Book> viewBorrowedBooks(const Member& member) {
    clearScreen();
    // put ur implementation here
}

bool reserveBook(const Member& member, const string& ISBN) {
    clearScreen();
    // put ur implementation here
}

bool cancelReservation(const Member& member, const string& ISBN) {
    clearScreen();
    // put ur implementation here
}

vector<Book> viewReservedBooks(const Member& member) {
    clearScreen();
    // put ur implementation here
}
