#include "../headerFile/Trip.h"
#include<utility>
#include<iostream>
using namespace std;
// Constructor
Trip::Trip()
    : availableSeat(0), startLocation(""), endLocation(""), referenceID(""), driver(nullptr), vehicle(nullptr) {}

// Destructor
Trip::~Trip() {}

// Setter methods
void Trip::setDriver( Driver* driver) { 
    this->driver = driver;
}
void Trip::setVehicle( Vehicle* vehicle) { 
    this->availableSeat = vehicle->getTotalSeat();
    this->vehicle = vehicle; 
}
void Trip::setStart(const Date &start) { this->start = start; }
void Trip::setEnd(const Date &end) { this->end = end; }
void Trip::setStartLocation(const std::string &startLocation) { this->startLocation = startLocation; }
void Trip::setEndLocation(const std::string &endLocation) { this->endLocation = endLocation; }
void Trip::setAvailableSeat(int availableSeat) { this->availableSeat = availableSeat; }
void Trip::setPassengers(const pair<Passenger, int> &passengers) { 
    this->passengers.push_back(passengers);
}
void Trip::setReferenceID(const std::string &referenceID) { this->referenceID = referenceID; }

// Getter methods
Driver* Trip::getDriver()  { return driver; }
Vehicle* Trip::getVehicle() { return vehicle; }
Date Trip::getStart() const { return start; }
Date Trip::getEnd() const { return end; }
std::string Trip::getStartLocation() const { return startLocation; }
std::string Trip::getEndLocation() const { return endLocation; }
int Trip::getAvailableSeat() const { return availableSeat; }
std::vector<std::pair<Passenger, int>>& Trip::getPassengers() { return passengers; }
std::string Trip::getReferenceID() const { return referenceID; }


void Trip::addPassengerToTrip(Passenger& passenger) {
    this->passengers.push_back(make_pair(passenger, 0));
    this->availableSeat--;
}
void Trip::changeStatusPassenger(int index, int value) {
    passengers[index].second = value;
}
string Trip::toString() {
        std::ostringstream oss;

        // Driver information
        if (driver != nullptr) {
            oss << "Driver: " << driver->getFullName() << " (" << driver->getUsername() << ")\n";
        }
        else {
            oss << "Driver: Not assigned\n";
        }

        // Vehicle information
        if (vehicle != nullptr) {
            oss << "Vehicle: " << vehicle->getModel() << " (" << vehicle->getPlateNumber() << ")\n";
        }
        else {
            oss << "Vehicle: Not assigned\n";
        }

        // Date information
        oss << "Start Date: " << start.getDay() << "\n"; // Assuming Date has a toString method
        oss << "End Date: " << end.getDay() << "\n";

        // Location information
        oss << "Start Location: " << startLocation << "\n";
        oss << "End Location: " << endLocation << "\n";

        // Available seats
        oss << "Available Seats: " << availableSeat << "\n";

        // Passenger information
        oss << "Passengers:\n";
        for (const pair<Passenger, int> & p : passengers) {
            oss << "  - " << p.first.getFullName() << " (Status: " << p.second << ")\n"; // Assuming Passenger has a getName method
        }

        // Reference ID
        oss << "Reference ID: " << referenceID << "\n";

        return oss.str();
}