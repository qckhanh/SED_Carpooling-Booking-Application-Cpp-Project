#pragma once

const int DEFAULT = -1;

class Date {
private:
    int hour;
    int minute;
    int second;
    int day;
    int month;
    int year;

public:
    // Constructor
    Date(int hour = DEFAULT, int minute = DEFAULT, int second = DEFAULT,
         int day = DEFAULT, int month = DEFAULT, int year = DEFAULT);

    // Getters
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Setters
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    //methods
};
