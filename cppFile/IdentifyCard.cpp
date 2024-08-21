#include "../headerFile/IdentityCard.h"

// Constructor
IdentifyCard::IdentifyCard()
    : name(""), gender(false), nationality(""), placeOfOrigin(""), placeOfResidence("") {}

// Destructor
IdentifyCard::~IdentifyCard() {}

// Setter methods
void IdentifyCard::setName(const std::string &name) { this->name = name; }
void IdentifyCard::setDOB(const Date &DOB) { this->DOB = DOB; }
void IdentifyCard::setGender(bool gender) { this->gender = gender; }
void IdentifyCard::setNationality(const std::string &nationality) { this->nationality = nationality; }
void IdentifyCard::setPlaceOfOrigin(const std::string &placeOfOrigin) { this->placeOfOrigin = placeOfOrigin; }
void IdentifyCard::setPlaceOfResidence(const std::string &placeOfResidence) { this->placeOfResidence = placeOfResidence; }
void IdentifyCard::setExpireDate(const Date &expireDate) { this->expireDate = expireDate; }

// Getter methods
std::string IdentifyCard::getName() const { return name; }
Date IdentifyCard::getDOB() const { return DOB; }
bool IdentifyCard::getGender() const { return gender; }
std::string IdentifyCard::getNationality() const { return nationality; }
std::string IdentifyCard::getPlaceOfOrigin() const { return placeOfOrigin; }
std::string IdentifyCard::getPlaceOfResidence() const { return placeOfResidence; }
Date IdentifyCard::getExpireDate() const { return expireDate; }
