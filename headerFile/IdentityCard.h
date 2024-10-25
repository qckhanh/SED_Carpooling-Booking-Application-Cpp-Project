#pragma once
#include <string>
#include "Date.h" 

class IdentityCard {
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
    IdentityCard();

    //destructor:
    ~IdentityCard();

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

