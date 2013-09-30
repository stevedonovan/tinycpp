#include <iostream>
#include <string>
#include <list>
using namespace std;

int main()
{
    list<string> ls;
    string s = "hello";
    ls.append(" world");
    cout << ls << endl;
    return 0;
}
