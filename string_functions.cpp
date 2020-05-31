#include "string_functions.h"
#include <sstream>
using namespace std;

vector<string> StringFunctions::tokenize(std::string line, char delimiter) {
    /**
     *
     * Splits a string into tokens by using a delimiter and returns them in a std::vector
     *
     * Input:
     * 		- line: string
     * 		- delimiter: character
     *
     * Output:
     * 		- tokens: std::vector
     **/
    vector<string> tokens;

    stringstream stream(line);
    string token;

    while(getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


std::string StringFunctions::strip(std::string str) {
    /**
     *
     * Removes all trailing whitespaces and newline characters.
     *
     * Input:
     * 		- str: the string
     *
     * Output:
     * 		- str: the string after its trailing whitespaces and \n characters have been removed.
     * **/
    while (str[0] == ' ' || str[0] == '\n')
        str.erase(0,1);

    while (str[str.size()-1] == ' ' || str[str.size()-1] == '\n')
        str.erase(str.size()-1,1);

    return str;
}
