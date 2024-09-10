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

    bool isValidPassword(const std::string& password);
    bool isValidPhoneNumber(const std::string& phoneNumber);
    bool isValidDate(const std::string& date);
    bool isValidTime(const std::string& time);
    bool isValidPlateNumber(const std::string &plateNumber);
    bool hasSufficientCredit(int userCredit, int requiredCredit);
    bool isValidRatingScore(int score);
    bool isValidLocation(const std::string& location);
    bool areSeatAvailable(int availableSeat, int requestedSeat);
    bool canCancelBooking(const std::string &bookingStatus);
    int getValidIntInput(const std::string& prompt, int min, int max);
    double getValidDoubleInput(const std::string& prompt, double min, double max);
    bool isValidUsername(const std::string& username);
    bool isCommonPassword(const std::string& password);
    bool isStrongPassword(const std::string& password);
    bool isValidName(const std::string& name);
    bool isValidAge(int age);
    bool isValidSeatNumber(int seats);
    bool isValidVehicleModel(const std::string& model);
    bool isValidColor(const std::string& color);
    bool isValidDuration(int minutes);
    bool isValidRating(int rating);
};
