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
        cin.clear();
        return input;
    }

    // Read input for other types
    template <typename T>
    typename std::enable_if<!std::is_same<T, std::string>::value, T>::type
        readInput() {
        T input;
        std::cin >> input;
        cin.clear();
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
    void printCarShape();

    // Input validation methods
    bool isValidEmail(const std::string& email);
    bool isValidPassportNumber(const std::string& passportNumber);
    bool isValidIdentityNumber(const std::string& idNumber);
    bool isValidCardNumber(string cardNumber);
    bool isValidPassword(const std::string& password);
    bool isValidPhoneNumber(const std::string& phoneNumber);
    bool isValidPlateNumber(const std::string& plateNumber);
    bool isValidRatingScore(int score);
    bool isValidLocation(const std::string& location);
    bool isValidOption(int x, int mn, int mx);
    bool isValidOption(string s, int mn, int mx);
    bool isValidRange(float x);
    // Other input method

    // Various input validation checks
    bool isValidUsername(const std::string& username);
    bool isValidName(const std::string& name);
    bool isValidSeatNumber(int seats);
    bool isValidVehicleModel(const std::string& model);
    bool isValidColor(const std::string& color);
    bool isValidRating(int rating);
    bool isValidCVV(const int& cvv);
    string getPasswordInput();

    // Example validation functions
    bool isValidDate(int day, int month, int year);
    bool isLeapYear(int year);
    bool isValidDateTrip(const Date& tripDate);
    string ReferenceIDGenerator(Date d1);
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
                    std::cout << " >>> [System]: Invalid option. See \"6. How to Use\" for instructions & policies and try again! \n";
                }
            }
            catch (std::ios::failure&) {
                std::cout << " >>> [System]:  Please enter a numeric value\n";
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
                    std::cout << " >>> [System]: Invalid option. See \"6. How to Use\" for instructions & policies and try again! \n";
                }
            }
            catch (std::ios::failure&) {
                std::cout << " >>> [System]:  Please enter a numeric value\n";
                // Clear the error state and ignore invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        return input;
    }

};


