#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>  // for std::hash
#include <sstream>
#include <iomanip>

using namespace std;


struct Book {
    string isbn;
    string title;
    string author;
    string genre;
    int quantity;
    int borrowCount = 0;
};

vector<Book> books;

struct Member {
    string id;
    string name;
    string contact;
    string membershipType;
};

vector<Member> members;


struct Fine {
    string memberId;
    double amount;
};

vector<Fine> fines;

string encryptPassword(const string& password) {
    hash<string> hasher;
    size_t hashed = hasher(password);
    stringstream ss;
    ss << hex << hashed;
    return ss.str();
}
void deleteBook(const string& isbn) {
    auto it = remove_if(books.begin(), books.end(),
        [&](const Book& b) { return b.isbn == isbn; });
    if (it != books.end()) {
        books.erase(it, books.end());
        cout << "Book deleted successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

void deleteMember(const string& id) {
    auto it = remove_if(members.begin(), members.end(),
        [&](const Member& m) { return m.id == id; });
    if (it != members.end()) {
        members.erase(it, members.end());
        cout << "Member deleted successfully.\n";
    } else {
        cout << "Member not found.\n";
    }
}
void returnBook(const string& isbn) {
    for (auto& b : books) {
        if (b.isbn == isbn) {
            ++b.quantity;
            cout << "Book returned successfully.\n";
            return;
        }
    }
    cout << "Book not found.\n";
}
int main() {
    int choice;
    string input;

    while (true) {
        cout << "\n--- Library Management Menu ---\n"
             << "1) Delete Book\n"
             << "2) Delete Member\n"
             << "3) Return Book\n"
             << "4) Delete Fine\n"
             << "5) Book Popularity Report\n"
             << "6) Encrypt Password\n"
             << "0) Exit\n"
             << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ISBN to delete: ";
                cin >> input;
                deleteBook(input);
                break;
            case 2:
                cout << "Enter Member ID to delete: ";
                cin >> input;
                deleteMember(input);
                break;
            case 3:
                cout << "Enter ISBN to return: ";
                cin >> input;
                returnBook(input);
                break;
            case 4:
                cout << "Enter Member ID to delete fine: ";
                cin >> input;
                deleteFine(input);
                break;
            case 5:
                showBookPopularity();
                break;
            case 6:
                cout << "Enter password: ";
                cin >> input;
                cout << "Hashed password: " << encryptPassword(input) << "\n";
                break;
            case 0:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid selection.\n";
        }
    }
}

