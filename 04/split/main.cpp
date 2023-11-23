#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string const& line, char sep, bool ignore_empty = false)
{
    std::vector<std::string> split_vector = {};
    std::string current_string = "";
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

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
