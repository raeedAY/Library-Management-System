#include "../include/bookManagement.h"
#include "../include/member.h"
#include "../include/ui.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

void addBook(Book& book) {
    clearScreen();
    
    // make sure that data/ exists
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    // Set initial status as available when adding a new book
    book.status = "available";
    cout << "New book status set to: " << book.status << endl;
}

void editBook(const string& ISBN) {
    clearScreen();
    vector<Book> books = loadBooks();
    
    for (auto& book : books) {
        if (book.ISBN == ISBN) {
            cout << "Current book status: " << book.status << endl;
            cout << "Enter new status (available/borrowed/lost): ";
            string newStatus;
            getline(cin, newStatus);
            
            if (newStatus == "available" || newStatus == "borrowed" || newStatus == "lost") {
                book.status = newStatus;
                cout << "Book status updated to: " << book.status << endl;
            } else {
                cout << "Invalid status. Valid options are: available, borrowed, lost" << endl;
            }
            break;
        }
    }
}

void removeBook(const string& ISBN) {
    clearScreen();
    vector<Book> books = loadBooks();
    
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->ISBN == ISBN) {
            books.erase(it);
            saveBooks(books);
            cout << "Book deleted successfully.\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

bool saveBooks(const vector<Book>& books) {
    // Implementation to be added 
    return true;
}

vector<Book> loadBooks() {
    vector<Book> books;
    // TODO: Implement actual loading logic
    return books;
}

