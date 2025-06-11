#include "../../include/bookManagement.h"
#include "../../include/member.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>

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
    bool bookfound = false;
    
    for (auto& book : books) {
        if (book.ISBN == ISBN) {
            bookfound = true;
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
    if(!bookfound){
        cout << "book with ISBN" << ISBN << " not found."<< endl;
        return;
    }
     
    ofstream outFile("data/books.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open books.txt for writing." << endl;
        return;
    }

    for (Book& b : books) {
        outFile << b.ISBN << "|" << b.title << "|" << b.author << "|"
                << b.genre << "|" << b.quantity << "|" << b.status << endl;
    }

    outFile.close();

}
void removeBook(const string& ISBN) {
    clearScreen();
    unordered_map<string, Book> books = loadBooks(); // Load books from storage
    auto it = books.find(ISBN);
    if (it != books.end()) {
        books.erase(it);
        saveBooks(books); // Save updated books to storage
        cout << "Book deleted successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}


bool saveBooks() {
    // Implementation to be added 
    return true;
}

bool loadBooks() {
    // Implementation to be added
    return true;
}

