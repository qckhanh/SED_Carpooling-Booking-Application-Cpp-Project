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
    std::vector<Passenger*>& getPassengers();   
    std::vector<Driver*>& getDrivers();         
    std::vector<Admin*>& getAdmins();           
    std::vector<Vehicle*>& getVehicles();       
    std::vector<Trip*>& getTrips();             
    std::vector<Feedback*>& getFeedbacks();     

    // Setters
    void setPassengers(const std::vector<Passenger*>& newPassengers);   
    void setDrivers(const std::vector<Driver*>& newDrivers);             
    void setAdmins(const std::vector<Admin*>& newAdmins);                
    void setVehicles(const std::vector<Vehicle*>& newVehicles);          
    void setTrips(const std::vector<Trip*>& newTrips);                   
    void setFeedbacks(const std::vector<Feedback*>& newFeedbacks);       

    //methods to add and load data
    void addPassenger(Passenger* passenger);  
    void addDriver(Driver* driver);  
    void addAdmin(Admin* admin);  
    void addVehicle(Vehicle* vehicle);  
    void addTrip(Trip* trip);  
    void addFeedback(Feedback* feedback);  
    void loadDriver();
    void loadVehicles();
    void loadTrips();
    void loadAdmins();
    void loadPassenger();
    void loadFeedback();

    void saveDrivers();
    void saveVehicles();
    void savePassengers();
    void saveTrips();
    void saveFeedback();
    void saveDataToFile();
};
