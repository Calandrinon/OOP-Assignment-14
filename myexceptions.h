#pragma once
#include <exception>
#include <string>
using namespace std;

class CommandFormatException: public exception {
    public:
        string message;

    public:
        CommandFormatException(string message) {
            this->message = message; 
        }
};


class RepositoryException: public exception {
    public:
        string message;

    public:
        RepositoryException(string message) {
            this->message = message;
        }
}; 


class IndexError: public exception {
    public:
        string message;

    public:
        IndexError(string message) {
            this->message = message;
        }
};
