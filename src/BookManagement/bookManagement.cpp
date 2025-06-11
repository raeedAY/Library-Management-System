#include "../../include/bookManagement.h"
#include "../../include/member.h"
#include "../../include/ui.h"

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
    vector<Book> books = listAllBooks();
    
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
    // Implementation to be added 
}

vector<Book> listAllBooks() {
    vector<Book> books;
    // Implementation to be added 
    return books;
}

bool saveBooks() {
    // Implementation to be added 
    return true;
}

bool loadBooks() {
    // Implementation to be added
    return true;
}

bool isBookAvailable(const string& ISBN) {
    vector<Book> books = listAllBooks();
    
    for (const auto& book : books) {
        if (book.ISBN == ISBN) {
            // Check if the book's status is "available"
            return book.status == "available";
        }
    }
    
    return false;
}
