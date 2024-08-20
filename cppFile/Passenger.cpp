#include "../headerFile/Passenger.h"
#include <vector>

//Constructor
Passenger::Passenger() : passengerRateScore(0.0f) {}

//Destructor
Passenger::~Passenger() {};

//Getter methods
double Passenger::getPassengerRateScore() const { return passengerRateScore; }
//const std::vector<Trip>& Passenger::getBooking() const { return booking; }

//Setter methods
void Passenger::setPassengerRateScore(const double& passengerRateScore) { this->passengerRateScore = passengerRateScore; }
//void Passenger::setBooking(const std::vector<Trip>& booking) { this->booking = booking; }

//Member functions
void Passenger::bookCarpool() {
    //Implementation
}

void Passenger::cancelBooking() {
    //Implementation
}
