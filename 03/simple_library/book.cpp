#include "book.hh"
#include <iostream>

Book::Book(std::string const &author, std::string const &title):
    author_(author),
    title_(title),
    loan_date_(Date()),
    due_date_(Date()),
    loaned_(false)
{

}

void Book::loan(Date d)
{
    if(loaned_)
    {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
    else
    {
        loan_date_ = d;
        due_date_ = loan_date_;
        due_date_.advance(28);
        loaned_ = true;
    }

}

void Book::print() const
{
    std::cout << author_ << " : " << title_ << std::endl;

    //book is available ?
    if(!loaned_)
    {
        std::cout << "- available" << std::endl;
    }
    else
    {
        std::cout << "- loaned: ";
        loan_date_.print();
        std::cout << "- to be returned: ";
        due_date_.print();
    }

}

void Book::renew()
{
    if(!loaned_)
    {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
    else
    {
        due_date_.advance(28);
    }

}

void Book::give_back()
{
    loaned_ = false;

}
