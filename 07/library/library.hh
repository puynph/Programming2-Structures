#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <string>
#include <map>
#include <vector>
using namespace std;

struct Book;
using Collection = map<string, vector<Book>>;

struct Book
{
    string author;
    string title;
    int reservations;
};

class Library
{
public:
    Library(string const &name);
    void addAuthor(const string &author);
    void addBook(const string &author, const string &title, int reservation);
    Collection getCollection() const;

private:
    //map contains author and their books
    Collection collection_;
    string name_;
};

#endif // LIBRARY_HH

