#pragma once
#include <vector>
#include "Trip.h"
#include "../Carpooling/Feedback.h";

class Trip;

class Passenger: public User{
    private:
        std::vector<Trip> totalCarPoolBooking;
    public:
        //Constructor
        Passenger();

        //Destructor
        ~Passenger();

        //Getter methods

        const std::vector<Trip>& getBooking() const;

        //Setter methods
        void setTotalCarPoolBooking(Trip trip);
        //Member function
        void bookACarPool(Trip trip);
        void cancelBooking();
};
