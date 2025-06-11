#include "../include/bookManagement.h"
#include "../include/member.h"
#include "../include/ui.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
    bool bookFound = false;
    
    for (auto& book : books) {
        if (book.ISBN == ISBN) {
            bookFound = true;
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
    if(!bookFound){
        cout << "Book with ISBN " << ISBN << " not found." << endl;
        return;
    }
     
    ofstream outFile("data/books.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open books.txt for writing." << endl;
        return;
    }

    for (const Book& b : books) {
        outFile << b.ISBN << "|" << b.title << "|" << b.author << "|"
                << b.genre << "|" << b.quantity << "|" << b.status << endl;
    }

    outFile.close();
}

void removeBook(const string& ISBN) {
    clearScreen();
    vector<Book> books = loadBooks();
    
    auto it = find_if(books.begin(), books.end(),
                     [&ISBN](const Book& book) { return book.ISBN == ISBN; });
    
    if (it != books.end()) {
        books.erase(it);
        if (saveBooks(books)) {
            cout << "Book deleted successfully.\n";
        } else {
            cout << "Error: Failed to save changes after deleting the book.\n";
        }
    } else {
        cout << "Book not found.\n";
    }
}

bool saveBooks(const vector<Book>& books) {
    ofstream outFile("data/books.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open books.txt for writing." << endl;
        return false;
    }

    for (const Book& book : books) {
        outFile << book.ISBN << "|" << book.title << "|" << book.author << "|"
                << book.genre << "|" << book.quantity << "|" << book.status << endl;
    }

    outFile.close();
    return true;
}

vector<Book> loadBooks() {
    vector<Book> books;
    ifstream inFile("data/books.txt");
    
    if (!inFile.is_open()) {
        cerr << "Warning: Could not open books.txt for reading. Starting with empty book list." << endl;
        return books;
    }

    string line;
    while (getline(inFile, line)) {
        Book book;
        size_t pos = 0;
        string token;
        vector<string> tokens;
        
        // Split line by '|' delimiter
        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line); // Add the last token
        
        if (tokens.size() == 6) {
            book.ISBN = tokens[0];
            book.title = tokens[1];
            book.author = tokens[2];
            book.genre = tokens[3];
            book.quantity = stoi(tokens[4]);
            book.status = tokens[5];
            books.push_back(book);
        }
    }

    inFile.close();
    return books;
}

