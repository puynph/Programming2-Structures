#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"

class Book
{
public:
    Book(std::string const &author, std::string const &title);
    void loan(Date d);
    void print() const;
    void renew();
    void give_back();

private:
    std::string author_;
    std::string title_;
    Date loan_date_;
    Date due_date_;
    bool loaned_;

};

#endif // BOOK_HH
