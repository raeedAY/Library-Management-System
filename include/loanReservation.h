#ifndef LOAN_RESERVATION_H
#define LOAN_RESERVATION_H

#include "member.h"
#include "bookManagement.h"

#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Loan {
    int memberId;
    string ISBN;
    time_t dueDate;
    bool isReturned;
};

bool borrowBook(const Member& member, const string& ISBN);
bool returnBook(const Member& member, const string& ISBN);
vector<Book> viewBorrowedBooks(const Member& member);
bool reserveBook(const Member& member, const string& ISBN);
bool cancelReservation(const Member& member, const string& ISBN);
vector<Book> viewReservedBooks(const Member& member);
vector<Loan> getOverdueLoans();
bool checkLoanStatus(const Member& member, const string& ISBN, time_t& outDueDate);

    

#endif 