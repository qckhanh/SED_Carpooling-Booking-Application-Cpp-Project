// UserExperience.cpp

#include "../headerFile/UserExperience.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

UserExperience::UserExperience(const char symbol) : decoratorSymbol(symbol) {
    // Initialize common error messages
    errorMessages.push_back("Invalid input. Please try again.");
    errorMessages.push_back("Input is out of range. Please enter a valid option.");
}

void UserExperience::displayLine(int length) {
    cout << setfill(decoratorSymbol) << setw(length) << decoratorSymbol << endl;
}

void UserExperience::displayHeader(const std::string& title) {
    int width = title.length() + 20; // Dynamically set width based on title length
    displayLine(width);
    cout << setfill(' ') << setw((width + title.length()) / 2) << title << endl;
    displayLine(width);
}

void UserExperience::handleError(const std::string& errorMessage) {
    string response;
    while (true) {
        cout << errorMessage << endl;
        cout << "Do you want to continue? (y/n): ";
        cin >> response;
        if (response == "y" || response == "Y") {
            break; // Continue
        }
        else if (response == "n" || response == "N") {
            cout << "Exiting..." << endl;
            break; // Exit loop and handle accordingly
        }
        else {
            cout << errorMessages[0] << endl; // Invalid input for continue question
        }
    }
}

int UserExperience::validateInput(int min, int max) {
    int option;
    while (true) {
        cout << "Enter a valid option (" << min << "-" << max << "): ";
        cin >> option;

        // Validate the input
        if (cin.fail() || option < min || option > max) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            handleError(errorMessages[1]);
        }
        else {
            return option; // Valid input
        }
    }
}

bool UserExperience::confirmMessage(const std::string& message) {
    int ans;
    while (true) {
        cout << message << endl;
        cout << "1. Yes | 0. No ? ";
        cin >> ans;
        if (ans == 1) {
            return true;
        }
        else if (ans == 0) {
            return false;
        }
        else {
            cout << "Invalid option. Please enter 1 for Yes or 0 for No." << endl;
        }
    }
}

void UserExperience::printHeader(const std::string& title) {
    int width = 45; // Total width of the header, including borders
    int titleLength = static_cast<int>(title.length());
    int leftPadding = (width - titleLength) / 2;
    int rightPadding = width - titleLength - leftPadding;

    // Top border
    std::string topBorder(width, '=');
    std::cout << topBorder << std::endl;

    // Title centered
    std::string centeredTitle = std::string(leftPadding, ' ') + title + std::string(rightPadding, ' ');
    std::cout << centeredTitle << std::endl;

    // Bottom border
    std::cout << topBorder << std::endl;
}

void UserExperience::printOption(int option, const std::string& description) {
    cout << "| " << setw(2) << right << option << " | " << setw(30) << left << description << " |" << endl;
}
