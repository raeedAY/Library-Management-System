#ifndef FINE_PAYMENT_H
#define FINE_PAYMENT_H

#include "member.h"
#include "bookManagement.h"

#include <string>
#include <vector>

using namespace std;

struct Fine {
    int fineId;
    string memberId;
    string ISBN;
    double amount;
    string reason;
    bool isPaid;
};

bool addFine(const Member& member, const string& ISBN, double amount, const string& reason);
bool payFine(int fineId, double amount);
vector<Fine> getMemberFines(const Member& member);
double getTotalFineAmount(const Member& member);
bool checkMemberHasFines(const Member& member);
bool applyFineExemption(int fineId, const string& exemptionReason);
bool adjustFineAmount(int fineId, double newAmount, const string& adjustmentReason);



#endif 