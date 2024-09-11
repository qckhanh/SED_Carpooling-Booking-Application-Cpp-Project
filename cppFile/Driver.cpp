#include "../headerFile/Driver.h"
#include "../headerFile/Trip.h"
#include "../headerFile/UserExperience.h"
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
    int indexFind = 1;
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
void Driver::changeStatusOfPassengerInTrip(Trip* trip, int passengerIndex, int value) {
    trip->changeStatusPassenger(passengerIndex, value);
}

void Driver::viewVehicle(UserExperience& ux) const {
    int index = 1;
    for (const auto& vehicle : driverVehicles) {
        cout << "Index: " << index << "Plate: " << vehicle->getPlateNumber()<< endl;
        vehicle->showInformation(ux);
        index++;
    }
}

vector<Trip*> Driver::getCarpoolWithStatus(int statusValue) {
    vector<Trip*> ans;
    for (auto& currentCarpool : carpools) {
        if (currentCarpool->getStatus() == statusValue) {
            ans.push_back(currentCarpool);
        }
    }
    return ans;
}
void Driver::viewCarpool(UserExperience& ux, int statusValue) {
    int index = 1;
    for (const auto& currentCarpool : carpools) {
        if (currentCarpool->getStatus() == statusValue) {
            cout << endl;
            cout << index << ": " << currentCarpool->getReferenceID() << ": " << endl;
            currentCarpool->showInformation(ux);
            index++;
        }
    }
}



void Driver::changeStatusCarpool(int index, int value) {
    
    int FindIndex = 1;
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
