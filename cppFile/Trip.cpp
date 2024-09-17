#include "../headerFile/Trip.h"
#include <iostream>
#include <iomanip>

// Constructor
Trip::Trip() : availableSeat(0) {
    currDriver = nullptr;
    currVehicle = nullptr;
}

// Destructor
Trip::~Trip() {}

// Setters
void Trip::setStatus(const int status) {
    this->status = status;
}
void Trip::setDriver(const std::string& driver_username) {
    this->driver_username = driver_username;
}

void Trip::setDriverP(Driver* driver) {
    this->currDriver = driver;
}

void Trip::setVehicleP(Vehicle* vehicle) {
    this->currVehicle = vehicle;
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

void Trip::setMinRate(const int minRate) {
    this->minRate = minRate;
}
void Trip::setTotalCredit(float credit) {
    totalCredit = credit;
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
float Trip::getTotalCredit() {
    return totalCredit;
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

int Trip::getMinRate() const {
    return minRate;
}
Driver* Trip::getDriverP() {
    return currDriver;
}
Vehicle* Trip::getVehicleP() {
    return currVehicle;
}
// Methods
void Trip::addPassengerToTrip(const std::string& passenger_username, int status) {
    passengers.push_back(std::make_pair(passenger_username, status));
    this->totalCredit += cost;
}
void Trip::changeStatusPassenger(int index, int value) {
    if (index >= 0 && index < passengers.size()) {
        passengers[index].second = value;
        if (value == 2) {
            totalCredit -= cost;
        }
    }
    else {
        std::cerr << "Invalid index: " << index << std::endl;
    }
}
void Trip::removePassenger(const std::string& passenger_username, int status) {
    for (auto it = passengers.begin(); it != passengers.end(); ) {
        if (it->first == passenger_username && it->second == status) {
            it = passengers.erase(it);
        }
        else {
            ++it;
        }
    }
}
void Trip::showInformation(UserExperience& ux) {
    ux.printHeader("TRIP INFORMATION");

    std::cout << std::left;
    std::cout << std::setw(18) << "Driver" << ": " << currDriver->getFullName() << (currDriver->getIsVerified() ? " [Verified] " : "") << endl;
    std::cout << std::setw(18) << "Driver's Rate" << ": " << currDriver->getRateScore() <<"/5" << std::endl;
    std::cout << std::setw(18) << "Start" << ": " << start.getHour() << ":" << start.getMinute() << ", " << start.getDay() << "/" << start.getMonth() << "/" << start.getYear() << std::endl;
    std::cout << std::setw(18) << "End"   << ": " << end.getHour() << ":" << end.getMinute() << ", " << end.getDay() << "/" << end.getMonth() << "/" << end.getYear() << std::endl;
    std::cout << std::setw(18) << "Start Location" << ": " << startLocation << std::endl;
    std::cout << std::setw(18) << "End Location" << ": " << endLocation << std::endl;
    std::cout << std::setw(18) << "Available Seats" << ": " << availableSeat << std::endl;
    std::cout << std::setw(18) << "Min Rate" << ": " << minRate << std::endl;
    std::cout << std::setw(18) << "Cost" << ": " << cost << std::endl;  
    std::cout << std::setw(18) << "Reference ID" << ": " << referenceID << std::endl;
    // Display the list of passengers
    std::cout << std::setw(18) << "Passengers" << ": [";
    for (const auto& passenger : passengers) {
        string status;
        if (passenger.second == 0) status = "Pending";
        else if (passenger.second == 1) status = "Actived";
        else if (passenger.second == 2) status = "Denied";
        else if (passenger.second == 3) status = "Rated";
        else status = "Invalid";
        std::cout << "(" << passenger.first << ", " << status << "), ";
    }
    std::cout << "]" << std::endl;
    currVehicle->showInformation(ux);

}
