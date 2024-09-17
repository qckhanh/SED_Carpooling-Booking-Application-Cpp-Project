#pragma once
#include <vector>

#include "Vehicle.h"
#include "UserExperience.h"
#include "Feedback.h"
#include "User.h"

class Trip;
class Vehicle;

class Driver : public User {
private:
    std::vector<Vehicle*> driverVehicles;
    std::vector<Trip*> carpools;

public:
    // Constructor and Destructor
    Driver();
    ~Driver();

    // Getter methods
    const std::vector<Vehicle*>& getDriverVehicles() const;
    std::vector<Trip*>& getCarpool();
    // Setter methods
    void addVehicle(Vehicle* vehicle);
    void addRunningCarpool(Trip* trip);
    void changeStatusOfPassengerInTrip(Trip* trip, int passengerIndex, int value);
    vector<Trip*> getCarpoolWithStatus(int statusValue);
    void viewVehicle(UserExperience& ux) const;
    void changeStatusCarpool(int index, int value);
};
