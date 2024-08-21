#pragma once
#ifndef IDENTIFYCARD_H
#define IDENTIFYCARD_H

#include <string>
#include "Date.h" // Assuming Date is defined in a separate header file

class IdentifyCard {
private:
    std::string name;
    Date DOB;
    bool gender;
    std::string nationality;
    std::string placeOfOrigin;
    std::string placeOfResidence;
    Date expireDate;

public:
    //constructor:
    IdentifyCard();

    //destructor:
    ~IdentifyCard();

    // Setters
    void setName(const std::string &name);
    void setDOB(const Date &DOB);
    void setGender(bool gender);
    void setNationality(const std::string &nationality);
    void setPlaceOfOrigin(const std::string &placeOfOrigin);
    void setPlaceOfResidence(const std::string &placeOfResidence);
    void setExpireDate(const Date &expireDate);

    // Getters
    std::string getName() const;
    Date getDOB() const;
    bool getGender() const;
    std::string getNationality() const;
    std::string getPlaceOfOrigin() const;
    std::string getPlaceOfResidence() const;
    Date getExpireDate() const;
};

#endif // IDENTIFYCARD_H
