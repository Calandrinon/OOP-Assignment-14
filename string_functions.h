#pragma once
#include <iostream>
#include <vector>
using namespace std;

class StringFunctions {
    public:
        static vector<string> tokenize(string line, char delimiter);
        static string strip(string str);
};
