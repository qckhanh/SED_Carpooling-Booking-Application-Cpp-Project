#include "Database.h"
#include "../headerFile/Date.h"
// Constructor
Database::Database() {}

// Getters
vector<Passenger>& Database::getPassengers() {
    return passengers;
}

vector<Driver>& Database::getDrivers() {
    return drivers;
}

vector<Admin>& Database::getAdmins() {
    return admins;
}

vector<Vehicle>& Database::getVehicles() {
    return vehicles;
}

vector<Trip>& Database::getTrips() {
    return trips;
}

// Setters
void Database::setPassengers(const vector<Passenger>& newPassengers) {
    passengers = newPassengers;
}

void Database::setDrivers(const vector<Driver>& newDrivers) {
    drivers = newDrivers;
}

void Database::setAdmins(const vector<Admin>& newAdmins) {
    admins = newAdmins;
}

void Database::setVehicles(const vector<Vehicle>& newVehicles) {
    vehicles = newVehicles;
}

void Database::setTrips(const vector<Trip>& newTrips) {
    trips = newTrips;
}

// CRUD operations for Passengers
void Database::addPassenger(const Passenger& passenger) {
    passengers.push_back(passenger);
}

Passenger* Database::getPassengerByIndex(int index) {
    if (index >= 0 && index < passengers.size()) {
        return &passengers[index];
    }
    return nullptr; // Return nullptr if index is out of range
}

bool Database::updatePassenger(int index, const Passenger& updatedPassenger) {
    if (index >= 0 && index < passengers.size()) {
        passengers[index] = updatedPassenger;
        return true;
    }
    return false; // Return false if index is out of range
}

bool Database::deletePassenger(int index) {
    if (index >= 0 && index < passengers.size()) {
        passengers.erase(passengers.begin() + index);
        return true;
    }
    return false; // Return false if index is out of range
}

// CRUD operations for Drivers
void Database::addDriver(const Driver& driver) {
    drivers.push_back(driver);
}

Driver* Database::getDriverByIndex(int index) {
    if (index >= 0 && index < drivers.size()) {
        return &drivers[index];
    }
    return nullptr; // Return nullptr if index is out of range
}

bool Database::updateDriver(int index, const Driver& updatedDriver) {
    if (index >= 0 && index < drivers.size()) {
        drivers[index] = updatedDriver;
        return true;
    }
    return false; // Return false if index is out of range
}

bool Database::deleteDriver(int index) {
    if (index >= 0 && index < drivers.size()) {
        drivers.erase(drivers.begin() + index);
        return true;
    }
    return false; // Return false if index is out of range
}

// CRUD operations for Admins
void Database::addAdmin(const Admin& admin) {
    admins.push_back(admin);
}

Admin* Database::getAdminByIndex(int index) {
    if (index >= 0 && index < admins.size()) {
        return &admins[index];
    }
    return nullptr; // Return nullptr if index is out of range
}

bool Database::updateAdmin(int index, const Admin& updatedAdmin) {
    if (index >= 0 && index < admins.size()) {
        admins[index] = updatedAdmin;
        return true;
    }
    return false; // Return false if index is out of range
}

bool Database::deleteAdmin(int index) {
    if (index >= 0 && index < admins.size()) {
        admins.erase(admins.begin() + index);
        return true;
    }
    return false; // Return false if index is out of range
}

// CRUD operations for Vehicles
void Database::addVehicle(const Vehicle& vehicle) {
    vehicles.push_back(vehicle);
}

Vehicle* Database::getVehicleByIndex(int index) {
    if (index >= 0 && index < vehicles.size()) {
        return &vehicles[index];
    }
    return nullptr; // Return nullptr if index is out of range
}

bool Database::updateVehicle(int index, const Vehicle& updatedVehicle) {
    if (index >= 0 && index < vehicles.size()) {
        vehicles[index] = updatedVehicle;
        return true;
    }
    return false; // Return false if index is out of range
}

bool Database::deleteVehicle(int index) {
    if (index >= 0 && index < vehicles.size()) {
        vehicles.erase(vehicles.begin() + index);
        return true;
    }
    return false; // Return false if index is out of range
}

// CRUD operations for Trips
void Database::addTrip(const Trip& trip) {
    trips.push_back(trip);
}

Trip* Database::getTripByIndex(int index) {
    if (index >= 0 && index < trips.size()) {
        return &trips[index];
    }
    return nullptr; // Return nullptr if index is out of range
}

bool Database::updateTrip(int index, const Trip& updatedTrip) {
    if (index >= 0 && index < trips.size()) {
        trips[index] = updatedTrip;
        return true;
    }
    return false; // Return false if index is out of range
}

bool Database::deleteTrip(int index) {
    if (index >= 0 && index < trips.size()) {
        trips.erase(trips.begin() + index);
        return true;
    }
    return false; // Return false if index is out of range
}

void Database::loadData() {
    fstream loadDriver("drivers.txt", ios::in);
    string line;
    while (std::getline(loadDriver, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split the line by comma and store in vector
        Driver tmpDriver;
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);

        }

        tmpDriver.setFullName(tokens[0]);
        tmpDriver.setUsername(tokens[1]);
        tmpDriver.setPassword(tokens[2]);
        Date tmpDOB(-1, -1, -1, stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
        tmpDriver.setDOB(tmpDOB);
        tmpDriver.setPhoneNumber(tokens[6]);
        tmpDriver.setAddress(tokens[7]);
        tmpDriver.setEmail(tokens[8]);
        tmpDriver.setIdType(tokens[9]);
        tmpDriver.setIdNumber(tokens[10]);
        drivers.push_back(tmpDriver);
        cout << "ADDED";

        std::cout << std::endl << endl;
    }

}
