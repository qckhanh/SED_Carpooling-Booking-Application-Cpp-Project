#pragma once
#include "Vehicle.h"
#include <vector>
#include "../Ra"
// #include "Vehicle.h"
// #include "Trip.h"
#include "User.h"
class Trip;
class Vehicle;
#include<iostream>
using namespace std;
class Driver: public User{
    private:
        double driverRateScore;
        std::vector<Vehicle> driverVehicles;
        std::vector<Trip*> running_carpool;
    public:
        //Constructor
        Driver();
        
        //Destrctor
        ~Driver();

        //Getter methods
        double getDriverRateScore() const;
        const std::vector<Vehicle>& getDriverVehicles() const;
        std::vector<Trip*>& getRunningCarpool() ;

        //Setter methods
        void setDriverRateScore(const double& driverRateScore);
        void setDriverVehicles(const vector<Vehicle>& driverVehicles);
        void addActiveTrip( Trip *trip);

        // Member functions
        void changeStatusOfPassengerInTrip(int tripIndex, int passengerIndex, int value);
        void viewCarpool();
        void deleteCarpool(int index);
        void updateCarpool();
};
