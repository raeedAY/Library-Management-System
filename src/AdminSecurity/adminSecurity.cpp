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
