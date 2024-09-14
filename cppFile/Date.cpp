#include "../headerFile/Date.h"
#include <sstream>  // Include for std::ostringstream
#include <iomanip>
#include<iostream>
#include<string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
// Constructor implementation
Date::Date(int hour, int minute, int second, int day, int month, int year)
    : hour(hour), minute(minute), second(second), day(day), month(month), year(year) {
}

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


//string Date::showInformation() {
    /*std::ostringstream oss;

    if (hour != -1) {
        oss << std::setw(2) << std::setfill('0') << hour << ":";
        oss << std::setw(2) << std::setfill('0') << (minute != -1 ? minute : 0);
    }

    if (day != -1 && month != -1 && year != -1) {
        if (hour != -1) {
            oss << " - ";
        }
        oss << std::setw(2) << std::setfill('0') << day << "/";
        oss << std::setw(2) << std::setfill('0') << month << "/";
        oss << year;
    }

    return oss.str();*/
//}

bool Date::operator>(const Date& other) const {
    if (compareValues(year, other.year) != 0) return compareValues(year, other.year) > 0;
    if (compareValues(month, other.month) != 0) return compareValues(month, other.month) > 0;
    if (compareValues(day, other.day) != 0) return compareValues(day, other.day) > 0;
    if (compareValues(hour, other.hour) != 0) return compareValues(hour, other.hour) > 0;
    if (compareValues(minute, other.minute) != 0) return compareValues(minute, other.minute) > 0;
    return compareValues(second, other.second) > 0;
}

bool Date::operator<(const Date& other) const {
    return other > *this;
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

bool Date::operator<=(const Date& other) const {
    return !(*this > other);
}

bool Date::operator==(const Date& other) const {
    return compareValues(year, other.year) == 0 &&
        compareValues(month, other.month) == 0 &&
        compareValues(day, other.day) == 0 &&
        compareValues(hour, other.hour) == 0 &&
        compareValues(minute, other.minute) == 0 &&
        compareValues(second, other.second) == 0;
}

// Helper function implementation
int Date::compareValues(int a, int b) {
    if (a == DEFAULT || b == DEFAULT) return 0;
    return (a > b) ? 1 : (a < b) ? -1 : 0;
}

std::string Date::toString() const {
    std::ostringstream oss;

    // Format time (hour:minute:second)
    if (hour != DEFAULT || minute != DEFAULT || second != DEFAULT) {
        if (hour != DEFAULT) {
            oss << std::setw(2) << std::setfill('0') << hour;
        }
        if (minute != DEFAULT) {
            oss << ":" << std::setw(2) << std::setfill('0') << minute;
        }
        if (second != DEFAULT) {
            oss << ":" << std::setw(2) << std::setfill('0') << second;
        }
        oss << " - "; // Add separator between time and date if time is present
    }

    // Format date (day/month/year)
    if (day != DEFAULT || month != DEFAULT || year != DEFAULT) {
        if (day != DEFAULT) {
            oss << std::setw(2) << std::setfill('0') << day;
        }
        if (month != DEFAULT) {
            oss << "/" << std::setw(2) << std::setfill('0') << month;
        }
        if (year != DEFAULT) {
            oss << "/" << year;
        }
    }

    return oss.str();
}


