#ifndef ADMIN_SECURITY_H
#define ADMIN_SECURITY_H

#include "member.h"

#include <string>

using namespace std;

Member checkLogin(string username, string password);
string hashPassword(const string& password);

// Database backup and restore functions
bool backupDatabase(const string& backupFilePath);
bool restoreDatabase(const string& backupFilePath);

// put ur definitions here

#endif