#include <iostream>

using namespace std;

long long int lottery_probability(long long int lottery, long long int drawn)
{
    long long int l = 1;
    long long int d = 1;
    long long int m = 1;

    for (long long int i = 1; i <= lottery ; ++i)
    {
        l = l * i;
    }
    for (long long int i = drawn; i >= 1; i--)
    {
        d = d * i;
    }
    for (long long int i = (lottery - drawn); i >= 1; i--)
    {
        m = m * i;
    }

    return l/(m*d);
}

bool input_check(long long int lottery, long long int drawn)
{
    if (lottery < 0 or drawn < 0)
    {
        cout << "The number of balls must be a positive number.";
        return false;
    }

    else if (drawn > lottery)
    {
        cout << "The maximum number of drawn balls is the total amount of balls.";
        return false;
    }

    return true;

}
int main()
{
    long int lottery;
    long int drawn;
    cout << "Enter the total number of lottery balls: ";
    cin >> lottery;
    cout << "Enter the number of drawn balls: " ;
    cin >> drawn;

    if (input_check(lottery, drawn))
    {
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/"
             << lottery_probability(lottery, drawn) << endl;

    }

}
