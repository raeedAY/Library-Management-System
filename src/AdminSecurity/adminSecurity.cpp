#include "../../include/adminSecurity.h"
#include "../../include/member.h"

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <functional>


using namespace std;


string hashPassword(const string& password) {
    size_t hashValue = hash<string>{}(password);
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hashValue;
    return ss.str();
}
    



Member checkLogin(string username, string password) {
    // put ur implementation here
}
