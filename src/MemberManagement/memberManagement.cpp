#include "../../include/memberManagement.h"
#include "../../include/adminSecurity.h"
#include "../../include/member.h"
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
    
    // make sure that data/ exists
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


Member searchMember(int memberId) {
    clearScreen();
    // put ur implementation here
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
    vector<Member> members = listAllMembers();
    
    for (const auto& member : members) {
        if (member.Id == memberId) {
            // If member is blacklisted, they cannot borrow
            if (member.isBlacklisted) {
                cout << "This member is blacklisted and cannot borrow books." << endl;
                return false;
            }
            return true;
        }
    }
    
    cout << "Member with ID " << memberId << " not found." << endl;
    return false;
}
