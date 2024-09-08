#include "../headerFile/Passenger.h"
#include "../headerFile/Trip.h"
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

// Constructor
Passenger::Passenger() {}

// Destructor
Passenger::~Passenger() {
    // Clean up allocated memory for trips
    for (auto trip : totalCarPoolBooking) {
        delete trip;
    }
}

// Getter methods
const std::vector<Trip*>& Passenger::getBooking() const {
    return totalCarPoolBooking;
}

// Setter methods
void Passenger::addToTotalCarPoolBooking(Trip* trip) {
    totalCarPoolBooking.push_back(trip);
}

// Member functions
void Passenger::bookACarPool(Trip* trip) {
    trip->addPassengerToTrip(username, 0);
    addToTotalCarPoolBooking(trip);
}

void Passenger::cancelBooking(int index) {
    delete totalCarPoolBooking[index]; // Free memory
    totalCarPoolBooking.erase(totalCarPoolBooking.begin() + index);
}

//std::vector<Trip*>& Passenger::getCarpool() {
//    return carpools;
//}

//void Passenger::viewCarpool(int statusValue) const {
//    int index = 0;
//    for (const auto& currentCarpool : carpools) {
//
//    }
//}
