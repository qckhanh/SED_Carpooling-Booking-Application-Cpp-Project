#pragma once
#include <vector>
#include <iostream>
#include "fstream"
#include <sstream>
#include <fstream>

#include "Passenger.h"
#include "Admin.h"
#include "Driver.h"
#include "Vehicle.h"
#include "Trip.h"

using namespace std;

class Database {
private:
    std::vector<Passenger*> passengers;
    std::vector<Driver*> drivers;
    std::vector<Admin*> admins;
    std::vector<Vehicle*> vehicles;
    std::vector<Trip*> trips;
    std::vector<Feedback*> feedbacks;

public:
    // Constructor
    Database();

    // Getters
    std::vector<Passenger*>& getPassengers();  // Return reference to vector of pointers
    std::vector<Driver*>& getDrivers();        // Return reference to vector of pointers
    std::vector<Admin*>& getAdmins();          // Return reference to vector of pointers
    std::vector<Vehicle*>& getVehicles();      // Return reference to vector of pointers
    std::vector<Trip*>& getTrips();            // Return reference to vector of pointers
    std::vector<Feedback*>& getFeedbacks();    // Return reference to vector of pointers

    // Setters
    void setPassengers(const std::vector<Passenger*>& newPassengers);  // Accept vector of pointers
    void setDrivers(const std::vector<Driver*>& newDrivers);            // Accept vector of pointers
    void setAdmins(const std::vector<Admin*>& newAdmins);               // Accept vector of pointers
    void setVehicles(const std::vector<Vehicle*>& newVehicles);         // Accept vector of pointers
    void setTrips(const std::vector<Trip*>& newTrips);                  // Accept vector of pointers
    void setFeedbacks(const std::vector<Feedback*>& newFeedbacks);      // Accept vector of pointers

    // CRUD operations for Passengers
    void addPassenger(Passenger* passenger);  // Use pointer
    Passenger* getPassengerByIndex(int index);
    bool updatePassenger(int index, Passenger* updatedPassenger);  // Use pointer
    bool deletePassenger(int index);

    // CRUD operations for Drivers
    void addDriver(Driver* driver);  // Use pointer
    Driver* getDriverByIndex(int index);
    bool updateDriver(int index, Driver* updatedDriver);  // Use pointer
    bool deleteDriver(int index);

    // CRUD operations for Admins
    void addAdmin(Admin* admin);  // Use pointer
    Admin* getAdminByIndex(int index);
    bool updateAdmin(int index, Admin* updatedAdmin);  // Use pointer
    bool deleteAdmin(int index);

    // CRUD operations for Vehicles
    void addVehicle(Vehicle* vehicle);  // Use pointer
    Vehicle* getVehicleByIndex(int index);
    bool updateVehicle(int index, Vehicle* updatedVehicle);  // Use pointer
    bool deleteVehicle(int index);

    // CRUD operations for Trips
    void addTrip(Trip* trip);  // Use pointer
    Trip* getTripByIndex(int index, int statusValue);
    bool updateTrip(int index, Trip* updatedTrip);  // Use pointer
    bool deleteTrip(Trip* trip);

    // CRUD operations for Feedbacks
    void addFeedback(Feedback* feedback);  // Use pointer
    Feedback* getFeedbackByIndex(int index);
    bool updateFeedback(int index, Feedback* updatedFeedback);  // Use pointer
    bool deleteFeedback(int index);

    // methods to load data from files
    void loadDriver();
    void loadVehicles();
    void loadTrips();
    void loadPassenger();
    void loadFeedback();

    void saveDrivers();
    void saveVehicles();
    void savePassengers();
    void saveTrips();
    void saveFeedback();
    void saveDataToFile();
    

    
};
