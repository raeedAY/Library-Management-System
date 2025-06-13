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
    
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    book.status = "available";
    
    ofstream outFile("data/books.txt", ios::app);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open books.txt for writing." << endl;
        return;
    }
    
    outFile << book.ISBN << "|" << book.title << "|" << book.author << "|"
            << book.genre << "|" << book.quantity << "|" << book.status << endl;
    
    outFile.close();
    cout << "Book added successfully!" << endl;
}

void editBook(const string& ISBN) {
    clearScreen();
    vector<Book> books = listAllBooks();
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
    vector<Book> books = listAllBooks();
    
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
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return false;
        }
    }
    
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

vector<Book> listAllBooks() {
    vector<Book> books;
    
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return books;
        }
    }
    
    ifstream inFile("data/books.txt");
    
    if (!inFile.is_open()) {
        ofstream outFile("data/books.txt");
        if (outFile.is_open()) {
            outFile << "1|The Catcher in the Rye|J.D. Salinger|Fiction|5|available" << endl;
            outFile << "2|To Kill a Mockingbird|Harper Lee|Fiction|3|available" << endl;
            outFile << "3|1984|George Orwell|Fiction|4|available" << endl;
            outFile << "4|The Da Vinci Code|Dan Brown|Mystery|2|available" << endl;
            outFile << "5|The Hobbit|J.R.R. Tolkien|Fantasy|6|available" << endl;
            outFile.close();
            
            inFile.open("data/books.txt");
            if (!inFile.is_open()) {
                return books;
            }
        } else {
            return books;
        }
    }

    string line;
    while (getline(inFile, line)) {
        Book book;
        size_t pos = 0;
        string token;
        vector<string> tokens;
        
        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);
        
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

bool isBookAvailable(const string& ISBN) {
    vector<Book> books = listAllBooks();
    for (const auto& book : books) {
        if (book.ISBN == ISBN) {
            return book.quantity > 0 && book.status == "available";
        }
    }
    return false;
}

