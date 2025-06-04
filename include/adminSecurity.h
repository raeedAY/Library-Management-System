#ifndef ADMIN_SECURITY_H
#define ADMIN_SECURITY_H

#include "member.h"

#include <string>

using namespace std;

Member checkLogin(string username, string password);
string hashPassword(const string& password);

// put ur definitions here

#endif