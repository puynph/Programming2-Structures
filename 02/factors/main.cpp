#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x;
    cout << "Enter a positive number: ";
    cin >> x;
    if (x <= 0)
    {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }
    int a = sqrt(x);
    while ( x % a != 0)
    {
        a--;
    }
    cout << x << " = " << a << " * " << x/a << endl;
}
