#include "Utils.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

string Utils::ignoreCase(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = char(tolower(str[i]));
    }
    return str;
}

string Utils::vectorToString(const vector<int> &v) {
    string out = "";
    for (int i = 0; i < v.size(); i++) {
        out.append(to_string(v[i]) + ",");
    }
    out.pop_back();
    return out;
}

vector<string> Utils::splitString(string str, char delim) {
    vector<string> out;
    bool found = false;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delim) {
            found = true;
        }
    }
    if (!found) {
        out.push_back(str);
        return out;
    }
    int a = 0;
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delim) {
            string s = str.substr(a, i-a);
            out.push_back(s);
            count++;
            a = i+1;
        }
        if (i == str.length()-1) {
            out.push_back(str.substr(a, i));
        }
    }
    return out;
}

int Utils::splitLength(string str, char delim) {
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delim) {
            count++;
        }
    }
    return count+1;
}

bool Utils::doesExist(string file) {
    ifstream ifile(file);
    return (bool)ifile;
}