#include "../../include/loanReservation.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Simple structure to track reservations
struct ReservationEntry {
    string ISBN;
    int memberId;
};

// Vector to store all reservations
vector<ReservationEntry> reservations;

// Helper function to save reservations
void saveReservations() {
    ofstream file("data/reservations.txt");
    if (file.is_open()) {
        for (const auto& res : reservations) {
            file << res.ISBN << "|" << res.memberId << endl;
        }
        file.close();
    }
}

// Helper function to load reservations
void loadReservations() {
    reservations.clear();
    ifstream file("data/reservations.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                ReservationEntry entry;
                entry.ISBN = line.substr(0, pos);
                entry.memberId = stoi(line.substr(pos + 1));
                reservations.push_back(entry);
            }
        }
        file.close();
    }
}

bool borrowBook(const Member& member, const string& ISBN) {
    clearScreen();
    // put ur implementation here
    return true;
}

bool returnBook(const Member& member, const string& ISBN) {
    clearScreen();
    
    // First check if the book exists and update its status
    vector<Book> books = listAllBooks();
    bool bookFound = false;
    
    for (const auto& book : books) {
        if (book.ISBN == ISBN) {
            bookFound = true;
            // Check if anyone has reserved this book
            loadReservations();
            for (const auto& res : reservations) {
                if (res.ISBN == ISBN) {
                    cout << "Notification: Book " << ISBN << " is now available for member " << res.memberId << endl;
                    break;
                }
            }
            break;
        }
    }
    
    if (!bookFound) {
        cout << "Book with ISBN " << ISBN << " not found." << endl;
        return false;
    }
    
    cout << "Book returned successfully!" << endl;
    return true;
}
 

vector<Book> viewBorrowedBooks(const Member& member) {
    clearScreen();
    // put ur implementation here
    vector<Book> books;
    return books;
}

bool reserveBook(const Member& member, const string& ISBN) {
    clearScreen();
    
    // Load current reservations
    loadReservations();
    
    // Check if book exists and is unavailable
    vector<Book> books = listAllBooks();
    bool bookFound = false;
    
    for (const auto& book : books) {
        if (book.ISBN == ISBN) {
            bookFound = true;
            if (book.status == "available") {
                cout << "Book is currently available. You can borrow it directly." << endl;
                return false;
            }
            break;
        }
    }
    
    if (!bookFound) {
        cout << "Book with ISBN " << ISBN << " not found." << endl;
        return false;
    }
    
    // Check if member already has a reservation
    for (const auto& res : reservations) {
        if (res.ISBN == ISBN && res.memberId == member.Id) {
            cout << "You already have a reservation for this book." << endl;
            return false;
        }
    }
    
    // Add new reservation
    ReservationEntry newRes{ISBN, member.Id};
    reservations.push_back(newRes);
    saveReservations();
    
    cout << "Book reserved successfully! You will be notified when it becomes available." << endl;
    return true;
}

bool cancelReservation(const Member& member, const string& ISBN) {
    clearScreen();
    
    loadReservations();
    bool found = false;
    
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->ISBN == ISBN && it->memberId == member.Id) {
            reservations.erase(it);
            found = true;
            break;
        }
    }
    
    if (found) {
        saveReservations();
        cout << "Reservation cancelled successfully!" << endl;
        return true;
    }
    
    cout << "No reservation found for this book." << endl;
    return false;
}

vector<Book> viewReservedBooks(const Member& member) {
    clearScreen();
    
    loadReservations();
    vector<Book> reservedBooks;
    vector<Book> allBooks = listAllBooks();
    
    for (const auto& res : reservations) {
        if (res.memberId == member.Id) {
            for (const auto& book : allBooks) {
                if (book.ISBN == res.ISBN) {
                    reservedBooks.push_back(book);
                    cout << "Book: " << book.title << " (ISBN: " << book.ISBN << ")" << endl;
                    cout << "Status: Reserved" << endl;
                    cout << "------------------------" << endl;
                    break;
                }
            }
        }
    }
    
    if (reservedBooks.empty()) {
        cout << "You have no reserved books." << endl;
    }
    
    return reservedBooks;
}
