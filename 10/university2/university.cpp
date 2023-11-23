#include "university.hh"
#include <iostream>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);
    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    std::map<int, Account*>::iterator iter = accounts_.find(account);
    if ( iter == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}

void University::sign_up(Params params)
{
    std::string course_code = params.at(0);
    int account_number = std::stoi(params.at(1));

    if ( courses_.find(course_code) == courses_.end() )
    {
        std::cout << CANT_FIND << course_code << std::endl;
        return;
    }
    if ( accounts_.find(account_number) == accounts_.end() )
    {
        std::cout << CANT_FIND << account_number << std::endl;
        return;
    }

    // If a student tries to sign up for a course for the second time
    if ( accounts_.at(account_number)->is_current_course(course_code))
    {
        std::cout << STUDENT_EXISTS << std::endl;
    }
    else if (accounts_.at(account_number)->is_graduated())
    {
        std::cout << ALREADY_GRADUATED << std::endl;
    }
    else if ( accounts_.at(account_number)->is_completed_course(course_code))
    {
        std::cout << STUDENT_COMPLETED << std::endl;
    }
    else
    {
        accounts_.at(account_number)->sign_up_course(courses_.at(course_code));
    }
}

void University::complete(Params params)
{
    std::string course_code = params.at(0);
    int account_number = std::stoi(params.at(1));
    if ( courses_.find(course_code) == courses_.end() )
    {
        std::cout << CANT_FIND << course_code << std::endl;
        return;
    }

    if ( accounts_.find(account_number) == accounts_.end() )
    {
        std::cout << CANT_FIND << account_number << std::endl;
        return;
    }
    accounts_.at(account_number)->complete_course(courses_.at(course_code));
}

void University::print_signups(Params params)
{
    std::string course_code = params.at(0);
    if ( courses_.find(course_code) == courses_.end() )
    {
        std::cout << CANT_FIND << course_code << std::endl;
        return;
    }
    // going through all students in Unversity and selecting
    // those who have signed up for the course
    for ( auto account : accounts_ )
    {
        if ( account.second->is_signed_up_course(course_code))
        {
            account.second->print();
        }
    }
}

void University::print_completed(Params params)
{
    int account_number = std::stoi(params.at(0));

    if ( accounts_.find(account_number) == accounts_.end() )
    {
        std::cout << CANT_FIND << account_number << std::endl;
        return;
    }
    accounts_.at(account_number)->print_completed();
}

void University::print_study_state(Params params)
{
    int account_number = std::stoi(params.at(0));

    if ( accounts_.find(account_number) == accounts_.end() )
    {
        std::cout << CANT_FIND << account_number << std::endl;
        return;
    }
    accounts_.at(account_number)->print_study_state();
}

void University::graduate(Params params)
{
    int account_number = std::stoi(params.at(0));

    if ( accounts_.find(account_number) == accounts_.end() )
    {
        std::cout << CANT_FIND << account_number << std::endl;
        return;
    }
    accounts_.at(account_number)->graduate();
}
