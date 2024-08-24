#pragma once
#include <vector>
#include "Trip.h"

class Trip;

class Passenger: public User{
    private:
        double passengerRateScore;
        std::vector<Trip*> totalCarPoolBooking;
    public:
        //Constructor
        Passenger();

        //Destructor
        ~Passenger();

        //Getter methods
        double getPassengerRateScore() const;
        const std::vector<Trip*>& getBooking() const;

        //Setter methods
        void setPassengerRateScore(const double& passengerRateScore);

        //Member function
        void bookACarPool(Trip* trip);
        void cancelBooking();
};
