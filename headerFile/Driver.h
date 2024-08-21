#pragma once
#include "Vehicle.h"
#include <vector>
// #include "Vehicle.h"
// #include "Trip.h"

class Trip;
class Vehicle;

using namespace std;
class Driver {
    private:
        double driverRateScore;
        std::vector<Vehicle> driverVehicles;
        std::vector<Trip> carpoolList;
        std::vector<Trip> requests;
    public:
        //Constructor
        Driver();

        //Destrctor
        ~Driver();

        //Getter methods
        double getDriverRateScore() const;
        const std::vector<Vehicle>& getDriverVehicles() const;
        const std::vector<Trip>& getCarpoolList() const;
        const std::vector<Trip>& getRequests() const;

        //Setter methods
        void setDriverRateScore(const double& driverRateScore);
        void setDriverVehicles(const vector<Vehicle>& driverVehicles);
        void setCarpoolList(const vector<Trip>& carpoolList);
        void setRequests(const vector<Trip>& requests);

        // Member functions
        void manageRequest();
        void createCarpool();
        void viewCarpool();
        void deleteCarpool();
        void updateCarpool();
};
