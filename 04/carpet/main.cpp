/* Mystery carpet
 *
 * Desc:
 *   This program implements a mystery carpet applying pattern matching.
 * The carpet consists of squares of different colors, which also holds
 * true for the pattern, but the size of the pattern is always 2 x 2, i.e.
 * it has four colored squares. The program searches for pattern
 * occurrences from the carpet.
 *   At first, the program asks for the size of the carpet (width and heigth).
 * The user is also asked for if the carpet (grid) will be filled with
 * randomly drawn colors, or with user-given ones. Depending on the input, 2
 * functions are utilised to create the carpet. In the latter option, the user
 * is asked to input a long string of colors, which should be precise with the
 * size of required carpet.
 *   On each round, the user is asked for a 2 x 2 pattern. The program prints, how
 * many occurrences was found and from which coordinates they were found.
 *   The program checks if the user-given colors are among accepted ones.
 * The program terminates when the user gives a quitting command ('q' or 'Q').
 *
 * Program author
 * Name: Uyen Phan
 * Student number: 151372454
 * UserID: cpuyph
 * E-Mail: uyen.phan@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 * */

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

//this split function is then used to read user input
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
            current_string += c;

    }

    if (!(current_string.empty() && ignore_empty))
    {
        split_vector.push_back(current_string);
        current_string.clear();
    }

    return split_vector;
}

//color declaration
enum Color{R, G, B, Y, W, COLORS_AMOUNT};

//map the integer from enum to its corresponding character
const std::vector<char> ENUM_TO_COLOR = {'R', 'G', 'B', 'Y', 'W'};

/*This function creates random carpet by mapping random number to Color.
 * It returns a 2D vector <Color data type> carpet
 * :param: int width, int height
 * :return: std::vector<std::vector<Color>>
 */
std::vector<std::vector<Color>> createRandomCarpet(int columnSize, int rowSize)
{
    int seed_value;
    std::cout << "Enter a seed value: ";
    std::cin >> seed_value;
    std::default_random_engine gen(seed_value);
    std::uniform_int_distribution<int> distr(0, 4);

    //create 2D vector carpet
    std::vector<std::vector<Color>> carpet;
    for (int i = 0; i < rowSize; i++)
    {
        //initialize a new row for each iteration
        std::vector<Color> row;
        for (int j = 0; j < columnSize; j++)
        {
            int rand = distr(gen);
            //different created random number corresponds with different color
            row.push_back(Color(rand));
        }
        //add row into the actual carpet
        carpet.push_back(row);
    }
    return carpet;
}

/* This function calculate the index of a character
 * in the vector
*/
int getIndex(std::vector<char> v, char K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {
        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }
    else
    {
        // If the element is not in the vector
        return -1;
    }
}

/*This function creates input carpet by going through the string input and
 * mapping corresponding char to its Color data type.
 * It returns a 2D vector <Color data type> carpet
 * :param: int width, int height, std::string carpetColor
 * :return: std::vector<std::vector<Color>>
 */
std::vector<std::vector<Color>> createInputCarpet(int columnSize, int rowSize, std::string carpetColor)
{
    //initialize an index to get the element from the input string
    int index = 0;
    std::vector<std::vector<Color>> carpet;
    for (int i = 0; i < rowSize; i++)
    {
        std::vector<Color> row;
        for (int j = 0; j < columnSize; j++ )
        {
            row.push_back(Color(getIndex(ENUM_TO_COLOR, carpetColor[index])));
            index ++;
        }
        carpet.push_back(row);
    }
    return carpet;

}


int main()
{
    //different input from user
    int height, width;
    char input;
    //a string input to handle invalid input (when input is only asked for a character)
    std::string inputString;
    std::string line;
    std::string inputCarpet;

    std::vector<std::vector<Color>> carpet;
    std::cout << "Enter carpet's width and height: " ;
    std::getline(std::cin, line);

    //numeric input
    std::vector<std::string> numerics = split(line, ' ', true);
    //stoi command to change string into integer
    width = std::stoi(numerics.at(0));
    height = std::stoi(numerics.at(1));

    //error is raised when the size of carpet does not meet the requirement
    if (width < 2 || height < 2 )
    {
        std::cout << " Error: Carpet cannot be smaller than pattern." << std::endl;
        return EXIT_FAILURE;
    }


    while (true)
    {
        std::cout << "Select start (R for random, I for input): ";
        std::cin >> inputString;
        if (inputString.size() > 1)
            continue;

        //capitalize the input
        input = toupper(inputString.at(0));
        if (input != 'R' && input != 'I')
            continue;

        //input carpet
        if (input == 'I')
        {
            std::cout << "Input: ";
            std::cin >> inputCarpet;
            //.....
            if (inputCarpet.size() != (size_t) height*width)
            {
                std::cout << " Error: Wrong amount of colors." << std::endl;
                continue;
            }

            //create a boolean value to flip the flag in times of invalid input
            bool unknown = false;

            //loop through each char in the input carpet
            for (char c : inputCarpet)
            {
                if (c != 'R' && c!= 'G' && c!= 'B' && c!= 'Y' && c!= 'W')
                {
                    std::cout << " Error: Unknown color." << std::endl;
                    //the flag is flipped
                    unknown = true;
                    break;
                }
            }

            //continues the loop
            if (unknown)
                continue;

            //otherwise, create from valid input and get out of the loop
            carpet = createInputCarpet(width, height, inputCarpet);
            break;
        }

        //random carpet
        else if (input == 'R')
        {
            carpet = createRandomCarpet(width, height);
            break;
        }
    }


    //print carpet
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            std::cout << ENUM_TO_COLOR.at(carpet.at(i).at(j)) << ' ';
        }
        std::cout << std::endl;
    }

    //string pattern input
    std::string findColor;
    while (true)
    {
        std::cout << "Enter 4 colors, or q to quit: ";
        std::cin >> findColor;

        //capitalize the input string
        std::transform(findColor.begin(), findColor.end(), findColor.begin(), ::toupper);

        //if valid input, break the loop
        if (findColor == "Q")
            break;

        if (findColor.size() != 4)
        {
            std::cout << " Error: Wrong amount of colors." << std::endl;
            continue;
        }

        //a bool value to flip the flag when invslid input
        bool unknown = false;
        for (char c : findColor)
        {
            if (c != 'R' && c!= 'G' && c!= 'B' && c!= 'Y' && c!= 'W')
            {
                std::cout << " Error: Unknown color." << std::endl;
                unknown = true;
                break;
            }

        }

        if (unknown)
            continue;

        //vector Color type to map the string input to corresponding color
        std::vector<Color> findColorVector;
        for (char c : findColor)
        {
            findColorVector.push_back(Color(getIndex(ENUM_TO_COLOR, c)));
        }

        //2D vector coordinates contain all positions of the pattern found in the carpet
        std::vector<std::vector<int>> cords;
        for (int i = 0; i < height; i++)
        {
            //....
            if (i + 1 == height)
                continue;
            for (int j = 0; j < width; j++)
            {
                if (j + 1 == width)
                    continue;

                //find the position of the first pattern in the carpet
                //then check it it satisfies for all of its neighbour
                if (carpet.at(i).at(j) == findColorVector.at(0))
                    if (carpet.at(i).at(j + 1) == findColorVector.at(1))
                        if (carpet.at(i+1).at(j) == findColorVector.at(2))
                            if (carpet.at(i+1).at(j+1) == findColorVector.at(3))
                            {
                                std::vector<int> cord;
                                cord.push_back(i);
                                cord.push_back(j);

                                //push each coordinate into 2D coordinates
                                cords.push_back(cord);
                            }

            }

        }

        if (cords.size() != 0)
        {
            //loop through each coordinate in the coordinates vector
            for (std::vector<int> cord : cords)
            {
                std::cout << " - Found at (" << cord.at(1) + 1 << ", " << cord.at(0) + 1 << ")" << std::endl;
            }
        }
        std::cout << " = Matches found: " << cords.size() << std::endl;

    }

}
