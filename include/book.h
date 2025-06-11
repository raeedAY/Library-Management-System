#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    std::string ISBN;
    std::string title;
    std::string author;
    std::string status;
    
    Book() = default;
    Book(std::string isbn, std::string title, std::string author)
        : ISBN(isbn), title(title), author(author), status("available") {}
};

#endif // BOOK_H 