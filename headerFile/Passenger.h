#pragma once
#include <vector>

class Passenger {
    private:
        double passengerRateScore;
        std::vector<Trip> booking;
    public:
        //Constructor
        Passenger();

        //Destructor
        ~Passenger();

        //Getter methods
        double getPassengerRateScore() const;
        const std::vector<Trip>& getBooking() const;

        //Setter methods
        void setPassengerRateScore(const double& passengerRateScore);
        void setBooking(const std::vector<Trip>& booking);

        //Member function
        void bookCarpool();
        void cancelBooking();
};
