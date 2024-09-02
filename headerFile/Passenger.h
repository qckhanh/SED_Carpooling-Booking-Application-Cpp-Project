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
    void addToTotalCarPoolBooking(Trip* trip);

    // Member functions
    void bookACarPool(Trip* trip);
    void cancelBooking(int index);
};
