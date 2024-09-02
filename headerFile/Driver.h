#pragma once
#include <vector>

#include "Vehicle.h"
#include "Feedback.h"
#include "User.h"

class Trip;
class Vehicle;

class Driver : public User {
private:
    std::vector<Vehicle*> driverVehicles;
    std::vector<Trip*> carpools;

public:
    // Constructor
    Driver();

    // Destructor
    ~Driver();

    // Getter methods
    const std::vector<Vehicle*>& getDriverVehicles() const;
    std::vector<Trip*>& getCarpool();
    Vehicle* getVehicleFromIndex(int index);
    Trip* getCarpoolFromIndex(int index, int statusValue);
    // Setter methods
    void addVehicle(Vehicle* vehicle);
    void addActiveTrip(Trip* trip);
    void setRunningCarpool(Trip* trip);

    // Member functions
    void changeStatusOfPassengerInTrip(int tripIndex, int passengerIndex, int value);
    void viewCarpool(int statusValue) const;
    void viewVehicle() const;
    void changeStatusCarpool(int index, int value);
    void updateCarpool();
};
