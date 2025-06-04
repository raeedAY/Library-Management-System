#ifndef LOAN_RESERVATION_H
#define LOAN_RESERVATION_H

#include "member.h"
#include "bookManagement.h"

#include <string>

using namespace std;

bool borrowBook(const Member& member, const string& ISBN);
bool returnBook(const Member& member, const string& ISBN);
vector<Book> viewBorrowedBooks(const Member& member);
bool reserveBook(const Member& member, const string& ISBN);
bool cancelReservation(const Member& member, const string& ISBN);
vector<Book> viewReservedBooks(const Member& member);

    // add ur definitions here

#endif 