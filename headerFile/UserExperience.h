// UserExperience.h
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <regex>
#include <vector>
#include <functional>
#include "BankAccount.h"
#include <ctime>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;
#define MAX_CARNUMBER_LENGTH 16
#define VISA_NUMBER_START "4614"
#define MASTERCARD_NUMBER_START "5565"
#define IDENTITY_NUMBER_START "0012"

class UserExperience {
private:
    char decoratorSymbol;           // Either '=' or '-'
    std::vector<std::string> errorMessages; // List of common error messages

    void displayLine(int length);   // Helper function to print a line of decoratorSymbol
    template <typename T>
    typename std::enable_if<std::is_same<T, std::string>::value, T>::type
        readInput() {
        T input;
        std::getline(std::cin >> std::ws, input);
        return input;
    }

    // Read input for other types
    template <typename T>
    typename std::enable_if<!std::is_same<T, std::string>::value, T>::type
        readInput() {
        T input;
        std::cin >> input;
        return input;
    }
public:
    // Constructor
    UserExperience();

    // Setters
    void setDecoratorSymbol(const char symbol) { this->decoratorSymbol = symbol; }
    // Decoration
    bool confirmMessage(const std::string& message);
    void printHeader(const std::string& title);
    void printHeaderNoTopBorder(const std::string& title);
    void printRightCenteredText(const std::string& text);
    void printCenteredText(const std::string& text);
    void printOption(int option, const std::string& description);
    void printError(const std::string& text);
    void printInstruction(const std::string& text);
    void printCarShape();

    // Error handling
    void handleError(const std::string& errorMessage);
    int validateInput(int min, int max);

    // Input validation methods
    bool isValidEmail(const std::string& email);
    bool isValidPassportNumber(const std::string& passportNumber);
    bool isValidIdentityNumber(const std::string& idNumber);
    bool isValidCardNumber(string cardNumber);
    bool isValidPassword(const std::string& password);
    bool isValidPhoneNumber(const std::string& phoneNumber);
    bool isValidDate(const std::string& date);
    bool isValidTime(const std::string& time);
    bool isValidPlateNumber(const std::string& plateNumber);
    bool hasSufficientCredit(int userCredit, int requiredCredit);
    bool isValidRatingScore(int score);
    bool isValidLocation(const std::string& location);
    bool areSeatAvailable(int availableSeat, int requestedSeat);
    bool isValidOption(int x, int mn, int mx);
    bool isValidRange(float x);
    // Other input method

    // Various input validation checks
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
    bool isValidCVV(const int& cvv);
    bool isNumber(string& str);
    string getPasswordInput();


    // Example validation functions
    bool validateInt(const int& input);

    bool validateString(const std::string& input);

    bool isValidDate(int day, int month, int year);

    bool isLeapYear(int year);
    bool isValidDateTrip(const Date& tripDate);

    template <typename T>
    T getValidInput(const std::string& prompt, bool (UserExperience::* validate)(const T&)) {
        T input;
        while (true) {
            std::cout << prompt;
            try {
                input = readInput<T>(); // Attempt to read the input

                // Check if the input is valid using the passed validation function
                if ((this->*validate)(input)) {
                    break;  // If valid, exit the loop and return the value
                }
                else {
                    std::cout << " >>> [Error] Invalid input. Please try again.\n";
                }
            }
            catch (std::ios::failure&) {
                std::cout << " >>> [Error] Invalid input type. Please enter the correct type.\n";
                // Clear the error state and ignore the invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        return input;
    }

    template <typename T, typename... Args>
    T getValidInput(const std::string& prompt, bool (UserExperience::* validate)(T, Args...), Args... args) {
        T input;
        while (true) {
            std::cout << prompt;
            try {
                input = readInput<T>(); // Attempt to read the input

                // Call the validation function with input and additional arguments
                if ((this->*validate)(input, args...)) {
                    break;  // If valid, exit the loop and return the input
                }
                else {
                    std::cout << " >>> [Error]: Invalid input. Please try again.\n";
                }
            }
            catch (std::ios::failure&) {
                std::cout << " >>> [Error]: Please enter a valid input type\n";
                // Clear the error state and ignore invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        return input;
    }

};


