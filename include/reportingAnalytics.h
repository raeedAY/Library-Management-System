#ifndef REPORTING_ANALYTICS_H
#define REPORTING_ANALYTICS_H

#include "member.h"
#include "bookManagement.h"
#include "loanReservation.h"

#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Statistics {
    int totalMembers;
    int totalBooks;
    int availableBooks;
    int adminCount;
    int librarianCount;
    int memberCount;
};

struct AuditLog {
    time_t timestamp;
    string action;      // "ADD", "DELETE", "EDIT"
    string bookISBN;
    string bookTitle;
    int userId;
    string userName;
};

Statistics StatisticsDashboard();
vector<Book> getMostPopularBooks(int limit);
vector<Member> getMostActiveMembers(int limit);

// Audit logging functions
void logBookAction(const string& action, const Book& book, const Member& user);
vector<AuditLog> getBookAuditLogs();
void saveAuditLog(const AuditLog& log);
void displayOverdueReport();



#endif