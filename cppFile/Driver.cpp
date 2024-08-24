#include "../headerFile/Driver.h"
#include "../headerFile/Trip.h"
#include <vector>
#include<iostream>
#include<utility>
using namespace std;
//Constructor
Driver::Driver() : driverRateScore(0.0f) {}

//Destructor
Driver::~Driver() {}

//Getter methods
double Driver::getDriverRateScore() const { return driverRateScore; }
const std::vector<Vehicle>& Driver::getDriverVehicles() const { return driverVehicles; }
 std::vector<Trip*>& Driver::getRunningCarpool()  { return running_carpool; }

//Setter methoods
void Driver::setDriverRateScore(const double& driverRateScore) { this->driverRateScore = driverRateScore; }
void Driver::setDriverVehicles(const std::vector<Vehicle>& driverVehicles) { this->driverVehicles = driverVehicles; }

void Driver::addActiveTrip(Trip *trip) { 
    trip->setDriver(this);
    running_carpool.push_back(trip);
}

//Member functions

void Driver::changeStatusOfPassengerInTrip(int tripIndex, int passengerIndex, int value) {
    this->running_carpool[tripIndex]->changeStatusPassenger(passengerIndex, value);
}



void Driver::viewCarpool() {
    for (const auto& currentCarpool : running_carpool) {
        cout << currentCarpool->toString() << endl;
    }
}

void Driver::deleteCarpool(int index) {
    running_carpool.erase(running_carpool.begin() + index);
}

void Driver::updateCarpool() {
    //Implementation
}
