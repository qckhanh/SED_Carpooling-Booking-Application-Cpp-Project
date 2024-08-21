#pragma once

#include <string>

class Vehicle {
private:
    std::string model;
    std::string color;
    std::string plateNumber;
    int totalSeat;

public:
    //constructor:
    Vehicle();
    
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
