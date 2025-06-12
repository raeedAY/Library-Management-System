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
    

string getUserRole(const string& username) {
    // Define roles
    vector<string> librarianUsernames = {"admin", "librarian1", "librarian2"}; // Add more librarian usernames as needed
    
    // Check if the username is in the librarian list
    for (const auto& librarian : librarianUsernames) {
        if (username == librarian) {
            return "librarian";
        }
    }
    
    // If not found in librarian list, return member role
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
