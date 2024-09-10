#include "../headerFile/Trip.h"
#include <iostream>
#include <iomanip>

// Constructor
Trip::Trip() : availableSeat(0) {}

// Destructor
Trip::~Trip() {}

// Setters
void Trip::setStatus(const int status) {
    this->status = status;
}
void Trip::setDriver(const std::string& driver_username) {
    this->driver_username = driver_username;
}

void Trip::setVehicle(const std::string& vehicle_plate) {
    this->vehicle_plate = vehicle_plate;
}

void Trip::setStart(const Date& start) {
    this->start = start;
}

void Trip::setEnd(const Date& end) {
    this->end = end;
}

void Trip::setStartLocation(const std::string& startLocation) {
    this->startLocation = startLocation;
}

void Trip::setEndLocation(const std::string& endLocation) {
    this->endLocation = endLocation;
}

void Trip::setAvailableSeat(int availableSeat) {
    this->availableSeat = availableSeat;
}

void Trip::setPassengers(const std::vector<std::pair<std::string, int>>& passengers) {
    this->passengers = passengers;
}

void Trip::setReferenceID(const std::string& referenceID) {
    this->referenceID = referenceID;
}

void Trip::setCost(const float cost) {
    this->cost = cost;
}

void Trip::setMinRate(const float minRate) {
    this->minRate = minRate;
}

// New Setter for Specific Passenger Status
void Trip::setPassengerStatus(const std::string& passenger_username, int status) {
    for (auto& passenger : passengers) {
        if (passenger.first == passenger_username) {
            passenger.second = status;
            return;
        }
    }
    std::cerr << "Passenger not found: " << passenger_username << std::endl;
}

// Getters
int Trip::getStatus() const {
    return status;
}
std::string Trip::getDriver() const {
    return driver_username;
}

std::string Trip::getVehicle() const {
    return vehicle_plate;
}

Date Trip::getStart() const {
    return start;
}

Date Trip::getEnd() const {
    return end;
}

std::string Trip::getStartLocation() const {
    return startLocation;
}

std::string Trip::getEndLocation() const {
    return endLocation;
}

int Trip::getAvailableSeat() const {
    return availableSeat;
}

std::vector<std::pair<std::string, int>>& Trip::getPassengers() {
    return passengers;
}

std::string Trip::getReferenceID() const {
    return referenceID;
}

float Trip::getCost() const {
    return cost;
}

float Trip::getMinRate() const {
    return minRate;
}

// New Getter for Specific Passenger Status
int Trip::getPassengerStatus(const std::string& passenger_username) const {
    for (const auto& passenger : passengers) {
        if (passenger.first == passenger_username) {
            return passenger.second;
        }
    }
    std::cerr << "Passenger not found: " << passenger_username << std::endl;
    return -1; // Return a special value indicating that the passenger was not found
}

// Methods
void Trip::addPassengerToTrip(const std::string& passenger_username, int status) {
    passengers.push_back(std::make_pair(passenger_username, status));
}

void Trip::changeStatusPassenger(int index, int value) {
    if (index >= 0 && index < passengers.size()) {
        passengers[index].second = value;
    }
    else {
        std::cerr << "Invalid index: " << index << std::endl;
    }
}

std::string Trip::toString() {
    std::stringstream ss;
    ss << "Trip [Driver: " << driver_username
        << ", Vehicle: " << vehicle_plate
        //<< ", Start: " << start.toString();
        //<< ", End: " << end.toString()
        << ", Start Location: " << startLocation
        << ", End Location: " << endLocation
        << ", Available Seats: " << availableSeat
        << ", Min Rate: " << minRate
        << ", Cost: " << cost
        << ", Reference ID: " << referenceID
        << ", Passengers: [";

    for (const auto& passenger : passengers) {
        ss << "(" << passenger.first << ", " << passenger.second << "), ";
    }

    ss << "]]";
    return ss.str();
}

void Trip::showInformation(UserExperience& ux) {
    ux.printHeader("TRIP INFORMATION");

    std::cout << std::left;
    std::cout << std::setw(18) << "Driver" << ": " << driver_username << std::endl;
    //driver rate
    std::cout << std::setw(18) << "Vehicle" << ": " << vehicle_plate << std::endl;
    // std::cout << std::setw(18) << "Start" << ": " << start.toString() << std::endl;
    // std::cout << std::setw(18) << "End"   << ": " << end.toString() << std::endl;
    std::cout << std::setw(18) << "Start Location" << ": " << startLocation << std::endl;
    std::cout << std::setw(18) << "End Location" << ": " << endLocation << std::endl;
    std::cout << std::setw(18) << "Available Seats" << ": " << availableSeat << std::endl;
    std::cout << std::setw(18) << "Min Rate" << ": " << minRate << std::endl;
    std::cout << std::setw(18) << "Cost" << ": " << cost << std::endl;
    std::cout << std::setw(18) << "Reference ID" << ": " << referenceID << std::endl;

    // Display the list of passengers
    std::cout << std::setw(18) << "Passengers" << ": [";
    for (const auto& passenger : passengers) {
        std::cout << "(" << passenger.first << ", " << passenger.second << "), ";
    }
    std::cout << "]" << std::endl;

}


