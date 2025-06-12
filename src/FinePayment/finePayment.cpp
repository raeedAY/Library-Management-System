#include "../../include/finePayment.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define the fines vector as a global variable
vector<Fine> fines;

bool addFine(const Member& member, const string& ISBN, double amount, const string& reason) {
    clearScreen();
    // put ur implementation here
}

bool payFine(int fineId, double amount) {
    clearScreen();
    // put ur implementation here
}

vector<Fine> getMemberFines(const Member& member) {
    clearScreen();
    // put ur implementation here
}

double getTotalFineAmount(const Member& member) {
    // put ur implementation here
}

bool checkMemberHasFines(const Member& member) {
    // put ur implementation here
}

bool deleteFine(const string& memberId) {
    auto it = remove_if(fines.begin(), fines.end(),
        [&](const Fine& f) { return f.memberId == memberId; });
    if (it != fines.end()) {
        fines.erase(it, fines.end());
        cout << "Fine deleted successfully.\n";
        return true;
    } else {
        cout << "Fine not found for this member.\n";
        return false;
    }
}

bool applyFineExemption(int fineId, const string& exemptionReason) {
    // Valid exemption reasons
    const vector<string> validReasons = {
        "medical emergency",
        "natural disaster",
        "family emergency",
        "university closure",
        "documented technical issue"
    };

    // Check if the exemption reason is valid
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
            
            cout << "Fine exemption applied successfully.\n";
            return true;
        }
    }

    cout << "Fine not found with ID: " << fineId << "\n";
    return false;
}

bool adjustFineAmount(int fineId, double newAmount, const string& adjustmentReason) {
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
  