#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

using namespace std;

struct Member {
    int Id;
    string name;
    string contactInfo;
    string username;
    string password;
    string membershipType;
    bool isBlacklisted;
    // int booksBorrowed
};

    

#endif