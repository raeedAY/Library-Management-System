#include "../../include/finePayment.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

vector<Fine> fines;
void loadFines() {
    fines.clear();
    
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ifstream file("data/fines.txt");
    if (!file.is_open()) {
        ofstream createFile("data/fines.txt");
        createFile.close();
        return;
    }
    
    string line;
    while (getline(file, line)) {
        Fine fine;
        size_t pos = 0;
        string token;
        vector<string> tokens;
        
        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);
        
        if (tokens.size() >= 6) {
            fine.fineId = stoi(tokens[0]);
            fine.memberId = tokens[1];
            fine.ISBN = tokens[2];
            fine.amount = stod(tokens[3]);
            fine.reason = tokens[4];
            fine.isPaid = (tokens[5] == "1");
            fines.push_back(fine);
        }
    }
    file.close();
}

// Helper function to save fines to file
void saveFines() {
    fs::path dataDirPath = "data";
    if (!fs::exists(dataDirPath)) {
        try {
            fs::create_directory(dataDirPath);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error: Could not create directory 'data'. " << e.what() << endl;
            return;
        }
    }
    
    ofstream file("data/fines.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open fines.txt for writing" << endl;
        return;
    }
    
    for (const auto& fine : fines) {
        file << fine.fineId << "|" << fine.memberId << "|" << fine.ISBN << "|"
             << fine.amount << "|" << fine.reason << "|" << (fine.isPaid ? "1" : "0") << endl;
    }
    file.close();
}

bool addFine(const Member& member, const string& ISBN, double amount, const string& reason) {
    clearScreen();
    
    loadFines();
    
    Fine newFine;
    newFine.fineId = fines.empty() ? 1 : fines.back().fineId + 1;
    newFine.memberId = to_string(member.Id);
    newFine.ISBN = ISBN;
    newFine.amount = amount;
    newFine.reason = reason;
    newFine.isPaid = false;
    
    fines.push_back(newFine);
    saveFines();
    
    cout << "Fine added successfully!" << endl;
    return true;
}

bool payFine(int fineId, double amount) {
    clearScreen();
    
    loadFines();
    
    for (auto& fine : fines) {
        if (fine.fineId == fineId) {
            if (fine.isPaid) {
                cout << "This fine has already been paid." << endl;
                return false;
            }
            
            if (amount < fine.amount) {
                cout << "Partial payment accepted. Remaining amount: $" << (fine.amount - amount) << endl;
                fine.amount -= amount;
            } else {
                cout << "Fine paid in full." << endl;
                fine.isPaid = true;
            }
            
            saveFines();
            return true;
        }
    }
    
    cout << "Fine not found with ID: " << fineId << endl;
    return false;
}

vector<Fine> getMemberFines(const Member& member) {
    clearScreen();
    
    loadFines();
    
    vector<Fine> memberFines;
    for (const auto& fine : fines) {
        if (fine.memberId == to_string(member.Id) && !fine.isPaid) {
            memberFines.push_back(fine);
            cout << "Fine ID: " << fine.fineId << endl;
            cout << "Amount: $" << fine.amount << endl;
            cout << "Reason: " << fine.reason << endl;
            cout << "Book ISBN: " << fine.ISBN << endl;
            cout << "------------------------" << endl;
        }
    }
    
    if (memberFines.empty()) {
        cout << "No outstanding fines for this member." << endl;
    }
    
    return memberFines;
}

double getTotalFineAmount(const Member& member) {
    loadFines();
    
    double total = 0.0;
    for (const auto& fine : fines) {
        if (fine.memberId == to_string(member.Id) && !fine.isPaid) {
            total += fine.amount;
        }
    }
    
    return total;
}

bool checkMemberHasFines(const Member& member) {
    loadFines();
    
    for (const auto& fine : fines) {
        if (fine.memberId == to_string(member.Id) && !fine.isPaid) {
            return true;
        }
    }
    
    return false;
}

bool deleteFine(const string& memberId) {
    loadFines();
    
    auto it = remove_if(fines.begin(), fines.end(),
        [&](const Fine& f) { return f.memberId == memberId; });
    if (it != fines.end()) {
        fines.erase(it, fines.end());
        saveFines();
        cout << "Fine deleted successfully.\n";
        return true;
    } else {
        cout << "Fine not found for this member.\n";
        return false;
    }
}

bool applyFineExemption(int fineId, const string& exemptionReason) {
    loadFines();
    
    // Valid exemption reasons
    const vector<string> validReasons = {
        "medical emergency",
        "natural disaster",
        "family emergency",
        "university closure",
        "documented technical issue"
    };

    bool isValidReason = false;
    for (const auto& reason : validReasons) {
        if (exemptionReason == reason) {
            isValidReason = true;
            break;
        }
    }

    if (!isValidReason) {
        cout << "Invalid exemption reason. Valid reasons are:\n";
        for (const auto& reason : validReasons) {
            cout << "- " << reason << "\n";
        }
        return false;
    }

    // Find the fine with the given ID
    for (auto& fine : fines) {
        if (fine.fineId == fineId) {
            // Apply the exemption by setting the amount to 0 and marking it as paid
            fine.amount = 0.0;
            fine.isPaid = true;
            fine.reason += " (Exempted - " + exemptionReason + ")";
            
            saveFines();
            cout << "Fine exemption applied successfully.\n";
            return true;
        }
    }

    cout << "Fine not found with ID: " << fineId << "\n";
    return false;
}

bool adjustFineAmount(int fineId, double newAmount, const string& adjustmentReason) {
    loadFines();
    
    // Find the fine with the given ID
    for (auto& fine : fines) {
        if (fine.fineId == fineId) {
            // Validate the new amount is not negative
            if (newAmount < 0) {
                cout << "Error: New fine amount cannot be negative.\n";
                return false;
            }

            // Calculate the adjustment amount
            double adjustment = fine.amount - newAmount;
            
            // Update the fine amount
            fine.amount = newAmount;
            
            // Add adjustment reason to the fine's reason
            fine.reason += " (Adjusted - " + adjustmentReason + ")";
            
            saveFines();
            cout << "Fine amount adjusted successfully.\n";
            cout << "Previous amount: $" << fine.amount + adjustment << "\n";
            cout << "New amount: $" << fine.amount << "\n";
            cout << "Adjustment: $" << adjustment << "\n";
            
            return true;
        }
    }
    
    cout << "Fine not found with ID: " << fineId << "\n";
    return false;
}
  