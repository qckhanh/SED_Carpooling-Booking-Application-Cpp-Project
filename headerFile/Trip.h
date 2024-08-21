#pragma once
#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <vector>
#include "Driver.h" // Assuming Driver and Passenger classes are defined in separate header files
#include "Passenger.h"
#include "Vehicle.h"
#include "Date.h"

class Trip {
private:
    Driver driver;
    std::vector<Passenger> passenger;
    Vehicle vehicle;
    Date start;
    Date end;
    std::string startLocation;
    std::string endLocation;
    int availableSeat;
    std::vector<std::pair<int, int>> passengers;
    std::string referenceID;

public:
    //constructor
    Trip();

    //destructor
    ~Trip();
    
    // Setters
    void setDriver(const Driver &driver);
    void setPassenger(const std::vector<Passenger> &passenger);
    void setVehicle(const Vehicle &vehicle);
    void setStart(const Date &start);
    void setEnd(const Date &end);
    void setStartLocation(const std::string &startLocation);
    void setEndLocation(const std::string &endLocation);
    void setAvailableSeat(int availableSeat);
    void setPassengers(const std::vector<std::pair<int, int>> &passengers);
    void setReferenceID(const std::string &referenceID);

    // Getters
    Driver getDriver() const;
    std::vector<Passenger> getPassenger() const;
    Vehicle getVehicle() const;
    Date getStart() const;
    Date getEnd() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;
    int getAvailableSeat() const;
    std::vector<std::pair<int, int>> getPassengers() const;
    std::string getReferenceID() const;
};

#endif // TRIP_H
