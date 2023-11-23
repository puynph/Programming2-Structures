#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>
#include <algorithm>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number),
    courses_(),
    currently_enrolled_(),
    total_credits_(),
    graduated_(false)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}
// This class doesn't need a destructor since only one Account
// object is created and detroyed in class University
Account::~Account()
{
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

bool Account::is_graduated()
{
    return graduated_;
}

void Account::sign_up_course( Course* &code )
{
    courses_.push_back(code);
    currently_enrolled_.push_back(true);
    std::cout << SIGNED_UP << std::endl;
}

void Account::complete_course( Course* &code )
{
    // find course code from attribute courses_
    auto it = std::find(courses_.begin(), courses_.end(), code);
    // if code is found
    if (it != courses_.end())
    {
        // This distance between iterator and the beginning of vector courses_
        // is returned as an integer
        // used to access the corresponding element in the currently_enrolled_
        if (currently_enrolled_[it - courses_.begin()])
        {
            currently_enrolled_[it - courses_.begin()] = false;
            // new credits for completed course
            total_credits_ += code->get_credits();
            std::cout << COMPLETED << std::endl;
        }
        else // if course is already completed
        {
            std::cout << NO_SIGNUPS << std::endl;
        }
    }
    else // if course hasn't been signed up
    {
        std::cout << NO_SIGNUPS << std::endl;
    }
}

bool Account::is_current_course( const std::string &code )
{
    for (vector_size_type i = 0; i < courses_.size(); i++)
    {
        // if course has been signed up and not completed
        if (courses_[i]->get_code() == code && currently_enrolled_[i])
        {
            return true;
        }
    }
    return false;
}

bool Account::is_completed_course( const std::string &code )
{
    for (vector_size_type i = 0; i < courses_.size(); i++)
    {
        // if course is signed up and already completed
        if (courses_[i]->get_code() == code && !currently_enrolled_[i])
        {
            return true;
        }
    }
    return false;
}

bool Account::is_signed_up_course(const std::string &code)
{
    for (vector_size_type i = 0; i < courses_.size(); i++)
    {
        if (courses_[i]->get_code() == code)
        {
            return true;
        }
    }
    return false;
}

void Account::print_study_state()
{
    std::cout << "Current: " << std::endl;
    for (vector_size_type i = 0; i < courses_.size(); i++)
    {
        if (currently_enrolled_[i])
        {
            courses_[i]->print_info(true);
        }
    }
    std::cout << "Completed: " << std::endl;
    for (vector_size_type i = 0; i < courses_.size(); i++)
    {
        if (!currently_enrolled_[i])
        {
            courses_[i]->print_info(true);
        }
    }
    std::cout << "Total credits: " << total_credits_ << std::endl;
}

void Account::print_completed()
{
    for (vector_size_type i = 0; i < courses_.size(); i++)
    {
        if (!currently_enrolled_[i])
        {
            courses_[i]->print_info(true);
        }
    }
    std::cout << "Total credits: " << total_credits_ << std::endl;
}

void Account::graduate()
{
    graduated_ = true;
    for (vector_size_type i = 0; i < courses_.size(); i++)
    {
        if (currently_enrolled_[i])
        {
        currently_enrolled_[i] = false;
        // get credits for completed course
        total_credits_ += courses_[i]->get_credits();
        }
    }
    std::cout << GRADUATED << std::endl;
}
