#include "smartPtr.hpp"
#include <iostream>
#include <string>
using namespace experis;
using namespace std;

int main()
{
    SmartPtr<int> smartPtr(new int);
    int& a = *smartPtr;
    a = 5;
    cout << *smartPtr << '\n';
    cout << (smartPtr == 0) << '\n';

    SmartPtr<string> smartStr(new string);
    cout << smartStr->c_str() << '\n';

    return 0;
}