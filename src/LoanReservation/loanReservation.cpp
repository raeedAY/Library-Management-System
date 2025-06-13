#include "../../include/loanReservation.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/reportingAnalytics.h"
#include "../../include/finePayment.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

struct ReservationEntry {
    string ISBN;
    int memberId;
};

vector<ReservationEntry> reservations;
vector<Loan> loans;

// Function to save loan records to file
void saveLoans() {
    filesystem::path dataDirPath = "data";
    if (!filesystem::exists(dataDirPath)) {
        try {
            filesystem::create_directory(dataDirPath);
        } catch (const filesystem::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ofstream file("data/loans.txt");
    if (file.is_open()) {
        for (const auto& loan : loans) {
            file << loan.memberId << "|" << loan.ISBN << "|" << loan.dueDate << "|" << (loan.isReturned ? "1" : "0") << endl;
        }
        file.close();
    }
}

// Function to load loan records from file
void loadLoans() {
    loans.clear();
    
    filesystem::path dataDirPath = "data";
    if (!filesystem::exists(dataDirPath)) {
        try {
            filesystem::create_directory(dataDirPath);
        } catch (const filesystem::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ifstream file("data/loans.txt");
    if (!file.is_open()) {
        ofstream createFile("data/loans.txt");
        createFile.close();
        return;
    }
    
    string line;
    while (getline(file, line)) {
        Loan loan;
        size_t pos = 0;
        string token;
        vector<string> tokens;
        
        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);
        
        if (tokens.size() >= 4) {
            loan.memberId = stoi(tokens[0]);
            loan.ISBN = tokens[1];
            loan.dueDate = stoll(tokens[2]);
            loan.isReturned = (tokens[3] == "1");
            loans.push_back(loan);
        }
    }
    file.close();
}

void saveReservations() {
    filesystem::path dataDirPath = "data";
    if (!filesystem::exists(dataDirPath)) {
        try {
            filesystem::create_directory(dataDirPath);
        } catch (const filesystem::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ofstream file("data/reservations.txt");
    if (file.is_open()) {
        for (const auto& res : reservations) {
            file << res.ISBN << "|" << res.memberId << endl;
        }
        file.close();
    }
}

void loadReservations() {
    reservations.clear();
    
    filesystem::path dataDirPath = "data";
    if (!filesystem::exists(dataDirPath)) {
        try {
            filesystem::create_directory(dataDirPath);
        } catch (const filesystem::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ifstream file("data/reservations.txt");
    if (!file.is_open()) {
        ofstream createFile("data/reservations.txt");
        createFile.close();
        return;
    }
    
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

// Convert time_t to string date format
string formatDate(time_t timestamp) {
    struct tm* timeinfo = localtime(&timestamp);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer);
}

bool borrowBook(const Member& member, const string& ISBN) {
    clearScreen();
    vector<Book> books = listAllBooks();
    bool bookFound = false;

    // Check if member has outstanding fines
    if (checkMemberHasFines(member)) {
        cout << "Cannot borrow book. Member has outstanding fines that must be paid first." << endl;
        return false;
    }
    
    // Check borrowing limit
    if (!checkBorrowingLimit(member.Id)) {
        cout << "Cannot borrow book. Member has reached the maximum borrowing limit." << endl;
        return false;
    }

    for (auto& book : books) {
        if (book.ISBN == ISBN) {
            bookFound = true;
            if (book.quantity > 0 && book.status == "available") {
                book.quantity--;
                if (book.quantity == 0) {
                    book.status = "borrowed";
                }
                
                // Set due date (14 days from today)
                time_t now = time(nullptr);
                time_t dueDate = now + (14 * 24 * 60 * 60); // 14 days in seconds
                
                // Add loan record
                loadLoans();
                Loan newLoan;
                newLoan.memberId = member.Id;
                newLoan.ISBN = ISBN;
                newLoan.dueDate = dueDate;
                newLoan.isReturned = false;
                loans.push_back(newLoan);
                saveLoans();
                
                saveBooks(books);
                logBookAction("BORROW", book, member);
                
                cout << "Book borrowed successfully!" << endl;
                cout << "Due date: " << formatDate(dueDate) << endl;
                return true;
            } else {
                cout << "Book is not available for borrowing." << endl;
                return false;
            }
        }
    }

    if (!bookFound) {
        cout << "Book with ISBN " << ISBN << " not found." << endl;
    }
    return false;
}

bool returnBook(const Member& member, const string& ISBN) {
    clearScreen();
    
    vector<Book> books = listAllBooks();
    bool bookFound = false;
    
    for (auto& book : books) {
        if (book.ISBN == ISBN) {
            bookFound = true;
            
            // Update book quantity
            book.quantity++;
            if (book.status == "borrowed" && book.quantity > 0) {
                book.status = "available";
            }
            saveBooks(books);
            
            // Update loan record
            loadLoans();
            bool loanFound = false;
            time_t returnDate = time(nullptr);
            
            for (auto& loan : loans) {
                if (loan.memberId == member.Id && loan.ISBN == ISBN && !loan.isReturned) {
                    loan.isReturned = true;
                    loanFound = true;
                    
                    // Check if return is late and add fine if needed
                    if (returnDate > loan.dueDate) {
                        // Calculate days overdue
                        int daysOverdue = (returnDate - loan.dueDate) / (24 * 60 * 60);
                        double fineAmount = daysOverdue * 0.50; // $0.50 per day
                        
                        string reason = "Overdue book return by " + to_string(daysOverdue) + " days";
                        addFine(member, ISBN, fineAmount, reason);
                        
                        cout << "Book is overdue by " << daysOverdue << " days." << endl;
                        cout << "Fine of $" << fixed << setprecision(2) << fineAmount << " has been added to your account." << endl;
                    }
                    
                    break;
                }
            }
            
            if (!loanFound) {
                cout << "No loan record found for this book." << endl;
            }
            
            saveLoans();
            
            // Check for reservations
            loadReservations();
            for (const auto& res : reservations) {
                if (res.ISBN == ISBN) {
                    cout << "Notification: Book " << ISBN << " is now available for member " << res.memberId << endl;
                    break;
                }
            }
            
            logBookAction("RETURN", book, member);
            cout << "Book returned successfully!" << endl;
            return true;
        }
    }
    
    if (!bookFound) {
        cout << "Book with ISBN " << ISBN << " not found." << endl;
    }
    return false;
}

bool checkLoanStatus(const Member& member, const string& ISBN, time_t& outDueDate) {
    loadLoans();
    
    for (const auto& loan : loans) {
        if (loan.memberId == member.Id && loan.ISBN == ISBN && !loan.isReturned) {
            outDueDate = loan.dueDate;
            return true;
        }
    }
    
    return false;
}

vector<Book> viewBorrowedBooks(const Member& member) {
    clearScreen();
    vector<Book> borrowedBooks;
    
    loadLoans();
    vector<Book> allBooks = listAllBooks();
    
    cout << "=======================================================================================" << endl;
    cout << "                            YOUR BORROWED BOOKS                                         " << endl;
    cout << "=======================================================================================" << endl;
    cout << left << setw(30) << "Title" << " | " 
         << setw(20) << "Author" << " | " 
         << setw(15) << "ISBN" << " | " 
         << "Due Date" << endl;
    cout << "=======================================================================================" << endl;
    
    time_t now = time(nullptr);
    bool hasBorrowed = false;

    for (const auto& loan : loans) {
        if (loan.memberId == member.Id && !loan.isReturned) {
            for (const auto& book : allBooks) {
                if (book.ISBN == loan.ISBN) {
                    borrowedBooks.push_back(book);
                    
                    // Display book with due date
                    cout << left << setw(30) << book.title << " | " 
                         << setw(20) << book.author << " | " 
                         << setw(15) << book.ISBN << " | ";
                         
                    if (now > loan.dueDate) {
                        cout << formatDate(loan.dueDate) << " (OVERDUE)" << endl;
                    } else {
                        cout << formatDate(loan.dueDate) << endl;
                    }
                    
                    hasBorrowed = true;
                    break;
                }
            }
        }
    }

    cout << "=======================================================================================" << endl;
    
    if (!hasBorrowed) {
        cout << "You have no borrowed books." << endl;
    }
    
    cout << "Press Enter to continue...";
    cin.get();

    return borrowedBooks;
}

// Function to get all overdue loans
vector<Loan> getOverdueLoans() {
    loadLoans();
    vector<Loan> overdueLoans;
    
    time_t now = time(nullptr);
    
    for (const auto& loan : loans) {
        if (!loan.isReturned && now > loan.dueDate) {
            overdueLoans.push_back(loan);
        }
    }
    
    return overdueLoans;
}

bool reserveBook(const Member& member, const string& ISBN) {
    clearScreen();
    
    loadReservations();
    
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
    
    for (const auto& res : reservations) {
        if (res.ISBN == ISBN && res.memberId == member.Id) {
            cout << "You already have a reservation for this book." << endl;
            return false;
        }
    }
    
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

    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i].ISBN == ISBN && reservations[i].memberId == member.Id) {
            reservations.erase(reservations.begin() + i);
            found = true;
            break;
        }
    }

    if (found) {
        saveReservations();
        cout << "Reservation cancelled successfully!" << endl;
        return true;
    } else {
        cout << "No reservation found for this book." << endl;
        return false;
    }
}

vector<Book> viewReservedBooks(const Member& member) {
    clearScreen();
    
    loadReservations();
    vector<Book> reservedBooks;
    vector<Book> allBooks = listAllBooks();
    
    cout << "=======================================================================================" << endl;
    cout << "                            YOUR RESERVED BOOKS                                         " << endl;
    cout << "=======================================================================================" << endl;
    cout << left << setw(30) << "Title" << " | " 
         << setw(20) << "Author" << " | " 
         << setw(15) << "ISBN" << " | " 
         << "Status" << endl;
    cout << "=======================================================================================" << endl;
    
    bool hasReserved = false;
    
    for (const auto& res : reservations) {
        if (res.memberId == member.Id) {
            for (const auto& book : allBooks) {
                if (book.ISBN == res.ISBN) {
                    reservedBooks.push_back(book);
                    
                    cout << left << setw(30) << book.title << " | " 
                         << setw(20) << book.author << " | " 
                         << setw(15) << book.ISBN << " | " 
                         << "Reserved" << endl;
                         
                    hasReserved = true;
                    break;
                }
            }
        }
    }
    
    cout << "=======================================================================================" << endl;
    
    if (!hasReserved) {
        cout << "You have no reserved books." << endl;
    }
    
    cout << "Press Enter to continue...";
    cin.get();
    
    return reservedBooks;
}
