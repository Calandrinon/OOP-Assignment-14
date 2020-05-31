#include "validator.h"
#include "myexceptions.h"
#include <vector>
#include <QDebug>
using namespace std;

void Validator::validate_time_of_creation(string time_of_creation) {
    /**
     *
     * Validates a date given as a string
     * The date should look like this: 01-01-2000
     *								  day-month-year
     * Input:
     * 		- time_of_creation: a date given as a string
     **/
    vector<string> tokens = StringFunctions::tokenize(time_of_creation, '-');
    string date = tokens[0] + " " + tokens[1] + " " + tokens[2];
    qDebug() << QString::fromStdString(date);
    if (tokens.size() != 3) {
        CommandFormatException command_format_exception("Incorrect time of creation format!\n");
        throw command_format_exception;
    }

    int month = stoi(tokens[1]);
    int day = stoi(tokens[0]);
    stoi(tokens[2]); //the year

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        CommandFormatException command_format_exception("Incorrect date!\n");
        throw command_format_exception;
    }

    //Conversion is not necessary but for validating the date(reassuring the fact that
    //the date is a series of numbers) it is useful because it throws an invalid_argument
    //exception in case the date string is just formed of letters.
}


void Validator::validate_times_accessed(string times_accessed) {
    /**
     * Validates the times_accessed parameter
     *
     * Input:
     * 		- times_accessed: a string
     **/
    stoi(times_accessed);
}
