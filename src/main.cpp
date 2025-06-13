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
#include <string>
#include <filesystem>

using namespace std;

int main() {
    // Create necessary directories if they don't exist
    filesystem::create_directory("data");
    
    clearScreen();
    cout << "======================================" << endl;
    cout << " HiLCoE Library Management System     " << endl;
    cout << "======================================" << endl;
    
    bool exitProgram = false;
    
    while (!exitProgram) {
        cout << "Please enter your username (or 'exit' to quit): ";
    string username;
    cin >> username;
        
        if (username == "exit") {
            exitProgram = true;
            break;
        }
        
    cout << "Please enter your password: ";
    string password;
    cin >> password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer

    Member loggedInUser = checkLogin(username, password);

    if (!loggedInUser.username.empty()) {
        clearScreen();
            cout << "======================================" << endl;
            cout << " Login Successful                    " << endl;
            cout << "======================================" << endl;
        cout << "Logged in as " << loggedInUser.username << " (" << loggedInUser.membershipType << ")" << endl;
        cout << "Press Enter to continue...";
        cin.get();

        if (loggedInUser.membershipType == "admin") {
            displayAdminMenu(loggedInUser);
        } else if (loggedInUser.membershipType == "librarian") {
            displayLibrarianMenu(loggedInUser);
        } else if (loggedInUser.membershipType == "member") {
            displayMemberMenu(loggedInUser);
        } else {
            cout << "Unknown membership type." << endl;
                cout << "Press Enter to continue...";
                cin.get();
        }
    } else {
        clearScreen();
            cout << "======================================" << endl;
            cout << " Login Failed                        " << endl;
            cout << "======================================" << endl;
        cout << "Invalid username or password" << endl;
            cout << "1. Try again" << endl;
            cout << "2. Create an account" << endl;
            cout << "3. Exit program" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Enter your choice: ";
            
            int choice;
            if (!(cin >> choice)) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                choice = 1; // Default to try again
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            switch (choice) {
                case 2: {
            clearScreen();
                    cout << "======================================" << endl;
                    cout << " Create New Account                  " << endl;
                    cout << "======================================" << endl;
            Member newMember;
                    newMember.membershipType = "member"; // Default to regular member
            addMember(newMember);
            cout << "Please login with your new account credentials." << endl;
                    cout << "Press Enter to continue...";
                    cin.get();
                    break;
                }
                case 3:
                    exitProgram = true;
                    break;
                default:
                    // Try again is the default
                    break;
        }
    }
    
        clearScreen();
    }
    
    cout << "Thank you for using HiLCoE's Library Management System!" << endl;
    return 0;
}