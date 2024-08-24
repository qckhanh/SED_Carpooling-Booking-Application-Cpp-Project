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

class Database
{
private:
    vector<Passenger> passengers;
    vector<Driver> drivers;
    vector<Admin> admins;
    vector<Vehicle> vehicles;
    vector<Trip> trips;

public:
    // Constructor
    Database();
  
    // Getters
    vector<Passenger>& getPassengers();
    vector<Driver>& getDrivers();
    vector<Admin>& getAdmins();
    vector<Vehicle>& getVehicles();
    vector<Trip>& getTrips();

    // Setters
    void setPassengers(const vector<Passenger>& newPassengers);
    void setDrivers(const vector<Driver>& newDrivers);
    void setAdmins(const vector<Admin>& newAdmins);
    void setVehicles(const vector<Vehicle>& newVehicles);
    void setTrips(const vector<Trip>& newTrips);

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

    //methods
    void loadData();
};