#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

typedef list<string> Strings;

string trim(string s) {
    int idx = s.find_first_not_of(" \t");
    if (idx == string::npos) {
        return s;
    } else {
        return s.substr(idx);
    }
}

int main(int argc, char **argv)
{
    Strings ls;
    ifstream inf("hello.cpp");
    string line;
    while (getline(inf,line)) {
        ls.push_back(trim(line));
    }
    ls.sort();
    int i = 1;
    for (Strings::iterator li = ls.begin(); li != ls.end(); li++) {
        if (*li != "") {
            cout << i << ' ' << *li << endl;
            ++i;
        }
    }
    return 0;
}
