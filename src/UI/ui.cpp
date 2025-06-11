#include "../../include/ui.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/memberManagement.h"
#include "../../include/loanReservation.h"
#include "../../include/reportingAnalytics.h"

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
}

void displayAdminMenu(const Member& loggedInUser) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "          ADMIN MENU                  " << endl;
    cout << "======================================" << endl;
    cout << "Welcome, " << loggedInUser.name << " (Admin)" << endl;
    cout << "--------------------------------------" << endl;
    cout << "1. Book Management" << endl;
    cout << "2. Member Management" << endl;
    cout << "3. Librarian Management" << endl;
    cout << "4. View Reports" << endl;
    cout << "5. System Settings" << endl;
    cout << "6. Logout" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1: {
            clearScreen();
            cout << "======================================" << endl;
            cout << "       BOOK MANAGEMENT                " << endl;
            cout << "======================================" << endl;
            cout << "1. Add New Book" << endl;
            cout << "2. Edit Book" << endl;
            cout << "3. Remove Book" << endl;
            cout << "4. Search Books" << endl;
            cout << "5. List All Books" << endl;
            cout << "6. Back to Main Menu" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Enter your choice: ";
            
            int bookChoice;
            cin >> bookChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (bookChoice) {
                case 1: {
                    Book newBook;
                    addBook(newBook);
                    break;
                }
                case 2:
                    // Edit book 
                    break;
                case 3:
                    // Remove book 
                    break;
                case 4:
                    // Search books
                    break;
                case 5:
                    // List all books
                    break;
                case 6:
                    displayAdminMenu(loggedInUser);
                    break;
                default:
                    cout << "Invalid choice. Press Enter to continue...";
                    cin.get();
                    displayAdminMenu(loggedInUser);
            }
            break;
        }
        case 2:
            // Member Management Menu
            break;
        case 3:
            // Librarian Management Menu
            break;
        case 4:
            // Reports Menu
            break;
        case 5:
            // System Settings Menu
            break;
        case 6:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Press Enter to continue...";
            cin.get();
            displayAdminMenu(loggedInUser);
    }
}

void displayLibrarianMenu(const Member& loggedInUser) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "         LIBRARIAN MENU               " << endl;
    cout << "======================================" << endl;
    cout << "Welcome, " << loggedInUser.name << " (Librarian)" << endl;
    cout << "--------------------------------------" << endl;
    cout << "1. Book Management" << endl;
    cout << "2. Loan Management" << endl;
    cout << "3. Member Management" << endl;
    cout << "4. Reports" << endl;
    cout << "5. Logout" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1: {
            clearScreen();
            cout << "======================================" << endl;
            cout << "       BOOK MANAGEMENT                " << endl;
            cout << "======================================" << endl;
            cout << "1. Add New Book" << endl;
            cout << "2. Edit Book" << endl;
            cout << "3. Search Books" << endl;
            cout<< " 4. Delete Book" <<endl;
            cout << "5. List All Books" << endl;
            cout << "6. Back to Main Menu" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Enter your choice: ";
            
            int bookChoice;
            cin >> bookChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (bookChoice) {
                case 1: {
                    Book newBook;
                    addBook(newBook);
                    break;
                }
                case 2:
                    // Edit book 
                    break;
                case 3:
                    // Search books
                    break;
                case 4:
                    // List all books
                    break;
                case 5:
                    displayLibrarianMenu(loggedInUser);
                    break;
                default:
                    cout << "Invalid choice. Press Enter to continue...";
                    cin.get();
                    displayLibrarianMenu(loggedInUser);
            }
            break;
        }
        case 2:
            // Loan Management Menu
            break;
        case 3:
            // Member Management Menu
            break;
        case 4:
            // Reports Menu
            break;
        case 5:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Press Enter to continue...";
            cin.get();
            displayLibrarianMenu(loggedInUser);
    }
}

void displayMemberMenu(const Member& loggedInUser) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "          MEMBER MENU                 " << endl;
    cout << "======================================" << endl;
    cout << "Welcome, " << loggedInUser.name << " (Member)" << endl;
    cout << "--------------------------------------" << endl;
    cout << "1. Browse Books" << endl;
    cout << "2. My Loans" << endl;
    cout << "3. My Reservations" << endl;
    cout << "4. My Profile" << endl;
    cout << "5. Logout" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            // Browse Books Menu
            break;
        case 2:
            // My Loans Menu
            break;
        case 3:
            // My Reservations Menu
            break;
        case 4:
            // My Profile Menu
            break;
        case 5:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Press Enter to continue...";
            cin.get();
            displayMemberMenu(loggedInUser);
    }
}

void displayBookDetailsView(const Book& book) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "          BOOK DETAILS                " << endl;
    cout << "======================================" << endl;
    cout << "ISBN: " << book.ISBN << endl;
    cout << "Title: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "Genre: " << book.genre << endl;
    cout << "Quantity: " << book.quantity << endl;
    cout << "Status: " << book.status << endl;
    cout << "--------------------------------------" << endl;
    cout << "Press Enter to continue...";
    cin.get();
} 