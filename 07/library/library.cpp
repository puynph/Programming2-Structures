#include "library.hh"


Library::Library(const string &name):
    collection_({}),
    name_(name)
{

}

void Library::addAuthor(const string &author)
{
    if(collection_.find(author) == collection_.end())
    {
        collection_.insert({author,{}});
    }
}

void Library::addBook(const string &author, const string &title, int reservation)
{
    //create Book, add author, add book to author
    addAuthor(author);
    collection_.at(author).push_back(Book {author, title, reservation});
}

Collection Library::getCollection() const
{
    return collection_;
}
