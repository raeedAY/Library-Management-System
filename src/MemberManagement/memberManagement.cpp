#include "../../include/memberManagement.h"
#include "../../include/adminSecurity.h"
#include "../../include/member.h"
#include "../../include/loanReservation.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

void addMember(Member& member) {
    clearScreen();
    cout << "Enter the User's name: ";
    cin >> member.name;
    cout << "Enter the User's contact information: ";
    cin >> member.contactInfo;
    cout << "Enter the User's username: ";
    cin >> member.username;
    cout << "Enter the User's password: ";
    string password;
    cin >> password;
    
    string hashedPassword = hashPassword(password);
    member.password = "";
    
    int nextId = 1;
    auto members = listAllMembers();
    if (!members.empty()) {
        for (const auto& m : members) {
            if (m.Id >= nextId) {
                nextId = m.Id + 1;
            }
        }
    }
    member.Id = nextId;
    
    if (member.membershipType.empty()) {
        member.membershipType = "member";
    }
    member.isBlacklisted = false;
    
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ofstream outfile;
    outfile.open("data/members.txt", ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open members.txt for writing" << endl;
        return;
    }
    
    // format: ID|name|contactInfo|username|hashedPassword|membershipType|isBlacklisted
    outfile << member.Id << "|" << member.name << "|" << member.contactInfo << "|" 
           << member.username << "|" << hashedPassword << "|" << member.membershipType 
           << "|" << member.isBlacklisted << endl;
    outfile.close();

    cout << "User added successfully!" << endl;
}

vector<Member> listAllMembers() {
      vector<Member> members;
    
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return members;
        }
    }
    
    ifstream infile("data/members.txt");

    if (!infile.is_open()) {
        ofstream outFile("data/members.txt");
        if (outFile.is_open()) {
            string adminPass = hashPassword("admin123");
            string librarianPass = hashPassword("lib123");
            string memberPass = hashPassword("member123");
            
            outFile << "1|Admin User|admin@example.com|admin|" << adminPass << "|admin|0" << endl;
            outFile << "2|Librarian User|librarian@example.com|librarian|" << librarianPass << "|librarian|0" << endl;
            outFile << "3|Regular Member|member@example.com|member|" << memberPass << "|member|0" << endl;
            outFile.close();
            
            infile.open("data/members.txt");
            if (!infile.is_open()) {
                return members;
            }
        } else {
            cerr << "Error: Could not create members.txt file" << endl;
        return members;
        }
    }

    string line;
    while (getline(infile, line)) {
        Member member;
        stringstream ss(line);
        
        char delimiter;
        ss >> member.Id >> delimiter;
        getline(ss, member.name, '|');
        getline(ss, member.contactInfo, '|');
        getline(ss, member.username, '|');
        getline(ss, member.password, '|');
        getline(ss, member.membershipType, '|');
        ss >> member.isBlacklisted;
        
        members.push_back(member);
    }

    infile.close();
    return members;
}


bool editMember(int memberId) {
    clearScreen();
    vector<Member> members = listAllMembers();
    bool memberFound = false;
    
    for (auto& member : members) {
        if (member.Id == memberId) {
            memberFound = true;
            
            cout << "Editing Member: " << member.name << " (ID: " << member.Id << ")" << endl;
            cout << "1. Edit Name (Current: " << member.name << ")" << endl;
            cout << "2. Edit Contact Info (Current: " << member.contactInfo << ")" << endl;
            cout << "3. Edit Username (Current: " << member.username << ")" << endl;
            cout << "4. Change Password" << endl;
            cout << "5. Change Membership Type (Current: " << member.membershipType << ")" << endl;
            cout << "6. Toggle Blacklist Status (Current: " << (member.isBlacklisted ? "Yes" : "No") << ")" << endl;
            cout << "7. Cancel" << endl;
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (choice) {
                case 1:
                    cout << "Enter new name: ";
                    getline(cin, member.name);
                    break;
                case 2:
                    cout << "Enter new contact info: ";
                    getline(cin, member.contactInfo);
                    break;
                case 3:
                    cout << "Enter new username: ";
                    getline(cin, member.username);
                    break;
                case 4: {
                    cout << "Enter new password: ";
                    string password;
                    getline(cin, password);
                    string hashedPassword = hashPassword(password);
                    member.password = hashedPassword;
                    break;
                }
                case 5: {
                    cout << "Select membership type:" << endl;
                    cout << "1. Member" << endl;
                    cout << "2. Librarian" << endl;
                    cout << "3. Admin" << endl;
                    cout << "Enter your choice: ";
                    int typeChoice;
                    cin >> typeChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch (typeChoice) {
                        case 1:
                            member.membershipType = "member";
                            break;
                        case 2:
                            member.membershipType = "librarian";
                            break;
                        case 3:
                            member.membershipType = "admin";
                            break;
                        default:
                            cout << "Invalid choice. Membership type not changed." << endl;
                    }
                    break;
                }
                case 6:
                    member.isBlacklisted = !member.isBlacklisted;
                    cout << "Blacklist status toggled to: " << (member.isBlacklisted ? "Blacklisted" : "Not Blacklisted") << endl;
                    break;
                case 7:
                    cout << "Edit cancelled." << endl;
                    return false;
                default:
                    cout << "Invalid choice." << endl;
                    return false;
            }
            
            break;
        }
    }
    
    if (!memberFound) {
        cout << "Member with ID " << memberId << " not found." << endl;
        return false;
    }
    
    ofstream outfile("data/members.txt");
    if (!outfile.is_open()) {
        cerr << "Error: Could not open members.txt for writing" << endl;
        return false;
    }
    
    for (const auto& member : members) {
        outfile << member.Id << "|" << member.name << "|" << member.contactInfo << "|" 
               << member.username << "|" << member.password << "|" << member.membershipType 
               << "|" << member.isBlacklisted << endl;
    }
    outfile.close();
    
    cout << "Member updated successfully!" << endl;
    cout << "Press Enter to continue...";
    cin.get();
    return true;
}

bool deleteMember(int memberId) {
    clearScreen();
    auto members = listAllMembers();
    auto it = remove_if(members.begin(), members.end(),
        [&](const Member& m) { return m.Id == memberId; });
    if (it != members.end()) {
        members.erase(it, members.end());
        
        ofstream outfile("data/members.txt");
        if (!outfile.is_open()) {
            cerr << "Error: Could not open members.txt for writing" << endl;
            return false;
        }
        
        for (const auto& member : members) {
            outfile << member.Id << "|" << member.name << "|" << member.contactInfo << "|" 
                   << member.username << "|" << member.password << "|" << member.membershipType 
                   << "|" << member.isBlacklisted << endl;
        }
        outfile.close();
        
        cout << "Member deleted successfully.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return true;
    } else {
        cout << "Member not found.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return false;
    }
}

Member searchMember(int memberId) {
    clearScreen();
    vector<Member> members = listAllMembers();
    
    for (const auto& member : members) {
        if (member.Id == memberId) {
            cout << "Member found:" << endl;
            cout << "ID: " << member.Id << endl;
            cout << "Name: " << member.name << endl;
            cout << "Contact: " << member.contactInfo << endl;
            cout << "Username: " << member.username << endl;
            cout << "Membership Type: " << member.membershipType << endl;
            cout << "Blacklisted: " << (member.isBlacklisted ? "Yes" : "No") << endl;
            cout << "Press Enter to continue...";
            cin.get();
            return member;
        }
    }
    
    cout << "Member with ID " << memberId << " not found." << endl;
    cout << "Press Enter to continue...";
    cin.get();
    return Member{};
}

bool updateMemberStatus(int memberId, bool isBlacklisted) {
    clearScreen();
    vector<Member> members = listAllMembers();
    bool memberFound = false;
    
    for (auto& member : members) {
        if (member.Id == memberId) {
            member.isBlacklisted = isBlacklisted;
            memberFound = true;
            break;
        }
    }
    
    if (!memberFound) {
        cout << "Member with ID " << memberId << " not found." << endl;
        return false;
    }
    
    // Open the file for writing (overwrite)
    ofstream outfile("data/members.txt");
    if (!outfile.is_open()) {
        cerr << "Error: Could not open members.txt for writing" << endl;
        return false;
    }
    
    // Write all members back to the file
    for (const auto& member : members) {
        outfile << member.Id << "|" << member.name << "|" << member.contactInfo << "|" 
               << member.username << "|" << member.password << "|" << member.membershipType 
               << "|" << member.isBlacklisted << endl;
    }
    outfile.close();
    
    cout << "Member status updated successfully!" << endl;
    return true;
}

bool checkBorrowingLimit(int memberId) {
    // Load the member's loans
    extern vector<Loan> loans; // Declare as extern to access loans from loanReservation.cpp
    
    // Load loans
    ifstream file("data/loans.txt");
    if (!file.is_open()) {
        // If file doesn't exist, member has no loans, so they're under the limit
        return true;
    }
    
    int activeLoans = 0;
    string line;
    
    while (getline(file, line)) {
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
            int loanMemberId = stoi(tokens[0]);
            bool isReturned = (tokens[3] == "1");
            
            if (loanMemberId == memberId && !isReturned) {
                activeLoans++;
            }
        }
    }
    
    file.close();
    
    // Maximum books a member can borrow is 5
    const int MAX_BOOKS = 5;
    return (activeLoans < MAX_BOOKS);
}
