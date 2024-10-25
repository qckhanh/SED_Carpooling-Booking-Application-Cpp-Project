// UserExperience.cpp

#include "../headerFile/UserExperience.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include<math.h>
#include <regex>
#include <iostream>
#include <string>
#include <ctime>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

UserExperience::UserExperience() {
    std::cin.exceptions(std::ios::failbit | std::ios::badbit);
    decoratorSymbol = '=';
}

void UserExperience::displayLine(int length) {
    cout << setfill(decoratorSymbol) << setw(length) << decoratorSymbol << endl;
}

bool UserExperience::confirmMessage(const std::string& message) {
    int ans;
    while (true) {
        cout << message << endl;
        ans = getValidInput<int>("1. Yes | 0. No ? ", &UserExperience::isValidOption, 0, 1);
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

void UserExperience::printHeaderNoTopBorder(const std::string& title){
    int width = 45; // Total width of the header, including borders
    int titleLength = static_cast<int>(title.length());
    int leftPadding = (width - titleLength) / 2;
    int rightPadding = width - titleLength - leftPadding;

    // Top border
    std::string topBorder(width, ' ');
    std::cout << topBorder << std::endl;

    // Title centered
    std::string centeredTitle = std::string(leftPadding, '_') + title + std::string(rightPadding, '_');
    std::cout << centeredTitle << std::endl;

    // Bottom border
    std::cout << topBorder << std::endl;
}

void UserExperience::printRightCenteredText(const std::string& text) {
    int width = 45; // Total width of the output
    int titleLength = static_cast<int>(text.length());
    int leftPadding = width - titleLength;

    // Right-aligned text
    std::string rightAlignedText = std::string(leftPadding, ' ') + text;
    std::cout << rightAlignedText << endl;
}

void UserExperience::printCenteredText(const std::string& text){
    int width = 45; // Total width of the header, including borders
    int titleLength = static_cast<int>(text.length());
    int leftPadding = (width - titleLength) / 2;
    int rightPadding = width - titleLength - leftPadding;

    // Top border
    std::string topBorder(width, ' ');
    std::cout << topBorder << std::endl;

    // Title centered
    std::string centeredTitle = std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
    std::cout << centeredTitle << std::endl;

    // Bottom border
    std::cout << topBorder << std::endl;
}

void UserExperience::printOption(int option, const std::string& description) {
    cout << "| " << setw(2) << right << ((option == -1) ? "" : to_string(option)) << " | " << setw(30) << left << description << " |" << endl;
}

void UserExperience::printCarShape(){
    const int totalWidth = 45; 
    const std::string car[] = {
        "      _______             ",
        "     //  ||\\ \\             ",
        "____//___||_\\ \\___          ",
        ")   __          __  \\     ",
        "|__/  \\________/  \\___|       ",
        "___\\_ /________\\_ /_____     "
    };

    int carWidth = 0;
    for (const auto& line : car) {
        carWidth = std::max(carWidth, static_cast<int>(line.length()));
    }

    int padding = (totalWidth - carWidth) / 2;

    for (const auto& line : car) {
        std::cout << std::string(padding, ' ') << line << std::endl;
    }
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
    return regex_match(idNumber, pattern);
    
}

bool UserExperience::isValidCardNumber(string cardNumber){

    std::regex cardPattern("^(4[0-9]{15}|5[1-5][0-9]{14})$");
    if (!std::regex_match(cardNumber, cardPattern)) return false;
    return true;
}

bool UserExperience::isValidPassword(const std::string& password) {
    // Password must be at least 8 characters long and contain at least one uppercase letter,
    // one lowercase letter, one number, and one special character
    std::regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    return std::regex_match(password, pattern);
}

bool UserExperience::isValidPhoneNumber(const std::string& phoneNumber) {
    // Assuming Vietnamese phone numbers: 10 digits starting with 0
    std::regex pattern("^0\\d{9}$");
    return std::regex_match(phoneNumber, pattern);
}

bool UserExperience::isValidPlateNumber(const std::string& plateNumber) {
    // Assuming a simple format for Vietnamese license plates: 2 numbers, 1 letter, 5 numbers
    std::regex pattern("^\\d{2}[A-Z]\\d{5}$");
    return std::regex_match(plateNumber, pattern);
}

bool UserExperience::isValidRatingScore(int score) {
    return score >= 1 && score <= 5;
}

bool UserExperience::isValidLocation(const std::string& location) {
    string locationCop = location;
    locationCop.erase(remove(locationCop.begin(), locationCop.end(), ' '), locationCop.end());
    for (auto& it : locationCop) {
        it = tolower(it);
    }
    std::vector<std::string> validLocations = { "hanoi", "saigon", "hochiminh", "danang"};  // Add more as needed
    for (auto& it : validLocations) {
        if (locationCop.find(it) != string::npos) {
            return true;
            cout << locationCop << endl;
            cout << it << endl;
        }
    }
    return false;
}


bool UserExperience::isValidUsername(const std::string& username) {
    // Username should be 3-20 characters long and contain only letters, numbers, and underscores
    std::regex pattern("^[a-zA-Z0-9_]{3,20}$");

    return regex_match(username, pattern);
}

bool UserExperience::isValidName(const std::string& name) {
    // Check if name contains only letters and spaces
    return std::regex_match(name, std::regex("^[a-zA-Z ]+$"));
}

//bool UserExperience::isValidAge(int age) {
//    return age >= 18 && age <= 100;  // Adjust age range as needed
//}

bool UserExperience::isValidSeatNumber(int seats) {
    return seats > 0 && seats <= 8;  // Adjust max seats as needed
}

bool UserExperience::isValidVehicleModel(const std::string& model) {
    // Check if model contains only letters, numbers, and spaces
    return std::regex_match(model, std::regex("^[a-zA-Z0-9 ]+$"));
}

bool UserExperience::isValidColor(const std::string& color) {
    std::vector<std::string> validColors = { "Red", "red", "Blue", "blue", "Green", "green",  "White", "white", "Black", "black",  "Silver", "silver"};  
    return std::find(validColors.begin(), validColors.end(), color) != validColors.end();
}


bool UserExperience::isValidRating(int rating) {
    return rating >= 1 && rating <= 5;
}

string UserExperience::getPasswordInput() {
    string password;
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


bool UserExperience::isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) {
        return false;
    }

    // Check if month is valid
    if (month < 1 || month > 12) {
        return false;
    }

    // Check the number of days in each month
    const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Adjust for leap year
    int maxDays = daysInMonth[month];
    if (month == 2 && isLeapYear(year)) {
        maxDays = 29;
    }

    // Check if day is valid for the given month
    if (day < 1 || day > maxDays) {
        return false;
    }

    return true;
}

bool UserExperience::isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool UserExperience::isValidDateTrip(const Date& tripDate) {
    // Get current date and time
    std::time_t t = std::time(nullptr);
    std::tm now_tm;

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&now_tm, &t);
#else
    localtime_r(&t, &now_tm);
#endif

    // Array of current date/time components
    int currentComponents[] = {
        now_tm.tm_year + 1900, // Year
        now_tm.tm_mon + 1,     // Month
        now_tm.tm_mday,        // Day
        now_tm.tm_hour,        // Hour
        now_tm.tm_min,         // Minute
        now_tm.tm_sec          // Second
    };

    // Array of trip date/time components
    int tripComponents[] = {
        tripDate.getYear(),
        tripDate.getMonth(),
        tripDate.getDay(),
        tripDate.getHour(),
        tripDate.getMinute(),
        tripDate.getSecond()
    };

    // Iterate over the components
    for (int i = 0; i < 6; ++i) {
        if (tripComponents[i] == -1) {
            continue; // Skip if component is missing
        }
        if (tripComponents[i] > currentComponents[i]) {
            return true; // Trip date is in the future
        }
        if (tripComponents[i] < currentComponents[i]) {
            return false; // Trip date is in the past
        }
        // If equal, continue to the next component
    }

    return true;
}

bool UserExperience::isValidOption(int x, int mn, int mx) {
    return x >= mn && x <= mx;
}
bool UserExperience::isValidOption(string s, int mn, int mx) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    int x = stoi(s);
    return (x >= mn && x <= mx) && (floor(x) == x);
}
bool UserExperience::isValidRange(float x) {
    return x >= 0.0 && x <= INT_MAX * 1.0;
}

bool UserExperience::isValidCVV(const int& cvv) {
    return (cvv >= 100 && cvv <= 999);  // Example validation for a 3-digit CVV
}


string UserExperience::ReferenceIDGenerator(Date d1) {
    double total = 0;
    int key = (int)(rand() % (57 - 20 + 1)) + 20;    
    total += (double)d1.getHour() * pow(key, 1);
    total += (double)d1.getMinute() * pow(key, 2);
    total += (double)d1.getDay() * pow(key, 3);
    total += (double)d1.getMonth() *pow(key, 4);
    total += (double)d1.getYear() *pow(key, 5);
    string s = to_string((long long)total).substr(0, 5);
    return s;
    
}

