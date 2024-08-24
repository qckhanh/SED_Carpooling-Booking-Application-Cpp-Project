#pragma once
#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <vector>
#include "Driver.h" // Assuming Driver and Passenger classes are defined in separate header files
#include "Passenger.h"
#include "Vehicle.h"
#include "Date.h"
#include<utility>
#include <sstream> // Include for stringstream

class Passenger;

class Trip {
private:
    Driver *driver;
    Vehicle *vehicle;
    Date start;
    Date end;
    std::string startLocation;
    std::string endLocation;
    int availableSeat;
    std::vector<std::pair<Passenger, int>> passengers;
    std::string referenceID;

public:
    //constructor
    Trip();

    //destructor
    ~Trip();

    // Setters
    void setDriver( Driver *driver);
    void setVehicle( Vehicle* vehicle);
    void setStart(const Date &start);
    void setEnd(const Date &end);
    void setStartLocation(const std::string &startLocation);
    void setEndLocation(const std::string &endLocation);
    void setAvailableSeat(int availableSeat);
    void setPassengers(const std::pair<Passenger, int>& passengers);
    void setReferenceID(const std::string &referenceID);

    // Getters
    Driver* getDriver() ;
    Vehicle* getVehicle();
    Date getStart() const;
    Date getEnd() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;
    int getAvailableSeat() const;
    std::vector<std::pair<Passenger, int>>& getPassengers();
    std::string getReferenceID() const;

    //methods
    void addPassengerToTrip(Passenger& passenger);
    void changeStatusPassenger(int index, int value);
    string toString();

};

#endif // TRIP_H
