#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

vector<string> split(string const& line, char sep, bool ignore_empty = false)
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

int main()
{
    // open file
    string filename;
    cout << "Input file: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file)
    {
        cout << "Error! The file "<< filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    // read through lines
    map<string, set<int>> found_words;
    string line;
    unsigned int counter = 1;
    while(getline(file, line))
    {
        vector<string> words = split(line, ' ', true);

        // go through words and read any new words
        for (string word : words)
        {
            // if the word hasn't existed
            if (found_words.find(word) == found_words.end())
            {
                found_words.insert({word, {}});
            }
            found_words.at(word).insert(counter);
        }
        counter ++;
    }

    // print out results
    for (map<string, set<int>>::iterator iter = found_words.begin(); iter != found_words.end(); iter ++)
    {
        cout << iter->first << " " << (int) iter->second.size() << ": ";
        // print individual line number
        set<int>::iterator line_numbers_iter = iter->second.begin();
        while(true)
        {
            cout << *line_numbers_iter;
            line_numbers_iter++;
            if(line_numbers_iter == iter->second.end())
            {
                break;
            }
            cout << ", ";
        }
        cout << endl;
    }
}
