// UserExperience.h
#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define MAX_CARNUMBER_LENGTH 16
#define VISA_NUMBER_START "4614"
#define MASTERCARD_NUMBER_START "5565"
#define IDENTITY_NUMBER_START "0012"

class UserExperience {
private:
    char decoratorSymbol;          // Either '=' or '-'
    std::vector<std::string> errorMessages; // List of common error messages

    void displayLine(int length);  // Helper function to print a line of decoratorSymbol

public:
    UserExperience(const char symbol = '=');
    void setDecoratorSymbol(const char symbol) { this->decoratorSymbol = symbol; }
    //decoration
    bool confirmMessage(const std::string& message);
    void printHeader(const std::string& title);
    void printOption(int option, const std::string& description);

    //error handling
    void handleError(const std::string& errorMessage);
    int validateInput(int min, int max);
    bool isValidEmail(const std::string& email);
    bool isValidPassportNumber(const std::string& passportNumber);
    bool isValidIdentityNumber(const std::string& idNumber);
    bool isValidCreditCard(const std::string& cardNumber, const std::string& cvv, const std::string& expiryDate);
};
