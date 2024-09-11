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
bool Passenger::addToTotalCarPoolBooking(Trip* trip) {
    if (find(totalCarPoolBooking.begin(), totalCarPoolBooking.end(), trip) == totalCarPoolBooking.end()) {
        totalCarPoolBooking.push_back(trip);
        return 1;
    }
    else cout << "Can not book! " << endl;
    return 0;
}

// Member functions
void Passenger::bookACarPool(Trip* trip) {
    if (addToTotalCarPoolBooking(trip)) {
        trip->addPassengerToTrip(username, 0);
        cout << "Booked! " << endl;
    }
}

void Passenger::cancelBooking(int index) {
    delete totalCarPoolBooking[index]; // Free memory
    totalCarPoolBooking.erase(totalCarPoolBooking.begin() + index);
}

void Passenger::cancelRequest(Trip* trip, int status) {
    trip->removePassenger(this->username, status);
}

vector<Trip*> Passenger::getTripByStatus(int status) {
    vector<Trip*> tmp;
    for (auto& currentTrip : totalCarPoolBooking) {
        for (auto& currentPassenger : currentTrip->getPassengers()) {
            if (currentPassenger.second == status && currentPassenger.first == this->username) {
                if(find(tmp.begin(), tmp.end(), currentTrip) ==  tmp.end()) tmp.push_back(currentTrip);
                break;
            }
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
