#include "../../include/adminSecurity.h"
#include "../../include/member.h"

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <functional>
#include <ctime>
#include <direct.h>

using namespace std;

string hashPassword(const string& password) {
    size_t hashValue = hash<string>{}(password);
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hashValue;
    return ss.str();
}
    


const vector<string> VALID_ROLES = {"admin", "librarian", "member"};

string getUserRole(const string& username) {
    // Open the members file
    ifstream memberFile("data/members.txt");
    if (!memberFile.is_open()) {
        cerr << "Error: Could not open members.txt for reading" << endl;
        return "member"; // Default to member role if file can't be opened
    }

    string line;
    while (getline(memberFile, line)) {
        // Split the line by pipe delimiter
        vector<string> fields;
        stringstream ss(line);
        string field;
        
        while (getline(ss, field, '|')) {
            fields.push_back(field);
        }
        
        // Check if we have enough fields and if username matches 
        if (fields.size() >= 6 && fields[3] == username) {
            memberFile.close();
            return fields[5]; // Return the membership type
        }
    }
    memberFile.close();

    // If user not found in members file, check for admin/librarian
    if (username == "admin") {
        return "admin";
    }
    
    if (username == "librarian1" || username == "librarian2") {
        return "librarian";
    }
    
    // Default to member role if not found
    return "member";
}


Member checkLogin(string username, string password) {
    Member user;
    user.username = username;
    user.membershipType = getUserRole(username);
    
    //i have initialized the chech login you can add your implmentation here
    
    return user;
}

// Function to backup the database
bool backupDatabase() {
    try {
        // Create backups directory
        _mkdir("src");
        _mkdir("src\\backups");
        
        // Create backup folder with timestamp
        time_t now = time(0);
        string backupFolder = "src\\backups\\backup_" + to_string(now);
        _mkdir(backupFolder.c_str());

        // List of files to backup
        string files[] = {"books.txt", "members.txt", "reservations.txt", "audit_logs.txt"};
        
        // Copy each file to backup
        for (const string& file : files) {
            ifstream src("src\\data\\" + file, ios::binary);
            if (src.is_open()) {
                ofstream dst(backupFolder + "\\" + file, ios::binary);
                dst << src.rdbuf();
                src.close();
                dst.close();
            }
        }
        
        cout << "Database backup created in: " << backupFolder << endl;
        return true;
    } catch (const exception& e) {
        cerr << "Backup error: " << e.what() << endl;
        return false;
    }
}

// Function to restore the database from latest backup
bool restoreDatabase() {
    try {
        // Create data directory
        _mkdir("src");
        _mkdir("src\\data");

        // List of files to restore
        string files[] = {"books.txt", "members.txt", "reservations.txt", "audit_logs.txt"};
        
        // Copy each file from backup to data folder
        for (const string& file : files) {
            ifstream src("src\\backups\\latest\\" + file, ios::binary);
            if (src.is_open()) {
                ofstream dst("src\\data\\" + file, ios::binary);
                dst << src.rdbuf();
                src.close();
                dst.close();
            }
        }
        
        cout << "Database restored from latest backup" << endl;
        return true;
    } catch (const exception& e) {
        cerr << "Restore error: " << e.what() << endl;
        return false;
    }
}
