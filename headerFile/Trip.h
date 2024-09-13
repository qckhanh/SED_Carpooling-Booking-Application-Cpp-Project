#pragma once
#include <string>
#include <vector>
#include <utility>
#include <sstream> 
#include "Driver.h" 
#include "Passenger.h"
#include "Vehicle.h"
#include "Date.h"
#include "UserExperience.h"

class Passenger;

class Trip {
private:    
    int status;  // 0: cancel, 1: active 2. finished
    std::string driver_username;
    std::string vehicle_plate;
    Date start;
    Date end;
    std::string startLocation;
    std::string endLocation;
    int availableSeat;
    int minRate;
    float cost;
    std::vector<std::pair<std::string, int>> passengers; // Stores <passenger_username, status>
    std::string referenceID;
    Driver* currDriver;
    Vehicle* currVehicle;
    float totalCredit;

public:
    // Constructor
    Trip();

    // Destructor
    ~Trip();

    // Setters
    void setStatus(const int status);
    void setDriver(const std::string& driver_username);
    void setVehicle(const std::string& vehicle_plate);
    void setStart(const Date& start);
    void setEnd(const Date& end);
    void setStartLocation(const std::string& startLocation);
    void setEndLocation(const std::string& endLocation);
    void setAvailableSeat(int availableSeat);
    void setPassengers(const std::vector<std::pair<std::string, int>>& passengers);
    void setReferenceID(const std::string& referenceID);
    void setMinRate(const int minRate);
    void setCost(const float cost);
    void setDriverP(Driver* driver);
    void setVehicleP(Vehicle* vehicle);
    void setPassengerStatus(const std::string& passenger_username, int status);
    

    // Setter for totalCredit
    void setTotalCredit(float credit);

    // Getters
    int getStatus() const;
    std::string getDriver() const;
    double getDriverRating(Driver *driver);
    std::string getVehicle() const;
    Date getStart() const;
    Date getEnd() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;
    int getAvailableSeat() const;
    std::vector<std::pair<std::string, int>>& getPassengers();
    std::string getReferenceID() const;
    int getMinRate() const;
    float getCost() const;
    // New Getter for Specific Passenger Status
    int getPassengerStatus(const std::string& passenger_username) const;
    Driver* getDriverP();
    Vehicle* getVehicleP();
    float getTotalCredit();

    // Methods
    void addPassengerToTrip(const std::string& passenger_username, int status);
    void removePassenger(const std::string& passenger_username, int status);
    void changeStatusPassenger(int index, int value);
    std::string toString();
    void showInformation(UserExperience& ux); //isguest
    
    

};


