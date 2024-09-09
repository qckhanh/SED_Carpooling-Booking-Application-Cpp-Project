#include "../headerFile/Vehicle.h"
#include "../headerFile/UserExperience.h"
#include <iostream>
#include<iomanip>
// Constructor
Vehicle::Vehicle(string owner_username, string model, string color, string plateNumber, int totalSeat) : owner_username(owner_username), model(model), color(color), plateNumber(plateNumber), totalSeat(totalSeat) {
    this->status = 1;
}
Vehicle::Vehicle() {
    this->status = 1;
}

// Destructor
Vehicle::~Vehicle() {
}

// Setter methods
void Vehicle::setModel(const std::string &model) { this->model = model; }
void Vehicle::setColor(const std::string &color) { this->color = color; }
void Vehicle::setPlateNumber(const std::string &plateNumber) { this->plateNumber = plateNumber; }
void Vehicle::setTotalSeat(int totalSeat) { this->totalSeat = totalSeat; }
void Vehicle::setOwner_username(const std::string& username) { this->owner_username = username; }
void Vehicle::setStatus(int status) { this->status = status;  }
// Getter methods
std::string Vehicle::getModel() const { return model; }
std::string Vehicle::getColor() const { return color; }
std::string Vehicle::getPlateNumber() const { return plateNumber; }
int Vehicle::getTotalSeat() const { return totalSeat; }
std::string Vehicle::getOwner_username() const { return owner_username;  }
int Vehicle::getStatus() const{ return status; }
void Vehicle::showInformation(UserExperience& ux) const {
    ux.printHeader("VEHICLE INFORMATION");
    std::cout << std::left;
    std::cout << std::setw(18) << "Owner Username" << ": " << owner_username << std::endl;
    std::cout << std::setw(18) << "Model" << ": " << model << std::endl;
    std::cout << std::setw(18) << "Color" << ": " << color << std::endl;
    std::cout << std::setw(18) << "Plate Number" << ": " << plateNumber << std::endl;
    std::cout << std::setw(18) << "Total Seats" << ": " << totalSeat << std::endl;

}

