#pragma once
#include "Vehicle.h"
#include <vector>
#include "../Carpooling/Feedback.h"
// #include "Vehicle.h"
// #include "Trip.h"
#include "User.h"
class Trip;
class Vehicle;
#include<iostream>
using namespace std;
class Driver: public User{
    private:
        std::vector<Vehicle> driverVehicles;
        std::vector<Trip> running_carpool;
    public:
        //Constructor
        Driver();
        
        //Destrctor
        ~Driver();

        //Getter methods
        const std::vector<Vehicle>& getDriverVehicles() const;
        std::vector<Trip>& getRunningCarpool();
        Vehicle& getVehicleFromIndex(int index);

        //Setter methods
        void setDriverVehicles(const Vehicle& vehicles);
        void addActiveTrip( Trip trip);
        void setRunningCarpool(Trip trip);

        // Member functions
        void changeStatusOfPassengerInTrip(int tripIndex, int passengerIndex, int value);
        void viewCarpool();
        void viewVehicle();
        void deleteCarpool(int index);
        void updateCarpool();
};
