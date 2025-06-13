#ifndef ADMIN_SECURITY_H
#define ADMIN_SECURITY_H

#include "member.h"

#include <string>

using namespace std;

string hashPassword(const string& password);
string getUserRole(const string& username);
Member checkLogin(string username, string password);

// Database backup and restore functions
bool backupDatabase();
bool restoreDatabase();

#endif