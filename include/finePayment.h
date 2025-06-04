#ifndef FINE_PAYMENT_H
#define FINE_PAYMENT_H

#include "member.h"
#include "bookManagement.h"

#include <string>
#include <vector>

using namespace std;

struct Fine {
    // int fineId etc
};

bool addFine(const Member& member, const string& ISBN, double amount, const string& reason);
bool payFine(int fineId, double amount);
vector<Fine> getMemberFines(const Member& member);
double getTotalFineAmount(const Member& member);
bool checkMemberHasFines(const Member& member);

    // add ur definitions here

#endif 