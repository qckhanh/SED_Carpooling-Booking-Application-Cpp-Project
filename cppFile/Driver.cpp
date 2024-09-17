#include "../headerFile/Driver.h"
#include "../headerFile/Trip.h"
#include "../headerFile/UserExperience.h"
#include <iostream>
#include <utility>

using namespace std;

// Constructor and Destructor
Driver::Driver() {
}
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
// Setter methods
void Driver::addVehicle(Vehicle* vehicle) {
    driverVehicles.push_back(vehicle);
}
void Driver::addRunningCarpool(Trip* trip) {
    carpools.push_back(trip);
}

// Member functions
void Driver::changeStatusOfPassengerInTrip(Trip* trip, int passengerIndex, int value) {
    trip->changeStatusPassenger(passengerIndex, value);
}
void Driver::viewVehicle(UserExperience& ux) const {
    int index = 1;
    for (const auto& vehicle : driverVehicles) {
        cout << "Index: " << index << "| Plate: " << vehicle->getPlateNumber()<< endl;
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
