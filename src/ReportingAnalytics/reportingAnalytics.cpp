#include "../../include/reportingAnalytics.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/memberManagement.h"
#include "../../include/ui.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <iomanip>

using namespace std;
namespace fs = filesystem;

const string AUDIT_LOG_FILE = "data/audit_logs.txt";

Statistics StatisticsDashboard() {
    clearScreen();
    Statistics stats;
    vector<Member> members = listAllMembers();
    vector<Book> books = listAllBooks();

    stats.totalMembers = members.size();
    stats.totalBooks = 0;
    stats.availableBooks = 0;
    stats.adminCount = 0;
    stats.librarianCount = 0;
    stats.memberCount = 0;

    for (const auto& book : books) {
        stats.totalBooks += book.quantity;
        if (book.status == "available") {
            stats.availableBooks += book.quantity;
        }
    }

    for (const auto& member : members) {
        if (member.membershipType == "admin") {
            stats.adminCount++;
        } else if (member.membershipType == "librarian") {
            stats.librarianCount++;
        } else if (member.membershipType == "member") {
            stats.memberCount++;
        }
    }

    return stats;
}

void logBookAction(const string& action, const Book& book, const Member& user) {
    AuditLog log;
    log.timestamp = time(nullptr);
    log.action = action;
    log.bookISBN = book.ISBN;
    log.bookTitle = book.title;
    log.userId = user.Id;
    log.userName = user.name;
    
    saveAuditLog(log);
}

void saveAuditLog(const AuditLog& log) {
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ofstream logFile(AUDIT_LOG_FILE, ios::app);
    if (logFile.is_open()) {
        logFile << ctime(&log.timestamp) 
                << "Action: " << log.action << "\n"
                << "Book: " << log.bookTitle << " (ISBN: " << log.bookISBN << ")\n"
                << "User: " << log.userName << " (ID: " << log.userId << ")\n"
                << "----------------------------------------\n";
        logFile.close();
    }
}

vector<AuditLog> getBookAuditLogs() {
    vector<AuditLog> logs;
    string line;
    
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return logs;
        }
    }
    
    ifstream logFile(AUDIT_LOG_FILE);
    
    if (!logFile.is_open()) {
        ofstream createFile(AUDIT_LOG_FILE);
        createFile.close();
        cout << "No audit logs found.\n";
        return logs;
    }

    cout << "\nSystem Audit Logs:\n";
    cout << "----------------------------------------\n";
    while (getline(logFile, line)) {
        cout << line << endl;
    }
    logFile.close();
    
    return logs;
}

vector<Book> getMostPopularBooks(int limit) {
    clearScreen();
    vector<Book> books = listAllBooks(); // Load all books
    if (books.empty()) {
        cout << "No books in the system.\n";
        return {};
    }
    sort(books.begin(), books.end(),
         [](const Book& a, const Book& b) {
             return a.borrowCount > b.borrowCount;
         });
    cout << "\nBook Popularity Report:\n";
    int count = 0;
    for (const auto& b : books) {
        if (count++ >= limit) break;
        cout << " • " << b.title
             << " (ISBN: " << b.ISBN << ") — borrowed "
             << b.borrowCount << " times\n";
    }
    // Return the top 'limit' books
    if (books.size() > limit) {
        books.resize(limit);
    }
    return books;
}

vector<Member> getMostActiveMembers(int limit) {
    clearScreen();
    vector<Member> members = listAllMembers();
    if (members.empty()) {
        cout << "No members in the system.\n";
        return {};
    }

    // Count borrows for each member
    vector<int> borrowCounts(members.size(), 0);
    
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return {};
        }
    }
    
    ifstream logFile(AUDIT_LOG_FILE);
    if (!logFile.is_open()) {
        ofstream createFile(AUDIT_LOG_FILE);
        createFile.close();
        cout << "No audit logs found. Cannot determine active members.\n";
        return {};
    }
    
    string line;
    
    while (getline(logFile, line)) {
        if (line.find("Action: BORROW") != string::npos) {
            getline(logFile, line); // Skip book line
            getline(logFile, line); // Get user line
            int userId = stoi(line.substr(line.find("ID: ") + 4));
            
            // Increment borrow count for this member
            for (size_t i = 0; i < members.size(); i++) {
                if (members[i].Id == userId) {
                    borrowCounts[i]++;
                    break;
                }
            }
        }
    }
    logFile.close();

    // Sort members by borrow count
    for (size_t i = 0; i < members.size() - 1; i++) {
        for (size_t j = 0; j < members.size() - i - 1; j++) {
            if (borrowCounts[j] < borrowCounts[j + 1]) {
                swap(borrowCounts[j], borrowCounts[j + 1]);
                swap(members[j], members[j + 1]);
            }
        }
    }

    // Display results
    cout << "\nMember Activity Report - Frequent Borrowers:\n";
    for (int i = 0; i < min(limit, static_cast<int>(members.size())); i++) {
        cout << " • " << members[i].name
             << " (ID: " << members[i].Id << ") — borrowed "
             << borrowCounts[i] << " books\n";
    }

    // Return top members
    if (members.size() > limit) {
        members.resize(limit);
    }
    return members;
}

// Function to display overdue books report
void displayOverdueReport() {
    clearScreen();
    cout << "=======================================================================================================" << endl;
    cout << "                                  OVERDUE BOOKS REPORT                                                  " << endl;
    cout << "=======================================================================================================" << endl;
    
    // Get all overdue loans
    vector<Loan> overdueLoans = getOverdueLoans();
    
    if (overdueLoans.empty()) {
        cout << "No overdue books at this time." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    vector<Book> allBooks = listAllBooks();
    vector<Member> allMembers = listAllMembers();
    
    cout << left << setw(30) << "Book Title" << " | " 
         << setw(15) << "ISBN" << " | " 
         << setw(20) << "Member Name" << " | " 
         << setw(10) << "Member ID" << " | " 
         << "Due Date" << endl;
    cout << "=======================================================================================================" << endl;
    
    for (const auto& loan : overdueLoans) {
        string bookTitle = "";
        string memberName = "";
        
        // Find book info
        for (const auto& book : allBooks) {
            if (book.ISBN == loan.ISBN) {
                bookTitle = book.title;
                break;
            }
        }
        
        // Find member info
        for (const auto& member : allMembers) {
            if (member.Id == loan.memberId) {
                memberName = member.name;
                break;
            }
        }
        
        // Format date
        time_t dueDate = loan.dueDate;
        struct tm* timeinfo = localtime(&dueDate);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
        
        int daysOverdue = (time(nullptr) - loan.dueDate) / (24 * 60 * 60);
        
        cout << left << setw(30) << bookTitle << " | " 
             << setw(15) << loan.ISBN << " | " 
             << setw(20) << memberName << " | " 
             << setw(10) << loan.memberId << " | " 
             << buffer << " (" << daysOverdue << " days overdue)" << endl;
    }
    
    cout << "=======================================================================================================" << endl;
    cout << "Total overdue books: " << overdueLoans.size() << endl;
    cout << "Press Enter to continue...";
    cin.get();
}
