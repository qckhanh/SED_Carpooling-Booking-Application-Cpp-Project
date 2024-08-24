#include "../headerFile/User.h"
#include <sstream>  // Include for std::ostringstream
#include <iostream> // Include for std::cout

// Constructor
User::User() : creditPoint(0.0f), isVerified(false) {}

// Destructor
User::~User() {}

// Getters
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFullName() const { return fullName; }
Date User::getDOB() const { return DOB; }
std::string User::getPhoneNumber() const { return phoneNumber; }
std::string User::getAddress() const { return address; }
std::string User::getEmail() const { return email; }
std::string User::getIdType() const { return idType; }
std::string User::getIdNumber() const { return idNumber; }
float User::getCreditPoint() const { return creditPoint; }
bool User::getIsVerified() const { return isVerified; }
BankAccount User::getBankAccount() const { return bankAccount; }
IdentityCard User::getCard() const { return card; }

// Setters
void User::setUsername(const std::string& username) { this->username = username; }
void User::setPassword(const std::string& password) { this->password = password; }
void User::setFullName(const std::string& fullName) { this->fullName = fullName; }
void User::setDOB(const Date& DOB) { this->DOB = DOB; }
void User::setPhoneNumber(const std::string& phoneNumber) { this->phoneNumber = phoneNumber; }
void User::setAddress(const std::string& address) { this->address = address; }
void User::setEmail(const std::string& email) { this->email = email; }
void User::setIdType(const std::string& idType) { this->idType = idType; }
void User::setIdNumber(const std::string& idNumber) { this->idNumber = idNumber; }
void User::setCreditPoint(float creditPoint) { this->creditPoint = creditPoint; }
void User::setIsVerified(bool isVerified) { this->isVerified = isVerified; }
void User::setBankAccount(const BankAccount& bankAccount) { this->bankAccount = bankAccount; }
void User::setCard(const IdentityCard& card) { this->card = card; }

// Member functions
void User::search() {
    // Implementation goes here
}

void User::rating() {
    // Implementation goes here
}

void User::verifyAccount() {
    // Implementation goes here
}

void User::manageInfo() {
    // Implementation goes here
}

