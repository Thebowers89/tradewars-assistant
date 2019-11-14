#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace Utils {
    string ignoreCase(string str);
    string vectorToString(const vector<int> &v);
    vector<string> splitString(string str, char delim);
    int splitLength(string str, char delim);
    bool doesExist(string file);
}

#endif