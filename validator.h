#pragma once
#include <iostream>
#include "string_functions.h"
using namespace std;

class Validator {
    public:
        void validate_time_of_creation(string time_of_creation);
        void validate_times_accessed(string times_accessed);
};