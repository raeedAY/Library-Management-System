#include "../../include/ui.h"
#include "../../include/member.h"
#include "../../include/adminSecurity.h"
#include "../../include/bookManagement.h"
#include "../../include/memberManagement.h"
#include "../../include/loanReservation.h"
#include "../../include/reportingAnalytics.h"
#include "../../include/finePayment.h"

#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <ctime>
#include <filesystem>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
}

void displayAdminMenu(const Member& loggedInUser) {
    while (true) {
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
                bool back = false;
                while (!back) {
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
                            cout << "Enter ISBN: ";
                            cin >> newBook.ISBN;
                            cout << "Enter title: ";
                            cin.ignore();
                            getline(cin, newBook.title);
                            cout << "Enter author: ";
                            getline(cin, newBook.author);
                            cout << "Enter genre: ";
                            getline(cin, newBook.genre);
                            cout << "Enter quantity: ";
                            cin >> newBook.quantity;
                    addBook(newBook);
                    break;
                        }
                        case 2: {
                            cout << "Enter ISBN of the book to edit: ";
                            string isbn;
                            cin >> isbn;
                            editBook(isbn);
                            break;
                        }
                        case 3: {
                            cout << "Enter ISBN of the book to remove: ";
                            string isbn;
                            cin >> isbn;
                            removeBook(isbn);
                            break;
                        }
                        case 4: {
                            cout << "Enter title or author to search: ";
                            string searchTerm;
                            cin.ignore();
                            getline(cin, searchTerm);
                            
                            vector<Book> allBooks = listAllBooks();
                            vector<Book> matchingBooks;
                            
                            for (const auto& book : allBooks) {
                                if (book.title.find(searchTerm) != string::npos || 
                                    book.author.find(searchTerm) != string::npos) {
                                    matchingBooks.push_back(book);
                                }
                            }
                            
                            if (matchingBooks.empty()) {
                                cout << "No matching books found." << endl;
                                cout << "Press Enter to continue...";
                                cin.get();
                            } else {
                                cout << "Found " << matchingBooks.size() << " matching books:" << endl;
                                for (const auto& book : matchingBooks) {
                                    displayBookDetailsView(book);
                                }
                            }
                            break;
                        }
                        case 5: {
                            vector<Book> books = listAllBooks();
                            displayBookTable(books);
                            break;
                        }
                        case 6:
                            back = true;
                            break;
                        default:
                            cout << "Invalid choice. Press Enter to continue...";
                            cin.get();
                    }
                }
                break;
            }
            case 2: {
                bool back = false;
                while (!back) {
                    clearScreen();
                    cout << "======================================" << endl;
                    cout << "     MEMBER MANAGEMENT                " << endl;
                    cout << "======================================" << endl;
                    cout << "1. Add New Member" << endl;
                    cout << "2. Edit Member" << endl;
                    cout << "3. Delete Member" << endl;
                    cout << "4. Search Member" << endl;
                    cout << "5. List All Members" << endl;
                    cout << "6. Back to Main Menu" << endl;
                    cout << "--------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    
                    int memberChoice;
                    cin >> memberChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch (memberChoice) {
                        case 1: {
                            Member newMember;
                            addMember(newMember);
                            break;
                        }
                        case 2: {
                            cout << "Enter member ID to edit: ";
                            int memberId;
                            cin >> memberId;
                            editMember(memberId);
                    break;
                        }
                        case 3: {
                            cout << "Enter member ID to delete: ";
                            int memberId;
                            cin >> memberId;
                            deleteMember(memberId);
                    break;
                        }
                        case 4: {
                            cout << "Enter member ID to search: ";
                            int memberId;
                            cin >> memberId;
                            Member member = searchMember(memberId);
                            if (!member.username.empty()) {
                                displayMemberDetailsView(member);
                            } else {
                                cout << "Member not found. Press Enter to continue...";
                                cin.get();
                            }
                    break;
                        }
                        case 5: {
                            vector<Member> members = listAllMembers();
                            displayMemberTable(members);
                    break;
                        }
                case 6:
                            back = true;
                    break;
                default:
                    cout << "Invalid choice. Press Enter to continue...";
                    cin.get();
                    }
                }
                break;
            }
            case 3: {
                bool back = false;
                while (!back) {
                    clearScreen();
                    cout << "======================================" << endl;
                    cout << "     LIBRARIAN MANAGEMENT             " << endl;
                    cout << "======================================" << endl;
                    cout << "1. Add New Librarian" << endl;
                    cout << "2. Edit Librarian" << endl;
                    cout << "3. Remove Librarian" << endl;
                    cout << "4. List All Librarians" << endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "--------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    
                    int librarianChoice;
                    cin >> librarianChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch (librarianChoice) {
                        case 1: {
                            Member newLibrarian;
                            newLibrarian.membershipType = "librarian";
                            addMember(newLibrarian);
                            break;
                        }
                        case 2: {
                            vector<Member> members = listAllMembers();
                            vector<Member> librarians;
                            
                            cout << "Librarians:" << endl;
                            cout << "--------------------------------------" << endl;
                            int count = 0;
                            for (const auto& member : members) {
                                if (member.membershipType == "librarian") {
                                    count++;
                                    cout << count << ". " << member.name << " (ID: " << member.Id << ")" << endl;
                                    librarians.push_back(member);
                                }
                            }
                            
                            if (librarians.empty()) {
                                cout << "No librarians found." << endl;
                                cout << "Press Enter to continue...";
                                cin.get();
                                break;
                            }
                            
                            cout << "Enter librarian number to edit: ";
                            int librarianNum;
                            cin >> librarianNum;
                            
                            if (librarianNum < 1 || librarianNum > librarians.size()) {
                                cout << "Invalid selection." << endl;
                                cout << "Press Enter to continue...";
                                cin.get();
                                break;
                            }
                            
                            editMember(librarians[librarianNum - 1].Id);
                            break;
                        }
                        case 3: {
                            vector<Member> members = listAllMembers();
                            vector<Member> librarians;
                            
                            cout << "Librarians:" << endl;
                            cout << "--------------------------------------" << endl;
                            int count = 0;
                            for (const auto& member : members) {
                                if (member.membershipType == "librarian") {
                                    count++;
                                    cout << count << ". " << member.name << " (ID: " << member.Id << ")" << endl;
                                    librarians.push_back(member);
                                }
                            }
                            
                            if (librarians.empty()) {
                                cout << "No librarians found." << endl;
                                cout << "Press Enter to continue...";
                                cin.get();
                                break;
                            }
                            
                            cout << "Enter librarian number to remove: ";
                            int librarianNum;
                            cin >> librarianNum;
                            
                            if (librarianNum < 1 || librarianNum > librarians.size()) {
                                cout << "Invalid selection." << endl;
                                cout << "Press Enter to continue...";
                                cin.get();
                                break;
                            }
                            
                            deleteMember(librarians[librarianNum - 1].Id);
                            break;
                        }
                        case 4: {
                            vector<Member> members = listAllMembers();
                            vector<Member> librarians;
                            
                            for (const auto& member : members) {
                                if (member.membershipType == "librarian") {
                                    librarians.push_back(member);
                                }
                            }
                            
                            displayMemberTable(librarians);
                            break;
                        }
                        case 5:
                            back = true;
                            break;
                        default:
                            cout << "Invalid choice. Press Enter to continue...";
                            cin.get();
                    }
                }
                break;
            }
            case 4: {
                bool back = false;
                while (!back) {
                    clearScreen();
                    cout << "======================================" << endl;
                    cout << "          REPORTS MENU                " << endl;
                    cout << "======================================" << endl;
                    cout << "1. Statistics Dashboard" << endl;
                    cout << "2. Most Popular Books" << endl;
                    cout << "3. Overdue Books Report" << endl;
                    cout << "4. View Audit Logs" << endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "--------------------------------------" << endl;
                    cout << "Enter your choice: ";

                    int reportChoice;
                    cin >> reportChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (reportChoice) {
                        case 1: {
                            Statistics stats = StatisticsDashboard();
                            cout << "Total Members: " << stats.totalMembers << endl;
                            cout << "Total Books: " << stats.totalBooks << endl;
                            cout << "Available Books: " << stats.availableBooks << endl;
                            cout << "Admins: " << stats.adminCount << endl;
                            cout << "Librarians: " << stats.librarianCount << endl;
                            cout << "Members: " << stats.memberCount << endl;
                            cout << "Press Enter to continue...";
                            cin.get();
                            break;
                        }
                        case 2:
                            getMostPopularBooks(5);
                            cout << "Press Enter to continue...";
                            cin.get();
                            break;
                        case 3:
                            displayOverdueReport();
                            break;
                        case 4:
                            getBookAuditLogs();
                            cout << "Press Enter to continue...";
                            cin.get();
                            break;
                        case 5:
                            back = true;
                            break;
                        default:
                            cout << "Invalid choice. Press Enter to continue...";
                            cin.get();
                    }
                }
                break;
            }
        case 5: {
            bool back = false;
            while (!back) {
                clearScreen();
                cout << "======================================" << endl;
                cout << "        SYSTEM SETTINGS               " << endl;
                cout << "======================================" << endl;
                cout << "1. Backup Data" << endl;
                cout << "2. Restore Data" << endl;
                cout << "3. System Information" << endl;
                cout << "4. Back to Main Menu" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Enter your choice: ";
                
                int settingsChoice;
                if (!(cin >> settingsChoice)) {
                    cin.clear(); // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                    cout << "Invalid input. Please enter a number." << endl;
                    cout << "Press Enter to continue...";
                    cin.get();
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                switch (settingsChoice) {
                    case 1: {
                        clearScreen();
                        cout << "======================================" << endl;
                        cout << "        BACKUP DATABASE              " << endl;
                        cout << "======================================" << endl;
                        cout << "This will create a backup of all library data." << endl;
                        cout << "Continue with backup? (y/n): ";
                        
                        char confirm;
                        cin >> confirm;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        if (confirm == 'y' || confirm == 'Y') {
                            clearScreen();
                            cout << "Creating backup..." << endl;
                            cout << "--------------------------------------" << endl;
                            
                        if (backupDatabase()) {
                                cout << "\nBackup completed successfully!" << endl;
                        } else {
                                cout << "\nBackup failed. Please check error messages." << endl;
                            }
                        } else {
                            cout << "Backup operation cancelled." << endl;
                        }
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2: {
                        clearScreen();
                        cout << "======================================" << endl;
                        cout << "        RESTORE DATABASE             " << endl;
                        cout << "======================================" << endl;
                        cout << "WARNING: Restoring will overwrite current data." << endl;
                        cout << "It is recommended to backup current data first." << endl;
                        cout << "Continue with restore? (y/n): ";
                        
                        char confirm;
                        cin >> confirm;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        if (confirm == 'y' || confirm == 'Y') {
                            clearScreen();
                            cout << "======================================" << endl;
                            cout << "        RESTORE DATABASE             " << endl;
                            cout << "======================================" << endl;
                            
                            if (restoreDatabase()) {
                                cout << "\nRestore completed successfully!" << endl;
                            } else {
                                cout << "\nRestore failed. Please check error messages." << endl;
                            }
                        } else {
                            cout << "Restore operation cancelled." << endl;
                        }
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 3: {
                        clearScreen();
                        cout << "======================================" << endl;
                        cout << "        SYSTEM INFORMATION            " << endl;
                        cout << "======================================" << endl;
                        cout << "Library Management System v1.0" << endl;
                        cout << "Developed for HiLCoE" << endl;
                        cout << "--------------------------------------" << endl;
                        
                        // Show backup info
                        cout << "Backup Information:" << endl;
                        
                        // Check if backups directory exists
                        filesystem::path backupsDir("backups");
                        if (filesystem::exists(backupsDir) && filesystem::is_directory(backupsDir)) {
                            int count = 0;
                            time_t latestTime = 0;
                            string latestBackup = "";
                            
                            for (const auto& entry : filesystem::directory_iterator(backupsDir)) {
                                if (filesystem::is_directory(entry)) {
                                    string name = entry.path().filename().string();
                                    if (name.find("backup_") != string::npos) {
                                        count++;
                                        time_t backupTime = filesystem::last_write_time(entry).time_since_epoch().count();
                                        if (backupTime > latestTime) {
                                            latestTime = backupTime;
                                            latestBackup = name;
                                        }
                                    }
                                }
                            }
                            
                            cout << "Total backups: " << count << endl;
                            if (count > 0) {
                                cout << "Latest backup: " << latestBackup << endl;
                            }
                        } else {
                            cout << "No backups found." << endl;
                        }
                        
                        cout << "--------------------------------------" << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 4:
                        back = true;
                        break;
                    default:
                        cout << "Invalid choice. Press Enter to continue...";
                        cin.get();
                }
            }
            break;
        }
        case 6:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Press Enter to continue...";
            cin.get();
        }
    }
}

void displayLibrarianMenu(const Member& loggedInUser) {
    while (true) {
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
                bool back = false;
                while (!back) {
            clearScreen();
            cout << "======================================" << endl;
            cout << "       BOOK MANAGEMENT                " << endl;
            cout << "======================================" << endl;
            cout << "1. Add New Book" << endl;
            cout << "2. Edit Book" << endl;
            cout << "3. Search Books" << endl;
                    cout << "4. Delete Book" << endl;
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
                case 2: {
                    cout << "Enter ISBN of the book to edit: ";
                    string isbn;
                    cin >> isbn;
                    editBook(isbn);
                    break;
                }
                case 3: {
                    cout << "Enter title or author to search: ";
                    string searchTerm;
                    cin.ignore();
                    getline(cin, searchTerm);
                    
                    vector<Book> allBooks = listAllBooks();
                    vector<Book> matchingBooks;
                    
                    for (const auto& book : allBooks) {
                        if (book.title.find(searchTerm) != string::npos || 
                            book.author.find(searchTerm) != string::npos) {
                            matchingBooks.push_back(book);
                        }
                    }
                    
                    if (matchingBooks.empty()) {
                        cout << "No matching books found." << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                    } else {
                        cout << "Found " << matchingBooks.size() << " matching books:" << endl;
                        for (const auto& book : matchingBooks) {
                            displayBookDetailsView(book);
                        }
                    }
                    break;
                }
                case 4: {
                    cout << "Enter ISBN of the book to remove: ";
                    string isbn;
                    cin >> isbn;
                    removeBook(isbn);
                    break;
                }
                case 5: {
                    vector<Book> books = listAllBooks();
                    displayBookTable(books);
                    break;
                }
                        case 6:
                            back = true;
                    break;
                default:
                    cout << "Invalid choice. Press Enter to continue...";
                    cin.get();
                    }
                }
                break;
            }
            case 2: {
                bool back = false;
                while (!back) {
                    clearScreen();
                    cout << "======================================" << endl;
                    cout << "       LOAN MANAGEMENT                " << endl;
                    cout << "======================================" << endl;
                    cout << "1. Borrow Book for Member" << endl;
                    cout << "2. Return Book for Member" << endl;
                    cout << "3. View All Loans" << endl;
                    cout << "4. View Overdue Loans" << endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "--------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    
                    int loanChoice;
                    if (!(cin >> loanChoice)) {
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                        cout << "Invalid input. Please enter a number." << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                        continue;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch (loanChoice) {
                        case 1: {
                            // Allow librarian to select a member first
                            clearScreen();
                            cout << "======================================" << endl;
                            cout << "        SELECT MEMBER                 " << endl;
                            cout << "======================================" << endl;
                            
                            cout << "Enter member ID: ";
                            int memberId;
                            if (!(cin >> memberId)) {
                                cin.clear(); // Clear error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                                cout << "Invalid input. Please enter a valid member ID." << endl;
                                cout << "Press Enter to continue...";
                                cin.get();
                                break;
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            Member member = searchMember(memberId);
                            if (!member.username.empty()) {
                                displayBorrowMenu(member);
                            } else {
                                cout << "Member not found. Press Enter to continue...";
                                cin.get();
                            }
                            break;
                        }
                        case 2: {
                            // Allow librarian to select a member first
                            clearScreen();
                            cout << "======================================" << endl;
                            cout << "        SELECT MEMBER                 " << endl;
                            cout << "======================================" << endl;
                            
                            cout << "Enter member ID: ";
                            int memberId;
                            if (!(cin >> memberId)) {
                                cin.clear(); // Clear error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                                cout << "Invalid input. Please enter a valid member ID." << endl;
                                cout << "Press Enter to continue...";
                                cin.get();
                                break;
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            Member member = searchMember(memberId);
                            if (!member.username.empty()) {
                                displayReturnMenu(member);
                            } else {
                                cout << "Member not found. Press Enter to continue...";
                                cin.get();
                            }
                            break;
                        }
                        case 3: {
                            // View all loans
                            clearScreen();
                            cout << "======================================" << endl;
                            cout << "        ALL LOANS                     " << endl;
                            cout << "======================================" << endl;
                            
                            vector<Loan> allLoans = getAllLoans();
                            
                            if (allLoans.empty()) {
                                cout << "No loans found in the system." << endl;
                            } else {
                                cout << left << setw(10) << "Loan ID" << " | "
                                     << setw(15) << "Member ID" << " | "
                                     << setw(15) << "Book ISBN" << " | "
                                     << setw(20) << "Borrow Date" << " | "
                                     << setw(20) << "Due Date" << " | "
                                     << "Status" << endl;
                                cout << "------------------------------------------------------------------------------------" << endl;
                                
                                for (const auto& loan : allLoans) {
                                    Member member = searchMember(loan.memberId);
                                    Book book = getBookByISBN(loan.ISBN);
                                    
                                    string status = loan.isOverdue ? "Overdue" : "On time";
                                    
                                    cout << left << setw(10) << loan.loanId << " | "
                                         << setw(15) << loan.memberId << " | "
                                         << setw(15) << loan.ISBN << " | "
                                         << setw(20) << loan.borrowDate << " | "
                                         << setw(20) << loan.dueDate << " | "
                                         << status << endl;
                                }
                            }
                            
                            cout << "Press Enter to continue...";
                            cin.get();
                            break;
                        }
                        case 4: {
                            // View overdue loans
                            clearScreen();
                            cout << "======================================" << endl;
                            cout << "        OVERDUE LOANS                 " << endl;
                            cout << "======================================" << endl;
                            
                            vector<Loan> allLoans = getAllLoans();
                            vector<Loan> overdueLoans;
                            
                            for (const auto& loan : allLoans) {
                                if (loan.isOverdue) {
                                    overdueLoans.push_back(loan);
                                }
                            }
                            
                            if (overdueLoans.empty()) {
                                cout << "No overdue loans found in the system." << endl;
                            } else {
                                cout << left << setw(10) << "Loan ID" << " | "
                                     << setw(15) << "Member ID" << " | "
                                     << setw(15) << "Book ISBN" << " | "
                                     << setw(20) << "Borrow Date" << " | "
                                     << setw(20) << "Due Date" << endl;
                                cout << "----------------------------------------------------------------------------------" << endl;
                                
                                for (const auto& loan : overdueLoans) {
                                    Member member = searchMember(loan.memberId);
                                    Book book = getBookByISBN(loan.ISBN);
                                    
                                    cout << left << setw(10) << loan.loanId << " | "
                                         << setw(15) << loan.memberId << " | "
                                         << setw(15) << loan.ISBN << " | "
                                         << setw(20) << loan.borrowDate << " | "
                                         << setw(20) << loan.dueDate << endl;
                                }
                            }
                            
                            cout << "Press Enter to continue...";
                            cin.get();
                            break;
                        }
                        case 5:
                            back = true;
                            break;
                        default:
                            cout << "Invalid choice. Press Enter to continue...";
                            cin.get();
                    }
                }
                break;
            }
        case 3: {
            bool back = false;
            while (!back) {
                clearScreen();
                cout << "======================================" << endl;
                cout << "     MEMBER MANAGEMENT                " << endl;
                cout << "======================================" << endl;
                cout << "1. Add New Member" << endl;
                cout << "2. Edit Member" << endl;
                cout << "3. Search Member" << endl;
                cout << "4. List All Members" << endl;
                cout << "5. Back to Main Menu" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Enter your choice: ";
                
                int memberChoice;
                cin >> memberChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                switch (memberChoice) {
                    case 1: {
                        Member newMember;
                        addMember(newMember);
                        break;
                    }
                    case 2: {
                        cout << "Enter member ID to edit: ";
                        int memberId;
                        cin >> memberId;
                        editMember(memberId);
                        break;
                    }
                    case 3: {
                        cout << "Enter member ID to search: ";
                        int memberId;
                        cin >> memberId;
                        Member member = searchMember(memberId);
                        if (!member.username.empty()) {
                            displayMemberDetailsView(member);
                        } else {
                            cout << "Member not found. Press Enter to continue...";
                            cin.get();
                        }
                        break;
                    }
                    case 4: {
                        vector<Member> members = listAllMembers();
                        displayMemberTable(members);
                        break;
                    }
                    case 5:
                        back = true;
                        break;
                    default:
                        cout << "Invalid choice. Press Enter to continue...";
                        cin.get();
                }
            }
            break;
        }
        case 4: {
            bool back = false;
            while (!back) {
                clearScreen();
                cout << "======================================" << endl;
                cout << "          REPORTS MENU                " << endl;
                cout << "======================================" << endl;
                cout << "1. Statistics Dashboard" << endl;
                cout << "2. Most Popular Books" << endl;
                cout << "3. Overdue Books Report" << endl;
                cout << "4. View Audit Logs" << endl;
                cout << "5. Back to Main Menu" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Enter your choice: ";

                int reportChoice;
                cin >> reportChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (reportChoice) {
                    case 1: {
                        Statistics stats = StatisticsDashboard();
                        cout << "Total Members: " << stats.totalMembers << endl;
                        cout << "Total Books: " << stats.totalBooks << endl;
                        cout << "Available Books: " << stats.availableBooks << endl;
                        cout << "Admins: " << stats.adminCount << endl;
                        cout << "Librarians: " << stats.librarianCount << endl;
                        cout << "Members: " << stats.memberCount << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2:
                        getMostPopularBooks(5);
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    case 3:
                        displayOverdueReport();
                        break;
                    case 4:
                        getBookAuditLogs();
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    case 5:
                        back = true;
                        break;
                    default:
                        cout << "Invalid choice. Press Enter to continue...";
                        cin.get();
                }
            }
            break;
        }
        case 5:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Press Enter to continue...";
            cin.get();
        }
    }
}

void displayMemberMenu(const Member& loggedInUser) {
    while (true) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "          MEMBER MENU                 " << endl;
    cout << "======================================" << endl;
    cout << "Welcome, " << loggedInUser.name << " (Member)" << endl;
    cout << "--------------------------------------" << endl;
    cout << "1. Browse Books" << endl;
    cout << "2. Borrow Book" << endl;
    cout << "3. Return Book" << endl;
    cout << "4. My Loans" << endl;
    cout << "5. My Reservations" << endl;
    cout << "6. Reserve a Book" << endl;
    cout << "7. Cancel Reservation" << endl;
    cout << "8. My Fines" << endl;
    cout << "9. Pay Fine" << endl;
    cout << "10. My Profile" << endl;
    cout << "11. Logout" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
        cout << "Invalid input. Please enter a number." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        continue;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
            case 1: {
                vector<Book> books = listAllBooks();
                displayBookTable(books);
            break;
            }
        case 2:
            displayBorrowMenu(loggedInUser);
            break;
        case 3:
            displayReturnMenu(loggedInUser);
            break;
        case 4:
            viewBorrowedBooks(loggedInUser);
            cout << "Press Enter to continue...";
            cin.get();
            break;
        case 5:
                viewReservedBooks(loggedInUser);
            cout << "Press Enter to continue...";
            cin.get();
            break;
        case 6: {
            // Improved interface for reserving books
            clearScreen();
            cout << "======================================" << endl;
            cout << "          RESERVE BOOK                " << endl;
            cout << "======================================" << endl;
            
            vector<Book> books = listAllBooks();
            vector<Book> availableForReserve;
            
            // Filter books that can be reserved
            for (const auto& book : books) {
                if (book.status != "Not Available") {
                    availableForReserve.push_back(book);
                }
            }
            
            if (availableForReserve.empty()) {
                cout << "No books available for reservation." << endl;
                cout << "Press Enter to continue...";
                cin.get();
            break;
            }
            
            cout << "Available Books for Reservation:" << endl;
            cout << "--------------------------------------" << endl;
            cout << left << setw(5) << "No." << " | " 
                 << setw(15) << "ISBN" << " | " 
                 << setw(30) << "Title" << " | " 
                 << setw(20) << "Author" << endl;
            cout << "--------------------------------------" << endl;
            
            int count = 1;
            for (const auto& book : availableForReserve) {
                cout << left << setw(5) << count << " | " 
                     << setw(15) << book.ISBN << " | " 
                     << setw(30) << book.title << " | " 
                     << setw(20) << book.author << endl;
                count++;
            }
            
            cout << "--------------------------------------" << endl;
            cout << "Enter book number to reserve (0 to cancel): ";
            int bookNum;
            
            if (!(cin >> bookNum)) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                cout << "Invalid input. Operation cancelled." << endl;
                cout << "Press Enter to continue...";
                cin.get();
            break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (bookNum == 0) {
                cout << "Operation cancelled." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            if (bookNum < 1 || bookNum > availableForReserve.size()) {
                cout << "Invalid book number." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            Book selectedBook = availableForReserve[bookNum - 1];
            reserveBook(loggedInUser, selectedBook.ISBN);
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        case 7: {
            // Improved interface for canceling reservations
            clearScreen();
            cout << "======================================" << endl;
            cout << "       CANCEL RESERVATION             " << endl;
            cout << "======================================" << endl;
            
            vector<Reservation> reservations = getUserReservations(loggedInUser);
            
            if (reservations.empty()) {
                cout << "You have no active reservations to cancel." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            cout << "Your Reservations:" << endl;
            cout << "--------------------------------------" << endl;
            cout << left << setw(5) << "No." << " | " 
                 << setw(15) << "ISBN" << " | " 
                 << setw(30) << "Title" << " | " 
                 << setw(20) << "Reserved Date" << endl;
            cout << "--------------------------------------" << endl;
            
            int count = 1;
            for (const auto& reservation : reservations) {
                // Get book details
                Book book = getBookByISBN(reservation.ISBN);
                
                cout << left << setw(5) << count << " | " 
                     << setw(15) << reservation.ISBN << " | " 
                     << setw(30) << book.title << " | " 
                     << setw(20) << reservation.reservationDate << endl;
                count++;
            }
            
            cout << "--------------------------------------" << endl;
            cout << "Enter reservation number to cancel (0 to cancel operation): ";
            int reserveNum;
            
            if (!(cin >> reserveNum)) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                cout << "Invalid input. Operation cancelled." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (reserveNum == 0) {
                cout << "Operation cancelled." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            if (reserveNum < 1 || reserveNum > reservations.size()) {
                cout << "Invalid reservation number." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            Reservation selectedReservation = reservations[reserveNum - 1];
            cancelReservation(loggedInUser, selectedReservation.ISBN);
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        case 8: {
                vector<Fine> fines = getMemberFines(loggedInUser);
                double totalAmount = getTotalFineAmount(loggedInUser);
                cout << "Total fine amount: $" << fixed << setprecision(2) << totalAmount << endl;
                cout << "Press Enter to continue...";
                cin.get();
            break;
            }
                case 9: {
            clearScreen();
            cout << "======================================" << endl;
            cout << "          PAY FINE                    " << endl;
            cout << "======================================" << endl;
            
            vector<Fine> fines = getMemberFines(loggedInUser);
            
            if (fines.empty()) {
                cout << "You have no outstanding fines to pay." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            cout << "Your Outstanding Fines:" << endl;
            cout << "--------------------------------------" << endl;
            cout << left << setw(5) << "No." << " | " 
                 << setw(10) << "Fine ID" << " | " 
                 << setw(15) << "Book ISBN" << " | " 
                 << setw(15) << "Amount ($)" << " | " 
                 << "Reason" << endl;
            cout << "--------------------------------------" << endl;
            
            int count = 1;
            for (const auto& fine : fines) {
                cout << left << setw(5) << count << " | " 
                     << setw(10) << fine.fineId << " | " 
                     << setw(15) << fine.bookISBN << " | " 
                     << setw(15) << fixed << setprecision(2) << fine.amount << " | " 
                     << fine.reason << endl;
                count++;
            }
            
            cout << "--------------------------------------" << endl;
            cout << "Total fine amount: $" << fixed << setprecision(2) << getTotalFineAmount(loggedInUser) << endl;
            cout << "--------------------------------------" << endl;
            cout << "Enter fine number to pay (0 to cancel): ";
            
            int fineNum;
            if (!(cin >> fineNum)) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
                cout << "Invalid input. Operation cancelled." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (fineNum == 0) {
                cout << "Operation cancelled." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            if (fineNum < 1 || fineNum > fines.size()) {
                cout << "Invalid fine number." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            
            Fine selectedFine = fines[fineNum - 1];
            cout << "Selected fine amount: $" << fixed << setprecision(2) << selectedFine.amount << endl;
            cout << "Enter amount to pay (or press Enter for full amount): $";
            
            string amountStr;
            double amount = selectedFine.amount; // Default to full amount
            getline(cin, amountStr);
            
            if (!amountStr.empty()) {
                try {
                    amount = stod(amountStr);
                    if (amount <= 0 || amount > selectedFine.amount) {
                        cout << "Invalid amount. Payment must be between $0.01 and $" << selectedFine.amount << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    }
                } catch (const exception& e) {
                    cout << "Invalid amount format. Please enter a valid number." << endl;
                    cout << "Press Enter to continue...";
                    cin.get();
                    break;
                }
            }
            
            if (payFine(selectedFine.fineId, amount)) {
                cout << "Payment of $" << fixed << setprecision(2) << amount << " processed successfully." << endl;
            } else {
                cout << "Payment failed. Please try again later." << endl;
            }
            
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        case 10:
                displayMemberDetailsView(loggedInUser);
            break;
        case 11:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Press Enter to continue...";
            cin.get();
        }
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

void displayMemberDetailsView(const Member& member) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "          MEMBER DETAILS              " << endl;
    cout << "======================================" << endl;
    cout << "ID: " << member.Id << endl;
    cout << "Name: " << member.name << endl;
    cout << "Contact Info: " << member.contactInfo << endl;
    cout << "Username: " << member.username << endl;
    cout << "Membership Type: " << member.membershipType << endl;
    cout << "Blacklisted: " << (member.isBlacklisted ? "Yes" : "No") << endl;
    cout << "--------------------------------------" << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

void displayMemberTable(const vector<Member>& members) {
    clearScreen();
    cout << "=======================================================================================================" << endl;
    cout << "                                      MEMBER LIST                                                       " << endl;
    cout << "=======================================================================================================" << endl;
    cout << left << setw(5) << "ID" << " | " 
         << setw(25) << "Name" << " | " 
         << setw(25) << "Username" << " | " 
         << setw(30) << "Contact Info" << " | " 
         << setw(10) << "Type" << " | " 
         << "Blacklisted" << endl;
    cout << "=======================================================================================================" << endl;
    
    for (const auto& member : members) {
        cout << left << setw(5) << member.Id << " | " 
             << setw(25) << member.name << " | " 
             << setw(25) << member.username << " | " 
             << setw(30) << member.contactInfo << " | " 
             << setw(10) << member.membershipType << " | " 
             << (member.isBlacklisted ? "Yes" : "No") << endl;
    }
    cout << "=======================================================================================================" << endl;
    cout << "Total Members: " << members.size() << endl;
    cout << "Press Enter to continue...";
    cin.get();
} 

void displayBookTable(const vector<Book>& books) {
    clearScreen();
    cout << "=======================================================================================================" << endl;
    cout << "                                        BOOK LIST                                                       " << endl;
    cout << "=======================================================================================================" << endl;
    cout << left << setw(15) << "ISBN" << " | " 
         << setw(30) << "Title" << " | " 
         << setw(20) << "Author" << " | " 
         << setw(15) << "Genre" << " | " 
         << setw(8) << "Quantity" << " | " 
         << "Status" << endl;
    cout << "=======================================================================================================" << endl;
    
    for (const auto& book : books) {
        cout << left << setw(15) << book.ISBN << " | " 
             << setw(30) << book.title << " | " 
             << setw(20) << book.author << " | " 
             << setw(15) << book.genre << " | " 
             << setw(8) << book.quantity << " | " 
             << book.status << endl;
    }
    cout << "=======================================================================================================" << endl;
    cout << "Total Books: " << books.size() << endl;
    cout << "Press Enter to continue...";
    cin.get();
} 

void displayBorrowMenu(const Member& loggedInUser) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "          BORROW BOOK                 " << endl;
    cout << "======================================" << endl;
    
    vector<Book> books = listAllBooks();
    vector<Book> availableBooks;
    
    // Filter only available books
    for (const auto& book : books) {
        if (book.quantity > 0 && book.status != "Not Available") {
            availableBooks.push_back(book);
        }
    }
    
    if (availableBooks.empty()) {
        cout << "No available books found for borrowing." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    cout << "Available Books:" << endl;
    cout << "--------------------------------------" << endl;
    cout << left << setw(5) << "No." << " | " 
         << setw(15) << "ISBN" << " | " 
         << setw(30) << "Title" << " | " 
         << setw(20) << "Author" << " | " 
         << "Quantity" << endl;
    cout << "--------------------------------------" << endl;
    
    int count = 1;
    for (const auto& book : availableBooks) {
        cout << left << setw(5) << count << " | " 
             << setw(15) << book.ISBN << " | " 
             << setw(30) << book.title << " | " 
             << setw(20) << book.author << " | " 
             << book.quantity << endl;
        count++;
    }
    
    cout << "--------------------------------------" << endl;
    cout << "Enter book number to borrow (0 to cancel): ";
    int bookNum;
    
    if (!(cin >> bookNum)) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
        cout << "Invalid input. Operation cancelled." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (bookNum == 0) {
        cout << "Operation cancelled." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    if (bookNum < 1 || bookNum > availableBooks.size()) {
        cout << "Invalid book number." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    Book selectedBook = availableBooks[bookNum - 1];
    borrowBook(loggedInUser, selectedBook.ISBN);
    
    cout << "Press Enter to continue...";
    cin.get();
}

void displayReturnMenu(const Member& loggedInUser) {
    clearScreen();
    cout << "======================================" << endl;
    cout << "          RETURN BOOK                 " << endl;
    cout << "======================================" << endl;
    
    vector<Loan> loans = viewBorrowedBooks(loggedInUser);
    
    if (loans.empty()) {
        cout << "You have no borrowed books to return." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    cout << "Your Borrowed Books:" << endl;
    cout << "--------------------------------------" << endl;
    cout << left << setw(5) << "No." << " | " 
         << setw(15) << "ISBN" << " | " 
         << setw(30) << "Title" << " | " 
         << setw(12) << "Due Date" << " | " 
         << "Status" << endl;
    cout << "--------------------------------------" << endl;
    
    int count = 1;
    for (const auto& loan : loans) {
        // Get book details
        Book book = getBookByISBN(loan.ISBN);
        
        string status = "On time";
        if (loan.isOverdue) {
            status = "Overdue";
        }
        
        cout << left << setw(5) << count << " | " 
             << setw(15) << loan.ISBN << " | " 
             << setw(30) << book.title << " | " 
             << setw(12) << loan.dueDate << " | " 
             << status << endl;
        count++;
    }
    
    cout << "--------------------------------------" << endl;
    cout << "Enter book number to return (0 to cancel): ";
    int bookNum;
    
    if (!(cin >> bookNum)) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
        cout << "Invalid input. Operation cancelled." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (bookNum == 0) {
        cout << "Operation cancelled." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    if (bookNum < 1 || bookNum > loans.size()) {
        cout << "Invalid book number." << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    Loan selectedLoan = loans[bookNum - 1];
    returnBook(loggedInUser, selectedLoan.ISBN);
    
    cout << "Press Enter to continue...";
    cin.get();
} 