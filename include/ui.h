#ifndef UI_H
#define UI_H

#include "member.h"

#include <string>

using namespace std;

void clearScreen();
void displayAdminMenu(const Member& loggedInUser);
void displayLibrarianMenu(const Member& loggedInUser);
void displayMemberMenu(const Member& loggedInUser);
void displayBorrowMenu(const Member& loggedInUser);
void displayReturnMenu(const Member& loggedInUser);
void displayBookDetailsView(const Book& book);
void displayMemberDetailsView(const Member& member);

    // add ur definitions here

#endif 