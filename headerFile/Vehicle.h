#pragma once

#include <string>
using namespace std;
class Vehicle {
private:
    std::string model;
    std::string color;
    std::string plateNumber;
    int totalSeat;

public:
    //constructor:
    Vehicle(): totalSeat(0) {}
    Vehicle(string model, string color, string plateNumber, int totalSeat);
    
    //destructor:
    ~Vehicle();
    
    // Setters
    void setModel(const std::string &model);
    void setColor(const std::string &color);
    void setPlateNumber(const std::string &plateNumber);
    void setTotalSeat(int totalSeat);

    // Getters
    std::string getModel() const;
    std::string getColor() const;
    std::string getPlateNumber() const;
    int getTotalSeat() const;
};
