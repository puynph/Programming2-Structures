#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string infileName = "";
    string outfileName = "";
    cout << "Input file: ";
    getline(cin, infileName);
    cout << "Output file: ";
    getline(cin, outfileName);


    ifstream infile_object(infileName);
    if ( not infile_object )
    {
        cout << "Error! The file " << infileName << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    else
    {
        ofstream outfile_object(outfileName);
        int i = 1;
        string line;
        while (getline(infile_object, line))
        {
            outfile_object << (i++) << " " << line << "\n";
        }
        infile_object.close();
        outfile_object.close();
    }

}
