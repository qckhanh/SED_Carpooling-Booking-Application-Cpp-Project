#pragma once
#include <string>
#include "UserExperience.h"

using namespace std;
class Vehicle {
private:
    std::string owner_username;
    std::string model;
    std::string color;
    std::string plateNumber;
    int totalSeat;
    int status;

public:
    //constructor:
    Vehicle();
    Vehicle(string owner_username, string model, string color, string plateNumber, int totalSeat);
    
    //destructor:
    ~Vehicle();
    
    // Setters
    void setOwner_username(const std::string& username);
    void setModel(const std::string &model);
    void setColor(const std::string &color);
    void setPlateNumber(const std::string &plateNumber);
    void setTotalSeat(int totalSeat);
    void setStatus(int status);

    // Getters
    std::string getOwner_username() const;
    std::string getModel() const;
    std::string getColor() const;
    std::string getPlateNumber() const;
    int getTotalSeat() const;
    int getStatus() const;
    //methods
    void showInformation(UserExperience& ux) const;
};
