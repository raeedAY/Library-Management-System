#include "../include/member.h"
#include "../include/adminSecurity.h"
#include "../include/bookManagement.h"
#include "../include/memberManagement.h"
#include "../include/loanReservation.h"
#include "../include/reportingAnalytics.h"
#include "../include/finePayment.h"
#include "../include/ui.h"

#include <iostream>
#include <limits>

using namespace std;

int main() {
    clearScreen();
    cout << "Welcome to HiLCoE's Library Management System" << endl;
    cout << "Please enter your username: ";
    string username;
    cin >> username;
    cout << "Please enter your password: ";
    string password;
    cin >> password;

    Member loggedInUser = checkLogin(username, password);

    if (!loggedInUser.username.empty()) {
        clearScreen();
        cout << "Logged in as " << loggedInUser.username << " (" << loggedInUser.membershipType << ")" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();

        if (loggedInUser.membershipType == "admin") {
            displayAdminMenu(loggedInUser);
        } else if (loggedInUser.membershipType == "librarian") {
            displayLibrarianMenu(loggedInUser);
        } else if (loggedInUser.membershipType == "member") {
            displayMemberMenu(loggedInUser);
        } else {
            cout << "Unknown membership type." << endl;
        }
    } else {
        clearScreen();
        cout << "Invalid username or password" << endl;
        cout << "Would you like to create an account? (y/n): ";
        char choice;
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            clearScreen();
            Member newMember;
            newMember.membershipType = "member";
            addMember(newMember);
            cout << "Please login with your new account credentials." << endl;
        }
    }
    
    return 0;
}