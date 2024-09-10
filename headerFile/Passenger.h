#pragma once
#include <vector>
#include "Trip.h"
#include "Feedback.h"

class Trip;

class Passenger : public User {
private:
    std::vector<Trip*> totalCarPoolBooking;

public:
    // Constructor
    Passenger();

    // Destructor
    ~Passenger();

    // Getter methods
    const std::vector<Trip*>& getBooking() const;

    // Setter methods
    bool addToTotalCarPoolBooking(Trip* trip);

    // Member functions
    void bookACarPool(Trip* trip);
    void cancelBooking(int index);
    void cancelRequest(Trip* trip, int status);
    vector<Trip*> getTripByStatus(int status);
    /*std::vector<Trip*>& getCarpool();
    void viewCarpool(int statusValue) const;*/
};
