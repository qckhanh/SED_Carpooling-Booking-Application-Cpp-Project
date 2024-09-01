#include "../headerFile/Vehicle.h"
#include <iostream>
// Constructor
Vehicle::Vehicle(string owner_username, string model, string color, string plateNumber, int totalSeat) : owner_username(owner_username), model(model), color(color), plateNumber(plateNumber), totalSeat(totalSeat) {}

// Destructor
Vehicle::~Vehicle() {}

// Setter methods
void Vehicle::setModel(const std::string &model) { this->model = model; }
void Vehicle::setColor(const std::string &color) { this->color = color; }
void Vehicle::setPlateNumber(const std::string &plateNumber) { this->plateNumber = plateNumber; }
void Vehicle::setTotalSeat(int totalSeat) { this->totalSeat = totalSeat; }
void Vehicle::setOwner_username(const std::string& username) { this->owner_username = username; }
// Getter methods
std::string Vehicle::getModel() const { return model; }
std::string Vehicle::getColor() const { return color; }
std::string Vehicle::getPlateNumber() const { return plateNumber; }
int Vehicle::getTotalSeat() const { return totalSeat; }
std::string Vehicle::getOwner_username() const { return owner_username;  }
void Vehicle::toString() const {
    std::cout << "Owner Username: " << owner_username << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "Plate Number: " << plateNumber << std::endl;
    std::cout << "Total Seats: " << totalSeat << std::endl;
}
