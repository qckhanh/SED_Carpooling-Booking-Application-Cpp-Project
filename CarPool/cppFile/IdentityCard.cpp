
#include "../headerFile/IdentityCard.h"

// Constructor
IdentityCard::IdentityCard() 
    : name(""), gender(false), nationality(""), placeOfOrigin(""), placeOfResidence("") {}

// Destructor
IdentityCard::~IdentityCard() {}

// Setter methods
void IdentityCard::setName(const std::string &name) { this->name = name; }
void IdentityCard::setDOB(const Date &DOB) { this->DOB = DOB; }
void IdentityCard::setGender(bool gender) { this->gender = gender; }
void IdentityCard::setNationality(const std::string &nationality) { this->nationality = nationality; }
void IdentityCard::setPlaceOfOrigin(const std::string &placeOfOrigin) { this->placeOfOrigin = placeOfOrigin; }
void IdentityCard::setPlaceOfResidence(const std::string &placeOfResidence) { this->placeOfResidence = placeOfResidence; }
void IdentityCard::setExpireDate(const Date &expireDate) { this->expireDate = expireDate; }

// Getter methods
std::string IdentityCard::getName() const { return name; }
Date IdentityCard::getDOB() const { return DOB; }
bool IdentityCard::getGender() const { return gender; }
std::string IdentityCard::getNationality() const { return nationality; }
std::string IdentityCard::getPlaceOfOrigin() const { return placeOfOrigin; }
std::string IdentityCard::getPlaceOfResidence() const { return placeOfResidence; }
Date IdentityCard::getExpireDate() const { return expireDate; }
