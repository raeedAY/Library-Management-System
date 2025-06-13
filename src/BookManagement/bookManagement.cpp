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
            
            cout << "Editing Book: " << book.title << " (ISBN: " << book.ISBN << ")" << endl;
            cout << "1. Edit Title (Current: " << book.title << ")" << endl;
            cout << "2. Edit Author (Current: " << book.author << ")" << endl;
            cout << "3. Change Status (Current: " << book.status << ")" << endl;
            cout << "4. Cancel" << endl;
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (choice) {
                case 1:
                    cout << "Enter new title: ";
                    getline(cin, book.title);
                    break;
                case 2:
                    cout << "Enter new author: ";
                    getline(cin, book.author);
                    break;
                case 3: {
                    cout << "Select new status:" << endl;
                    cout << "1. Available" << endl;
                    cout << "2. Borrowed" << endl;
                    cout << "3. Lost" << endl;
                    cout << "Enter your choice: ";
                    int statusChoice;
                    cin >> statusChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch (statusChoice) {
                        case 1:
                            book.status = "available";
                            break;
                        case 2:
                            book.status = "borrowed";
                            break;
                        case 3:
                            book.status = "lost";
                            break;
                        default:
                            cout << "Invalid choice. Status not changed." << endl;
                    }
                    break;
                }
                case 4:
                    cout << "Edit cancelled." << endl;
                    return;
                default:
                    cout << "Invalid choice." << endl;
                    return;
            }
            
            break;
        }
    }
    
    if (!bookFound) {
        cout << "Book with ISBN " << ISBN << " not found." << endl;
        return;
    }
    
    ofstream outFile("data/books.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open books.txt for writing." << endl;
        return;
    }

    for (const Book& b : books) {
        outFile << b.ISBN << "|" << b.title << "|" << b.author << "|" << b.status << endl;
    }

    outFile.close();
    cout << "Book updated successfully!" << endl;
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

