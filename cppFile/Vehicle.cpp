#include "../headerFile/Vehicle.h"

// Constructor
Vehicle::Vehicle() : model(""), color(""), plateNumber(""), totalSeat(0) {}

// Destructor
Vehicle::~Vehicle() {}

// Setter methods
void Vehicle::setModel(const std::string &model) { this->model = model; }
void Vehicle::setColor(const std::string &color) { this->color = color; }
void Vehicle::setPlateNumber(const std::string &plateNumber) { this->plateNumber = plateNumber; }
void Vehicle::setTotalSeat(int totalSeat) { this->totalSeat = totalSeat; }

// Getter methods
std::string Vehicle::getModel() const { return model; }
std::string Vehicle::getColor() const { return color; }
std::string Vehicle::getPlateNumber() const { return plateNumber; }
int Vehicle::getTotalSeat() const { return totalSeat; }
