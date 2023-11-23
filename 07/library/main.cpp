#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include "library.hh"

/* Library Project
 *
 * Desc:
 *   This program implements a program that reads the book collection data of
 * different libraries from an input file. The data is then stored in a listed <map>
 * such that the key is <string> library name, payload is <Collection>. <Collection>
 * is a <map>, whose key is <string> author name and payload is <Book>. <Book> is
 * a struct type, which is declared in header.
 *   At first, the program asks for the input file. If the file is not valid or cannot
 * be opened, the program terminated with return EXIT_FAILURE. Otherwise, on each round,
 * different command is used to search data in question, while utilising the data
 * structure of the program.
 *   This program a class for a library (Library) in files library.hh and library.cpp.
 * Methods as addBook, getCollection in some way makes it convenient to search for data
 * (as used in the below codes).
 *   The program terminates with the return value EXIT_SUCCESS when the user gives
 * a quitting command ("quit").
 *
 * Program author
 * Name: Uyen Phan
 * Student number: 151372454
 * UserID: cpuyph
 * E-Mail: uyen.phan@tuni.fi
 * */

using namespace std;

vector<string> split(string const &line, char sep, bool ignore_empty = false)
{
    vector<string> split_vector = {};
    string current_string = "";
    //loop through each char in line
    for (char c : line)
    {
        //check if each char is a seperation mark
        if (c == sep)
        {
            //current string is finished
            if (!(current_string.empty() && ignore_empty))
            {
                split_vector.push_back(current_string);
                current_string.clear();
            }
        }
        else
        {
            current_string += c;
        }

    }

    if (!(current_string.empty() && ignore_empty))
    {
        split_vector.push_back(current_string);
        current_string.clear();
    }

    return split_vector;
}

//check the validation of each line in input file
bool isLineValid(string const &line)
{
    // check if line contains appropriate amount 
    // check split vector size
    vector <string> line_parts = split(line, ';');

    if (line_parts.size() != 4)
    {
        return false;
    }

    // check if there's any part missing, in case semi-colon is at the end of line.
    for (string &line_part : line_parts)
    {
        if (line_part.empty())
            return false;
    }

    // check if the number of reservations is valid
    bool isDigit = true;
    for (char &c : line_parts.at(3))
    {
        if (!isdigit(c))
        {
            isDigit = false;
            break;
        }
    }
    if (isDigit)
    {
        return true;
    }
    if (line_parts.at(3) == "on-the-shelf")
        return true;
    return false;
}

// reading the input file
// create libraries
// add books etc. to library
// modify database structure 
// this function returns a boolean value, if false, the program returns EXIT_FAILURE
bool readDataIntoDatabase(string const &filename, map<string, Library> &database)
{
    // open file 
    ifstream file(filename);
    
    // handle errors
    if (!file)
    {
        cout << "Error: input file cannot be opened" << endl;
        return false;
    }
    
    // loop through line -> action
    string line;
    while(getline(file, line))
    {
        // handle line input 
        // error check
        if (isLineValid(line))
        {
            // add line info to library system
            vector<string> line_parts = split(line, ';');
            // write out the different params
            string libraryName = line_parts.at(0);
            string author = line_parts.at(1);
            string title = line_parts.at(2);
            // check reservation amount
            int reservations = 0; // on-the-shelf
            if (line_parts.at(3) != "on-the-shelf")
            {
                //stoi command to change string into integer
                reservations = stoi(line_parts.at(3));
            }
            // add library to system
            if (database.find(libraryName) == database.end())
            {
                database.insert({libraryName, Library(libraryName)});
            }

            // the same book in the same library has existed
            // the valid number of reservations should be the latest.
            if (database.at(libraryName).getCollection().count(author))
            {
                bool existed = false;
                vector<Book> books = database.at(libraryName).getCollection().at(author);
                for (Book &book : books)
                {
                    if (book.title == title)
                    {
                        book.reservations = reservations;
                        existed = true;
                    }
                }
                if (existed)
                {
                    continue;
                }
            }
            database.at(libraryName).addBook(author, title, reservations);

        }
        else
        {
            cout << "Error: empty field" << endl;
            return false;
        }
    }
    file.close();
    return true;
}

void printLibraries(map<string, Library> const &database)
{
    // iterate through the map to get the name if the library, which is key
    for (map<string, Library>::const_iterator iter = database.begin();
         iter != database.end(); iter ++)
    {
        cout << iter->first << endl;
    }
}

void printMaterial(map<string, Library> const &database, string const &libName)
{
    // type check for debugging purpose
    // cout << typeid(database.at(libName)).name();
    // use getCollection method to get the collection of the wanted library
    Collection collection = database.at(libName).getCollection();
    // Collection type is a <map>, key is <string> and payload is Book type
    for (auto &dataPair : collection)
    {
        for (Book const &book : dataPair.second)
        {
            cout << dataPair.first << ": " << book.title << endl;
        }
    }
}

void printBooks(Collection const &collection, string const &authorName)
{
    // loop through the author name and Book properties
    for (auto &dataPair : collection)
    {
        for (Book const &book : dataPair.second)
        {
            // if the key in <map> collection is the name of wanted author
            if (dataPair.first == authorName)
            {
                if (book.reservations != 0)
                {
                    cout << book.title << " --- " << book.reservations << " reservations" << endl;
                }
                else
                {
                    cout << book.title << " --- " << "on the shelf" << endl;
                }
            }
        }
    }
}

void printReservable(map<string, Library> const &database, string const &authorName, string const &bookName)
{
    // many reservations
    int min = 100;
    // same minimum number of reservations may appear in many libraries
    map<string, int> libraries;
    bool foundBook = false;
    for (map<string, Library>::const_iterator iter = database.begin();
         iter != database.end(); iter ++)
    {
        // cout << typeid((iter->second).getCollection().at(authorName)).name() << endl;
        // get the collection for different library of each iterator
        Collection collection = (iter->second).getCollection();
        for (Collection::const_iterator iter2 = collection.begin(); iter2 != collection.end(); iter2 ++)
        {
            for (Book const &book : iter2->second)
            {
                if (book.author == authorName && book.title == bookName && book.reservations <= min)
                {
                    min = book.reservations;
                    foundBook = true;
                    libraries.insert({iter->first, book.reservations});
                }
            }
        }
    }

    if (!foundBook)
    {
        cout << "Book is not a library book" << endl;
        return;
    }

    // iterate through the libraries map and keep only the library with minimum reservations
    for (map<string, int>::const_iterator iter = libraries.begin();
         iter != libraries.end(); iter ++)
    {
        if (iter->second != min)
        {
            libraries.erase(iter->first);
        }

    }

    if (min > 99)
    {
        cout << "Book is not reservable from any library" << endl;
    }
    else
    {
        if (min == 0)
        {
            cout << "on the shelf" << endl;
        }
        else
            cout << min << " reservations" << endl;
        for (auto &dataPair : libraries)
        {
            cout << "--- " << dataPair.first << endl;
        }
    }

}

void printLoanable(map<string, Library> const &database)
{
    map<string, vector<string>> loanable;
    for (map<string, Library>::const_iterator iter = database.begin();
         iter != database.end(); iter ++)
    {
        //cout << typeid((iter->second).getCollection().at(authorName)).name() << endl;
        Collection collection = (iter->second).getCollection();
        for (auto iter2 = collection.begin(); iter2 != collection.end(); iter2 ++)
        {
            for (Book &book : iter2->second)
            {
                // if the book is still on-the-shelf
                if (book.reservations == 0)
                {
                    if (loanable.find(book.author) == loanable.end())
                    {
                        loanable.insert({book.author, {}});
                    }
                    loanable.at(book.author).push_back(book.title);

                }
            }
        }
    }

    for (auto &dataPair : loanable)
    {
        // sort the book name in alphabetical order
        sort(dataPair.second.begin(), dataPair.second.end());
        for (string &book : dataPair.second)
            cout << dataPair.first << ": " << book << endl;
    }
}

// check the size of different input command, if invalid, returns false
bool userInputSize(vector<string> command)
{
    if (command.at(0) == "quit" || command.at(0) == "libraries" || command.at(0) == "loanable")
    {
        return command.size() == 1;
    }
    else if (command.at(0) == "material")
    {
        return command.size() == 2;
    }
    else if (command.at(0) == "books")
    {
        return command.size() == 3;
    }
    else if (command.at(0) == "reservable")
    {
        return command.size() >= 3;
    }
    else
    {
        cout << "Error: unknown command" << endl;
        return true;
    }
}

int main()
{
    // init data structure
    map<string, Library> allLibraries;
    // ask for input file 
    string filename;
    cout << "Input file: ";
    getline(cin, filename);
    if (!readDataIntoDatabase(filename, allLibraries))
    {
        return EXIT_FAILURE;
    }

    // interface
    string input;
    while (true)
    {
        cout << "lib> ";
        getline(cin, input);
        vector<string> userInput = split(input, ' ');
        if (!userInputSize(userInput))
        {
            cout << "Error: wrong number of parameters" << endl;
            continue;
        }
        if (userInput.at(0) == "quit")
        {
            break;
        }
        else if (userInput.at(0) == "libraries")
        {
            printLibraries(allLibraries);
        }
        else if (userInput.at(0) == "material")
        {
            // check key is not in map
            if (!allLibraries.count(userInput.at(1)))
            {
                cout << "Error: unknown library" << endl;
            }
            else
            {
                printMaterial(allLibraries, userInput.at(1));
            }

        }
        else if (userInput.at(0) == "books")
        {
            if (!allLibraries.count(userInput.at(1)))
            {
                cout << "Error: unknown library" << endl;
            }
            else
            {
                Collection collection = allLibraries.at(userInput.at(1)).getCollection();
                if (!collection.count(userInput.at(2)))
                {
                    cout << "Error: unknown author" << endl;
                }
                else
                {
                    printBooks(collection, userInput.at(2));
                }
            }
        }

        else if (userInput.at(0) == "reservable")
        {
            string author = userInput.at(1);
            string book = "";
            // extract the book name from user input
            for (vector< int >::size_type i = 2; i < userInput.size(); i ++)
            {
                book += userInput.at(i);
                if (i != userInput.size()-1)
                {
                    book += ' ';
                }
            }
            // remove the quotation marks if there are any
            book.erase(remove(book.begin(), book.end(), '"'), book.end());
            printReservable(allLibraries, author, book);
        }

        else if (userInput.at(0) == "loanable")
        {
            printLoanable(allLibraries);
        }
    }
    return EXIT_SUCCESS;
}
