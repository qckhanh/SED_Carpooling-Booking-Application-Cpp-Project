#include "../headerFile/Driver.h"
#include <vector>

//Constructor
Driver::Driver() : driverRateScore(0.0f) {}

//Destructor
Driver::~Driver() {}

//Getter methods
double Driver::getDriverRateScore() const { return driverRateScore; }
//const std::vector<Vehicle>& Driver::getDriverVehicles() const { return driverVehicles; }
//const std::vector<Trip>& Driver::getCarpoolList() const { return carpoolList }
//const std::vector<Trip>& Driver::getRequests() const { return requests; }

//Setter methoods
void Driver::setDriverRateScore(const double& driverRateScore) { this->driverRateScore = driverRateScore; }
//void Driver::setDriverVehicles(const vector<Vehicle>& driverVehicles) { this->driverVehicles = driverVehicles; }
//void Driver::setCarpoolList(const vector<Trip>& carpoolList) { this->carpoolList = carpoolList; }
//void Driver::setRequests(const vector<Trip>& requests) { this-> requests = requests; }

//Member functions

void Driver::manageRequest() {
    //Implementation
}

void Driver::createCarpool() {
    //Implementation
}

void Driver::viewCarpool() {
    //Implementation
}

void Driver::deleteCarpool() {
    //Implementation
}

void Driver::updateCarpool() {
    //Implementation
}
