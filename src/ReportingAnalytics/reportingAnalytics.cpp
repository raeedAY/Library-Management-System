#include "../../include/reportingAnalytics.h"
#include "../../include/member.h"
#include "../../include/bookManagement.h"
#include "../../include/memberManagement.h"
#include "../../include/ui.h"

#include <iostream>
#include <vector>

using namespace std;

SystemStatus StatisticsDashboard() {
    clearScreen();
    // put ur implementation here
}
vector<Book> getMostPopularBooks(int limit) {
    clearScreen();
    vector<Book> books = listAllBooks(); // Load all books
    if (books.empty()) {
        cout << "No books in the system.\n";
        return {};
    }
    sort(books.begin(), books.end(),
         [](const Book& a, const Book& b) {
             return a.borrowCount > b.borrowCount;
         });
    cout << "\nBook Popularity Report:\n";
    int count = 0;
    for (const auto& b : books) {
        if (count++ >= limit) break;
        cout << " • " << b.title
             << " (ISBN: " << b.ISBN << ") — borrowed "
             << b.borrowCount << " times\n";
    }
    // Return the top 'limit' books
    if (books.size() > limit) {
        books.resize(limit);
    }
    return books;
}
vector<Member> getMostActiveMembers(int limit) {
    clearScreen();
    // put ur implementation here
}
