#include "../headerFile/Passenger.h"
#include "../headerFile/Trip.h"
#include <vector>
#include<iostream>
#include<utility>
using namespace std;

//Constructor
Passenger::Passenger(){
}

//Destructor
Passenger::~Passenger() {};

//Getter methods

const std::vector<Trip>& Passenger::getBooking() const { return totalCarPoolBooking; }

//Setter methods

//Member functions
void Passenger::bookACarPool(Trip trip) {
    trip.addPassengerToTrip(username, 0);
    setTotalCarPoolBooking(trip);
}

void Passenger::cancelBooking() {
    //Implementation
}

void Passenger::setTotalCarPoolBooking(Trip trip) {
    totalCarPoolBooking.push_back(trip);
}
