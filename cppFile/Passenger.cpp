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
bool Passenger::isCanBook(Trip* trip) {
    if (find(totalCarPoolBooking.begin(), totalCarPoolBooking.end(), trip) != totalCarPoolBooking.end()) return 0;
    if (trip->getAvailableSeat() < 1) return 0;
    if (creditPoint < trip->getCost() || (this->getRateScore() < trip->getMinRate() && this->getRateScore() != -1)) return 0;
    return 1;
}


// Member functions
void Passenger::bookACarPool(Trip* trip) {
  
    if (!isCanBook(trip)) {
        cout << "Sorry! You cant book this carpool! " << endl;
        return;
    }
    addToTotalCarPoolBooking(trip);
    trip->addPassengerToTrip(this->username, 0);
    this->creditPoint -= trip->getCost();
    cout << "Carpool booked! " << endl;
}

void Passenger::cancelBooking(int index) {
    delete totalCarPoolBooking[index]; // Free memory
    totalCarPoolBooking.erase(totalCarPoolBooking.begin() + index);
}

void Passenger::cancelRequest(Trip* trip, int status) {
    trip->removePassenger(this->username, status);
}

vector<Trip*> Passenger::getTripByStatus(int status) {
    vector<Trip*> tmp = {};
    for (auto& currentTrip : totalCarPoolBooking) {
        if (currentTrip->getStatus() == status) {
            tmp.push_back(currentTrip);
        }
        
        
    }
    return tmp;
}
//std::vector<Trip*>& Passenger::getCarpool() {
//    return carpools;
//}

void Passenger::viewCarpool(UserExperience& ux, int statusValue) const {
    int index = 1;
    for (const auto& currentCarpool : totalCarPoolBooking) {
        if (currentCarpool->getStatus() == statusValue) {
            cout << endl;
            cout << index << ": " << currentCarpool->getReferenceID() << ": " << endl;
            currentCarpool->showInformation(ux);
            index++;
        }
    }
}
