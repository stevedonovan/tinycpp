#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

string trim(string s) {
    int i=0, idx = 0;
    for (auto ch: s) {
        if (ch != ' ') {
            idx = i;
            break;
        }
        ++i;
    }
    return s.substr(idx);
}

int main(int argc, char **argv)
{
    list<string> ls;
    ifstream inf("hello.cpp");
    string line;
    while (getline(inf,line)) {
        ls.push_back(trim(line));
    }
    ls.sort();
    auto i = 1;
    for (string s: ls) {
        cout << i << ' ' << s << endl;
        ++i;
    }
    return 0;
}
