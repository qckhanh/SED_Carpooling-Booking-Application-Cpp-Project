// UserExperience.h

#ifndef USER_EXPERIENCE_H
#define USER_EXPERIENCE_H

#include <iostream>
#include <vector>
#include <string>

class UserExperience {
private:
    char decoratorSymbol;          // Either '=' or '-'
    std::vector<std::string> errorMessages; // List of common error messages

    void displayLine(int length);  // Helper function to print a line of decoratorSymbol

public:
    // Constructor
    UserExperience(const char symbol = '=');
    void setDecoratorSymbol(const char symbol) { this->decoratorSymbol = symbol;  }

    // Display a centered header
    void displayHeader(const std::string& title);

    // Handle errors with a retry mechanism
    void handleError(const std::string& errorMessage);

    // Validate input within a specified range
    int validateInput(int min, int max);

    // Confirm a message with Yes/No option
    bool confirmMessage(const std::string& message);

    // Print a decorative header
    void printHeader(const std::string& title);

    // Print an option in a formatted way
    void printOption(int option, const std::string& description);
};

#endif
