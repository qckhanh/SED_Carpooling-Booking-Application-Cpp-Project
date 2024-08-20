#include "../headerFile/Trip.h"

// Constructor
Trip::Trip()
    : availableSeat(0), startLocation(""), endLocation(""), referenceID("") {}

// Destructor
Trip::~Trip() {}

// Setter methods
void Trip::setDriver(const Driver &driver) { this->driver = driver; }
void Trip::setPassenger(const std::vector<Passenger> &passenger) { this->passenger = passenger; }
void Trip::setVehicle(const Vehicle &vehicle) { this->vehicle = vehicle; }
void Trip::setStart(const Date &start) { this->start = start; }
void Trip::setEnd(const Date &end) { this->end = end; }
void Trip::setStartLocation(const std::string &startLocation) { this->startLocation = startLocation; }
void Trip::setEndLocation(const std::string &endLocation) { this->endLocation = endLocation; }
void Trip::setAvailableSeat(int availableSeat) { this->availableSeat = availableSeat; }
void Trip::setPassengers(const std::vector<std::pair<int, int>> &passengers) { this->passengers = passengers; }
void Trip::setReferenceID(const std::string &referenceID) { this->referenceID = referenceID; }

// Getter methods
Driver Trip::getDriver() const { return driver; }
std::vector<Passenger> Trip::getPassenger() const { return passenger; }
Vehicle Trip::getVehicle() const { return vehicle; }
Date Trip::getStart() const { return start; }
Date Trip::getEnd() const { return end; }
std::string Trip::getStartLocation() const { return startLocation; }
std::string Trip::getEndLocation() const { return endLocation; }
int Trip::getAvailableSeat() const { return availableSeat; }
std::vector<std::pair<int, int>> Trip::getPassengers() const { return passengers; }
std::string Trip::getReferenceID() const { return referenceID; }
