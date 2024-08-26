#pragma once
#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <vector>
#include "Driver.h" // Assuming Driver and Passenger classes are defined in separate header files
#include "Passenger.h"
#include "Vehicle.h"
#include "Date.h"
#include <utility>
#include <sstream> // Include for stringstream

class Passenger;

class Trip {
private:
    std::string driver_username;
    std::string vehicle_plate;
    Date start;
    Date end;
    std::string startLocation;
    std::string endLocation;
    int availableSeat;
    std::vector<std::pair<std::string, int>> passengers; // Stores <passenger_username, status>
    std::string referenceID;

public:
    // Constructor
    Trip();

    // Destructor
    ~Trip();

    // Setters
    void setDriver(const std::string& driver_username);
    void setVehicle(const std::string& vehicle_plate);
    void setStart(const Date& start);
    void setEnd(const Date& end);
    void setStartLocation(const std::string& startLocation);
    void setEndLocation(const std::string& endLocation);
    void setAvailableSeat(int availableSeat);
    void setPassengers(const std::vector<std::pair<std::string, int>>& passengers);
    void setReferenceID(const std::string& referenceID);

    // New Setter for Specific Passenger Status
    void setPassengerStatus(const std::string& passenger_username, int status);

    // Getters
    std::string getDriver() const;
    std::string getVehicle() const;
    Date getStart() const;
    Date getEnd() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;
    int getAvailableSeat() const;
    std::vector<std::pair<std::string, int>>& getPassengers();
    std::string getReferenceID() const;

    // New Getter for Specific Passenger Status
    int getPassengerStatus(const std::string& passenger_username) const;

    // Methods
    void addPassengerToTrip(const std::string& passenger_username, int status);
    void changeStatusPassenger(int index, int value);
    std::string toString();

};

#endif // TRIP_H
