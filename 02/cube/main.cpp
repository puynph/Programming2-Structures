#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    int cube = n*n*n;

    if (cube/n/n == n)
    {
        cout << "The cube of " << n << " is "<< cube << "." <<endl;
    }
    else
    {
        cout << "Error! The cube of " << n << " is not " << cube << "." << endl;
    }

    return 0;
}
