#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

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

    map<string, unsigned int> playerScores;
    string line;
    while(getline(file, line))
    {
        string player = split(line, ':', true).at(0);
        unsigned int score = stoi(split(line, ':', true).at(1));
        if (playerScores.find(player) == playerScores.end())
        {
            playerScores.insert({player, {}});
        }
        playerScores.at(player) += score;
    }
    cout << "Final scores: " << endl;
    for (map<string, unsigned int>::iterator iter = playerScores.begin(); iter != playerScores.end(); iter ++)
    {
        cout << iter->first << ": " << iter->second << endl;
    }
}
