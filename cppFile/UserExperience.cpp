// UserExperience.cpp

#include "../headerFile/UserExperience.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <regex>

#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

UserExperience::UserExperience(const char symbol) : decoratorSymbol(symbol) {
    // Initialize common error messages
    errorMessages.push_back("Invalid input. Please try again.");
    errorMessages.push_back("Input is out of range. Please enter a valid option.");
}

void UserExperience::displayLine(int length) {
    cout << setfill(decoratorSymbol) << setw(length) << decoratorSymbol << endl;
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



bool UserExperience::isValidPassportNumber(const std::string& passportNumber) {
    // Regular expression for validating a Vietnamese passport number
    // One uppercase letter followed by 7 digits
    const std::regex pattern(R"([A-Z]\d{7})");
    return std::regex_match(passportNumber, pattern);
}

bool UserExperience::isValidEmail(const std::string& email) {
    // Regular expression for validating an Email
    const std::regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    return std::regex_match(email, pattern);
}

bool UserExperience::isValidIdentityNumber(const std::string& idNumber) {
    std::regex pattern("^(001|079)[0-3]([0-9]{2})[0-9]{6}$");
    return std::regex_match(idNumber, pattern);

    // Regex pattern explanation:
    // ^                   : Start of the string
    // (001|079)           : Province code for Hanoi (001) or Ho Chi Minh City (079)
    // [0-3]               : Gender and century code (0,1 for 20th century, 2,3 for 21st century)
    // (                   : Start of year group
    //   ([0-9]{2})        : Any two digits for year
    // )
    // [0-9]{6}            : Six digits for the random part
    // $                   : End of the string
    //Reference: https://thuvienphapluat.vn/banan/tin-tuc/quy-dinh-ve-so-id-quoc-gia-the-nao-so-id-quoc-gia-viet-nam-la-gi-9266
    // https://nhankiet.vn/vi/w2787/Ma-tinhthanh-pho-cua-so-can-cuoc-cong-dan-CCCD.html
}

bool UserExperience::isValidCreditCard(const std::string& cardNumber, const std::string& cvv, const std::string& expiryDate) {
    // Regex patterns
    std::regex cardPattern("^(4[0-9]{15}|5[1-5][0-9]{14})$");
    std::regex cvvPattern("^[0-9]{3}$");
    std::regex expiryPattern("^(0[1-9]|1[0-2])/[0-9]{2}$");

    // Check card number format
    if (!std::regex_match(cardNumber, cardPattern)) return false;
    // Check CVV
    if (!std::regex_match(cvv, cvvPattern)) return false;
    // Check expiry date format and validity
    if (!std::regex_match(expiryDate, expiryPattern)) return false;

    // Parse expiry date
    int month = std::stoi(expiryDate.substr(0, 2));
    int year = std::stoi(expiryDate.substr(3, 2)) + 2000;

    // Get current date
    std::time_t t = std::time(nullptr);
    std::tm now_tm;

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&now_tm, &t);
#else
    localtime_r(&t, &now_tm);
#endif

    int currentYear = now_tm.tm_year + 1900;
    int currentMonth = now_tm.tm_mon + 1;

    // Check if card is expired
    if (year < currentYear || (year == currentYear && month < currentMonth)) return false;
    return true;



    //References:
    //Stack Overflow - Regex credit card number tests
    // https ://stackoverflow.com/questions/9315647/regex-credit-card-number-tests

    //Regular - Expressions.info - Finding or Verifying Credit Card Numbers
    //    https ://www.regular-expressions.info/creditcard.html

    //Stack Overflow - Get the Credit Card Type based on Number
    //    https ://stackoverflow.com/questions/9467896/get-the-credit-card-type-based-on-number

    //Salesforce Trailblazer Community - Need to validate a proper credit card number
    //    https ://trailhead.salesforce.com/trailblazer-community/feed/0D54S00000A7qWOSAZ
}

string UserExperience::getPasswordInput() {
    std::string password;
#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
#else
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::getline(std::cin, password);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    return password;
}


