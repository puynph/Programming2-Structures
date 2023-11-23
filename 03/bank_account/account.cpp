#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner),
    has_credit_(has_credit),
    balance_(),
    credit_limit_()
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int limit)
{
    if(!has_credit_)
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;

    }
    else
    {
        credit_limit_ = limit;
    }
}

void Account::save_money(int money)
{
    balance_ += money;
}

void Account::take_money(int money)
{
    if(balance_ < money && !has_credit_)
    {
        std::cout << "Cannot take money: balance underflow" << std::endl;
    }

    else if(balance_ - money < -credit_limit_)
    {
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
    }

    else
    {

        balance_ -= money;
        std::cout << money << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;

    }
}

void Account::transfer_to(Account &other_account, int money)
{
    if(balance_ < money && !has_credit_)
    {
        std::cout << "Cannot take money: balance underflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }

    else if(balance_ - money < -credit_limit_)
    {
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }

    else
    {
        other_account.save_money(money);
        balance_ -= money;
        std::cout << money << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
    }

}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

int Account::balance()
{
    return balance_;
}
