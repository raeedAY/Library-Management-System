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
    
    // put ur implementation here
}

void editBook(const string& ISBN) {
    clearScreen();
    // put ur implementation here
}

void removeBook(const string& ISBN) {
    clearScreen();
    // put ur implementation here
}

vector<Book> listAllBooks() {
    // put ur implementation here
}

bool saveBooks() {
    // put ur implementation here
}

bool loadBooks() {
    // put ur implementation here
}

bool isBookAvailable(const string& ISBN) {
    // put ur implementation here
}
