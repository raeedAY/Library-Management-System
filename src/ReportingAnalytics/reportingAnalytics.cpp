#include "../../include/reportingAnalytics.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/memberManagement.h"
#include "../../include/ui.h"
#include <algorithm>  // Add this for sort
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

const string AUDIT_LOG_FILE = "audit_logs.txt";

Statistics StatisticsDashboard() {
    clearScreen();
    Statistics stats = {0, 0, 0, 0, 0, 0};  // Initialize with default values
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
    ifstream logFile(AUDIT_LOG_FILE);
    
    if (!logFile.is_open()) {
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
    // put ur implementation here
}
