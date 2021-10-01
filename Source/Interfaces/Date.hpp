#ifndef DATE_HPP
#define DATE_HPP

#include <string>

class Date {

public:

    Date(std::string input_month = "January", int input_day = 1, int input_year = 0);
    std::string getMonth();
    int getDay();
    int getYear();

private:

    std::string month;
    int day;
    int year;
};

#endif