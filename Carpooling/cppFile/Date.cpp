#include "../headerFile/Date.h"
#include <sstream>  // Include for std::ostringstream
#include <iomanip>
#include<iostream>
#include<string>
using namespace std;
// Constructor implementation
Date::Date(int hour, int minute, int second, int day, int month, int year)
    : hour(hour), minute(minute), second(second), day(day), month(month), year(year) {}

// Getter implementations
int Date::getHour() const { return hour; }
int Date::getMinute() const { return minute; }
int Date::getSecond() const { return second; }
int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

// Setter implementations
void Date::setHour(int hour) { this->hour = hour; }
void Date::setMinute(int minute) { this->minute = minute; }
void Date::setSecond(int second) { this->second = second; }
void Date::setDay(int day) { this->day = day; }
void Date::setMonth(int month) { this->month = month; }
void Date::setYear(int year) { this->year = year; }

//method
void Date::toString() {
    cout << ((hour == -1) ? 0 : hour) << ":"
        << ((minute == -1) ? 0 : hour) << ":"
        << ((second == -1) ? 0 : hour) << ":, "
        << ((day == -1) ? 0 : hour) << " - "
        << ((month == -1) ? 0 : hour) << " - "
        << ((year == -1) ? 0 : hour);
}


