#include "../headerFile/Driver.h"
#include "../headerFile/Trip.h"
#include <iostream>
#include <utility>

using namespace std;

// Constructor
Driver::Driver() {
}

// Destructor
Driver::~Driver() {
    // Clean up allocated memory for vehicles and trips
    for (auto vehicle : driverVehicles) {
        delete vehicle;
    }
    for (auto trip : carpools) {
        delete trip;
    }
}

// Getter methods
const std::vector<Vehicle*>& Driver::getDriverVehicles() const {
    return driverVehicles;
}

std::vector<Trip*>& Driver::getCarpool() {
    return carpools;
}

Vehicle* Driver::getVehicleFromIndex(int index) {
    return driverVehicles[index];
}

Trip* Driver::getCarpoolFromIndex(int index, int statusValue) {
    int indexFind = 0;
    for (int i = 0; i < (int)carpools.size(); i++) {
        if (carpools[i]->getStatus() == statusValue) {
            if (indexFind == index) return carpools[i];
            indexFind++;
        }
    }
    return nullptr;
}

// Setter methods
void Driver::addVehicle(Vehicle* vehicle) {
    driverVehicles.push_back(vehicle);
}

void Driver::addActiveTrip(Trip* trip) {
    setRunningCarpool(trip);
}

void Driver::setRunningCarpool(Trip* trip) {
    carpools.push_back(trip);
}

// Member functions
void Driver::changeStatusOfPassengerInTrip(int tripIndex, int passengerIndex, int value) {
    carpools[tripIndex]->changeStatusPassenger(passengerIndex, value);
}

void Driver::viewVehicle() const {
    for (const auto& vehicle : driverVehicles) {
        vehicle->toString();
    }
}

void Driver::viewCarpool(int statusValue) const {
    int index = 0;
    for (const auto& currentCarpool : carpools) {

        if (currentCarpool->getStatus() == statusValue) {
            cout << index <<": " <<  currentCarpool->toString() << endl;
            index++;
        }
    }
}



void Driver::changeStatusCarpool(int index, int value) {
    
    int FindIndex = 0;
    for(int i = 0; i < (int)carpools.size(); i++){
        if (carpools[i]->getStatus() == 1) {
            if (FindIndex == index) {
                carpools[i]->setStatus(value);
                return;
            }
            FindIndex++;

        }
    }
    cout << "FAILED";
}

void Driver::updateCarpool() {
    // Implementation
}
