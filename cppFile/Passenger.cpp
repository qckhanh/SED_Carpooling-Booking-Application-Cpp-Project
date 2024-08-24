#include "../headerFile/Passenger.h"
#include "../headerFile/Trip.h"
#include <vector>
#include<iostream>
#include<utility>
using namespace std;

//Constructor
Passenger::Passenger() : passengerRateScore(0.0f) {}

//Destructor
Passenger::~Passenger() {};

//Getter methods
double Passenger::getPassengerRateScore() const { return passengerRateScore; }
const std::vector<Trip*>& Passenger::getBooking() const { return totalCarPoolBooking; }

//Setter methods
void Passenger::setPassengerRateScore(const double& passengerRateScore) { this->passengerRateScore = passengerRateScore; }

//Member functions
void Passenger::bookACarPool(Trip* trip) {
    trip->addPassengerToTrip(*this);
    this->totalCarPoolBooking.push_back(trip);
    //Implementation
}

void Passenger::cancelBooking() {
    //Implementation
}
