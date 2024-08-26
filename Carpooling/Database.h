#pragma once
#include<vector>
#include<iostream>
#include "../headerFile/Passenger.h"
#include "../headerFile/Admin.h"
#include "../headerFile/Driver.h"
#include "../headerFile/Vehicle.h"
#include "../headerFile/Trip.h"
#include "fstream"
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Database {
private:
    std::vector<Passenger> passengers;
    std::vector<Driver> drivers;
    std::vector<Admin> admins;
    std::vector<Vehicle> vehicles;
    std::vector<Trip> trips;
    std::vector<Feedback> feedbacks;

public:
    // Constructor
    Database();

    // Getters
    std::vector<Passenger>& getPassengers();
    std::vector<Driver>& getDrivers();
    std::vector<Admin>& getAdmins();
    std::vector<Vehicle>& getVehicles();
    std::vector<Trip>& getTrips();
    std::vector<Feedback>& getFeedbacks(); // New getter for Feedbacks

    // Setters
    void setPassengers(const std::vector<Passenger>& newPassengers);
    void setDrivers(const std::vector<Driver>& newDrivers);
    void setAdmins(const std::vector<Admin>& newAdmins);
    void setVehicles(const std::vector<Vehicle>& newVehicles);
    void setTrips(const std::vector<Trip>& newTrips);
    void setFeedbacks(const std::vector<Feedback>& newFeedbacks); // New setter for Feedbacks

    // CRUD operations for Passengers
    void addPassenger(const Passenger& passenger);
    Passenger* getPassengerByIndex(int index);
    bool updatePassenger(int index, const Passenger& updatedPassenger);
    bool deletePassenger(int index);

    // CRUD operations for Drivers
    void addDriver(const Driver& driver);
    Driver* getDriverByIndex(int index);
    bool updateDriver(int index, const Driver& updatedDriver);
    bool deleteDriver(int index);

    // CRUD operations for Admins
    void addAdmin(const Admin& admin);
    Admin* getAdminByIndex(int index);
    bool updateAdmin(int index, const Admin& updatedAdmin);
    bool deleteAdmin(int index);

    // CRUD operations for Vehicles
    void addVehicle(const Vehicle& vehicle);
    Vehicle* getVehicleByIndex(int index);
    bool updateVehicle(int index, const Vehicle& updatedVehicle);
    bool deleteVehicle(int index);

    // CRUD operations for Trips
    void addTrip(const Trip& trip);
    Trip* getTripByIndex(int index);
    bool updateTrip(int index, const Trip& updatedTrip);
    bool deleteTrip(int index);

    // CRUD operations for Feedbacks
    void addFeedback(const Feedback& feedback);
    Feedback* getFeedbackByIndex(int index);
    bool updateFeedback(int index, const Feedback& updatedFeedback);
    bool deleteFeedback(int index);

    //methods
    void loadDriver();
    void loadVehicles();
    void loadTrips();
    void loadPassenger();
};