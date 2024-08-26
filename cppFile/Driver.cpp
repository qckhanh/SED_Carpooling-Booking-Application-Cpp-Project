#include "../headerFile/Driver.h"
#include "../headerFile/Trip.h"
#include <vector>
#include<iostream>
#include<utility>
using namespace std;
//Constructor
Driver::Driver(){
    this->feedbacks.setOwner_username(this->username);
}

//Destructor
Driver::~Driver() {}

//Getter methods
const std::vector<Vehicle>& Driver::getDriverVehicles() const { return driverVehicles; }
 std::vector<Trip>& Driver::getRunningCarpool()  { return running_carpool; }
 Vehicle& Driver::getVehicleFromIndex(int index) {
     return driverVehicles[index];
 }
//Setter methoods
void Driver::setDriverVehicles(const Vehicle& vehicles) { driverVehicles.push_back(vehicles); }
void Driver::addActiveTrip(Trip trip) { 
    trip.setDriver(username);
    setRunningCarpool(trip);
}

void Driver::setRunningCarpool(Trip trip) {
    this->running_carpool.push_back(trip);
}
//Member functions

void Driver::changeStatusOfPassengerInTrip(int tripIndex, int passengerIndex, int value) {
    running_carpool[tripIndex].changeStatusPassenger(passengerIndex, value);
}

void Driver::viewVehicle() {
    for (auto& x : driverVehicles) x.toString();
}


void Driver::viewCarpool() {
    for ( auto currentCarpool : running_carpool) {
        cout << currentCarpool.toString() << endl;
    }
}

void Driver::deleteCarpool(int index) {
    running_carpool.erase(running_carpool.begin() + index);
}

void Driver::updateCarpool() {
    //Implementation
}
