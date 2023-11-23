/* University 2
 *
 * Desc:
 *   The program consists of classes Account, Course, University, Cli,
 * and Utils module as well as the main program module. The program makes
 * use of pointers. The class University has 2 maps data structure, of which
 * payloads are instances of class Account and Course. Likewise, the class
 * Account also has an attribute which are instances of class Course,
 * containing all courses the account has signed up for. By doing this,
 * dynamic memory management is implemented in this course program.
 *   The main program prints the promt and expects to receive input until
 * QUIT command is given by the user. User can use HELP command if needs
 * any guidance.
 *   Error is given in certain situations, which are more specific in each
 * class header file. Different commands belong to different classes, whose
 * functions are also explained more explicitly in header files.
 *
 * Name: Uyen Phan
 * Student number: 151372454
 * UserID: cpuyph ( Necessary due to gitlab folder naming. )
 * E-Mail: uyen.phan@tuni.fi
 *
 * */
//#include "utils.hh"
#include "cli.hh"
#include "university.hh"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}

