#ifndef REPORTING_ANALYTICS_H
#define REPORTING_ANALYTICS_H

#include "member.h"
#include "bookManagement.h"

#include <string>
#include <vector>

using namespace std;

struct Statistics {
    int totalMembers;
    int totalBooks;
    int availableBooks;
    int adminCount;
    int librarianCount;
    int memberCount;
};

Statistics StatisticsDashboard();
vector<Book> getMostPopularBooks(int limit);
vector<Member> getMostActiveMembers(int limit);

    // add ur definitions here

#endif