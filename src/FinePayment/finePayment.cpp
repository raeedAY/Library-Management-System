#include "../../include/finePayment.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/ui.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
