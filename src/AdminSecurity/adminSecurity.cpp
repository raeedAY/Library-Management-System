#include "../../include/adminSecurity.h"
#include "../../include/member.h"

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <functional>
#include <ctime>
#include <direct.h>
#include <iomanip>
#include <sstream>

using namespace std;

string hashPassword(const string& password) {
    size_t hashValue = hash<string>{}(password);
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hashValue;
    return ss.str();
}
    
const vector<string> VALID_ROLES = {"admin", "librarian", "member"};

string getUserRole(const string& username) {
    ifstream memberFile("data/members.txt");
    if (!memberFile.is_open()) {
        cerr << "Error: Could not open members.txt for reading" << endl;
        return "";
    }

    string line;
    while (getline(memberFile, line)) {
        stringstream ss(line);
        int id;
        string name, contactInfo, user, pass, role;
        bool blacklisted;
        
        char delimiter;
        ss >> id >> delimiter;
        getline(ss, name, '|');
        getline(ss, contactInfo, '|');
        getline(ss, user, '|');
        getline(ss, pass, '|');
        getline(ss, role, '|');
        ss >> blacklisted;
        
        if (user == username) {
            memberFile.close();
            return role;
        }
    }
    
    memberFile.close();
    return "";
}


Member checkLogin(string username, string password) {
    Member user;
    
    ifstream memberFile("data/members.txt");
    if (!memberFile.is_open()) {
        cerr << "Error: Could not open members.txt for reading" << endl;
        return user;
    }

    string line;
    while (getline(memberFile, line)) {
        stringstream ss(line);
        int id;
        string name, contactInfo, fileUsername, pass, role;
        bool blacklisted;
        
        char delimiter;
        ss >> id >> delimiter;
        getline(ss, name, '|');
        getline(ss, contactInfo, '|');
        getline(ss, fileUsername, '|');
        getline(ss, pass, '|');
        getline(ss, role, '|');
        ss >> blacklisted;
        
        if (fileUsername == username) {
            string hashedPassword = hashPassword(password);
            
            if (pass == hashedPassword) {
                user.Id = id;
                user.name = name;
                user.contactInfo = contactInfo;
                user.username = fileUsername;
                user.password = "";
                user.membershipType = role;
                user.isBlacklisted = blacklisted;
                
                memberFile.close();
                return user;
            }
            break;
        }
    }
    
    memberFile.close();
    return user;
}

// Function to backup the database
bool backupDatabase() {
    try {
        // Create backups directory if it doesn't exist
        if (_mkdir("backups") == -1 && errno != EEXIST) {
            cerr << "Error: Could not create backups directory" << endl;
            return false;
        }
        
        // Create backup folder with timestamp
        time_t now = time(0);
        tm* localTime = localtime(&now);
        
        // Format as YYYY-MM-DD_HH-MM-SS for better readability
        char timeStr[20];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d_%H-%M-%S", localTime);
        
        string backupFolder = "backups\\backup_" + string(timeStr);
        if (_mkdir(backupFolder.c_str()) == -1) {
            cerr << "Error: Could not create backup folder: " << backupFolder << endl;
            return false;
        }

        // List of files to backup
        string files[] = {"books.txt", "members.txt", "reservations.txt", "audit_logs.txt", "fines.txt", "loans.txt"};
        int successCount = 0;
        int totalFiles = sizeof(files)/sizeof(files[0]);
        
        cout << "Starting backup process..." << endl;
        
        // Copy each file to backup
        for (const string& file : files) {
            cout << "Backing up " << file << "... ";
            
            // Check if source file exists
            ifstream checkSrc("data\\" + file);
            if (!checkSrc.good()) {
                cout << "Skipped (file not found)" << endl;
                checkSrc.close();
                continue;
            }
            checkSrc.close();
            
            ifstream src("data\\" + file, ios::binary);
            if (src.is_open()) {
                ofstream dst(backupFolder + "\\" + file, ios::binary);
                if (dst.is_open()) {
                dst << src.rdbuf();
                    if (dst.good()) {
                        successCount++;
                        cout << "Success" << endl;
                    } else {
                        cout << "Failed to write backup file" << endl;
                    }
                    dst.close();
                } else {
                    cout << "Failed to create backup file" << endl;
                }
                src.close();
            } else {
                cout << "Failed to open source file" << endl;
            }
        }
        
        cout << "\nBackup completed: " << successCount << "/" << totalFiles << " files backed up successfully" << endl;
        cout << "Backup location: " << backupFolder << endl;
        
        return successCount > 0;
    } catch (const exception& e) {
        cerr << "Backup error: " << e.what() << endl;
        return false;
    }
}

// Function to restore the database from latest backup
bool restoreDatabase() {
    try {
        // Create data directory if it doesn't exist
        if (_mkdir("data") == -1 && errno != EEXIST) {
            cerr << "Error: Could not create data directory" << endl;
            return false;
        }

        // Check if backups directory exists
        filesystem::path backupsDir("backups");
        if (!filesystem::exists(backupsDir) || !filesystem::is_directory(backupsDir)) {
            cerr << "Error: Backups directory does not exist" << endl;
            return false;
        }

        // Get latest backup folder
        string latestBackup = "";
        time_t latestTime = 0;
        
        cout << "Available backups:" << endl;
        cout << "----------------------------" << endl;
        int count = 0;
        
            for (const auto& entry : filesystem::directory_iterator(backupsDir)) {
                if (filesystem::is_directory(entry)) {
                    string name = entry.path().filename().string();
                    if (name.find("backup_") != string::npos) {
                    count++;
                    cout << count << ". " << name << endl;
                    
                    // For timestamp-based backups
                    if (name.length() > 7) {
                        string timeStr = name.substr(7);
                        time_t backupTime = filesystem::last_write_time(entry).time_since_epoch().count();
                        
                        if (backupTime > latestTime) {
                            latestTime = backupTime;
                            latestBackup = name;
                        }
                    }
                }
            }
        }
        
        if (count == 0) {
            cerr << "No backups found." << endl;
            return false;
        }
        
        cout << "----------------------------" << endl;
        cout << "Latest backup: " << latestBackup << endl;
        cout << "Do you want to use this backup? (y/n): ";
        
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        string backupPath;
        
        if (choice == 'y' || choice == 'Y') {
            backupPath = "backups\\" + latestBackup;
        } else {
            cout << "Enter backup number to restore: ";
            int backupNum;
            cin >> backupNum;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (backupNum < 1 || backupNum > count) {
                cerr << "Invalid backup number." << endl;
                return false;
            }
            
            int i = 0;
            for (const auto& entry : filesystem::directory_iterator(backupsDir)) {
                if (filesystem::is_directory(entry)) {
                    string name = entry.path().filename().string();
                    if (name.find("backup_") != string::npos) {
                        i++;
                        if (i == backupNum) {
                            backupPath = "backups\\" + name;
                            break;
                        }
                    }
                }
            }
        }
        
        if (backupPath.empty()) {
            cerr << "Failed to determine backup path." << endl;
            return false;
        }
        
        // List of files to restore
        string files[] = {"books.txt", "members.txt", "reservations.txt", "audit_logs.txt", "fines.txt", "loans.txt"};
        int successCount = 0;
        int totalFiles = sizeof(files)/sizeof(files[0]);
        
        cout << "\nStarting restore process from " << backupPath << "..." << endl;
        
        // Copy each file from backup to data folder
        for (const string& file : files) {
            cout << "Restoring " << file << "... ";
            
            // Check if backup file exists
            ifstream checkSrc(backupPath + "\\" + file);
            if (!checkSrc.good()) {
                cout << "Skipped (backup file not found)" << endl;
                checkSrc.close();
                continue;
            }
            checkSrc.close();
            
            ifstream src(backupPath + "\\" + file, ios::binary);
            if (src.is_open()) {
                ofstream dst("data\\" + file, ios::binary);
                if (dst.is_open()) {
                dst << src.rdbuf();
                    if (dst.good()) {
                        successCount++;
                        cout << "Success" << endl;
                    } else {
                        cout << "Failed to write file" << endl;
                    }
                    dst.close();
                } else {
                    cout << "Failed to create destination file" << endl;
                }
                src.close();
            } else {
                cout << "Failed to open backup file" << endl;
            }
        }
        
        cout << "\nRestore completed: " << successCount << "/" << totalFiles << " files restored successfully" << endl;
        
        return successCount > 0;
    } catch (const exception& e) {
        cerr << "Restore error: " << e.what() << endl;
        return false;
    }
}
