#include <iostream>

using namespace std;

int main()
{
    /// declare array
    int a[] = {0, 1, 2, 3, 4, 5};
    /// declare pointer, *ptr save memory address
    int *ptr = a;
    /// & address of operator (obtain address)
    cout << &a[2] << endl;
    cout << ptr+2 << endl;

    /// get the value of pointer ptr+2
    cout << *(ptr+2) << endl;
    /// output the value of second element of array
    cout << a[2];
    return 0;
}
