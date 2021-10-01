#include "../Interfaces/Date.hpp"

using namespace std;

Date::Date(string input_month, int input_day, int input_year) {

    month = input_month;
    day = input_day;
    year = input_year;
}

string Date::getMonth() { return month; }
int Date::getDay() { return day; }
int Date::getYear() { return year; }