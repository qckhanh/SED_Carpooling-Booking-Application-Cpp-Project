#include "Database.h"
#include "../headerFile/Date.h"
// Constructor
Database::Database() {}

// Getters
std::vector<Passenger>& Database::getPassengers() {
    return passengers;
}

std::vector<Driver>& Database::getDrivers() {
    return drivers;
}

std::vector<Admin>& Database::getAdmins() {
    return admins;
}

std::vector<Vehicle>& Database::getVehicles() {
    return vehicles;
}

std::vector<Trip>& Database::getTrips() {
    return trips;
}

std::vector<Feedback>& Database::getFeedbacks() {
    return feedbacks;
}

// Setters
void Database::setPassengers(const std::vector<Passenger>& newPassengers) {
    passengers = newPassengers;
}

void Database::setDrivers(const std::vector<Driver>& newDrivers) {
    drivers = newDrivers;
}

void Database::setAdmins(const std::vector<Admin>& newAdmins) {
    admins = newAdmins;
}

void Database::setVehicles(const std::vector<Vehicle>& newVehicles) {
    vehicles = newVehicles;
}

void Database::setTrips(const std::vector<Trip>& newTrips) {
    trips = newTrips;
}

void Database::setFeedbacks(const std::vector<Feedback>& newFeedbacks) {
    feedbacks = newFeedbacks;
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

// CRUD operations for Feedbacks
void Database::addFeedback(const Feedback& feedback) {
    feedbacks.push_back(feedback);
}

Feedback* Database::getFeedbackByIndex(int index) {
    if (index >= 0 && index < feedbacks.size()) {
        return &feedbacks[index];
    }
    return nullptr; // Return nullptr if index is out of range
}

bool Database::updateFeedback(int index, const Feedback& updatedFeedback) {
    if (index >= 0 && index < feedbacks.size()) {
        feedbacks[index] = updatedFeedback;
        return true;
    }
    return false; // Return false if index is out of range
}

bool Database::deleteFeedback(int index) {
    if (index >= 0 && index < feedbacks.size()) {
        feedbacks.erase(feedbacks.begin() + index);
        return true;
    }
    return false; // Return false if index is out of range
}

void Database::loadDriver() {
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

        if (tokens.size() >= 15) {
            // Extract and set basic user information
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
            BankAccount bankAccount;
            bankAccount.setBankAccountName(tokens[11]);
            bankAccount.setBankAccountNumber(tokens[12]);
            bankAccount.setCVV(stoi(tokens[13]));
            bankAccount.setAccountBalance(stod(tokens[14]));
            Date expireDate(-1, -1, -1, stoi(tokens[15]), stoi(tokens[16]), stoi(tokens[17]));
            bankAccount.setExpireDate(expireDate);
            tmpDriver.setBankAccount(bankAccount);

            // Add the driver to the list of drivers
            drivers.push_back(tmpDriver);
            
            cout << "ADDED: " << tmpDriver.getFullName();
        }
        else {
            cout << "Error: Incorrect format in line: " << line << endl;
        }
        cout << std::endl;
    }
}

void Database::loadVehicles() {
    fstream loadVehicle("vehicles.txt", ios::in);
    string line;
    while (std::getline(loadVehicle, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split the line by comma and store in vector
        Vehicle tmpVehicle;

        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 5) {
            // Extract and set vehicle information
            tmpVehicle.setOwner_username(tokens[0]); // First token is the owner username
            tmpVehicle.setModel(tokens[1]);
            tmpVehicle.setColor(tokens[2]);
            tmpVehicle.setPlateNumber(tokens[3]);
            tmpVehicle.setTotalSeat(stoi(tokens[4]));

            // Assign the vehicle to the correct driver based on username
            for (auto& driver : drivers) {
                if (driver.getUsername() == tmpVehicle.getOwner_username()) {
                    driver.setDriverVehicles(tmpVehicle);
                    break;
                }
            }
            vehicles.push_back(tmpVehicle);
            cout << "ADDED: " << tmpVehicle.getModel() << " (" << tmpVehicle.getPlateNumber() << ")" << endl;
        }
        else {
            cout << "Error: Incorrect format in line: " << line << endl;
        }
    }
    loadVehicle.close();
}
void Database::loadPassenger() {
    fstream loadPassenger("passenger.txt", ios::in);
    string line;
    if (!loadPassenger.is_open()) {
                std::cerr << "Error opening file: " << "passenger.txt" << std::endl;
                return;
     }
    while (std::getline(loadPassenger, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split the line by comma and store in vector
        Passenger tmpPassenger;
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 15) {
            // Extract and set basic user information
            tmpPassenger.setFullName(tokens[0]);
            tmpPassenger.setUsername(tokens[1]);
            tmpPassenger.setPassword(tokens[2]);
            Date tmpDOB(-1, -1, -1, stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
            tmpPassenger.setDOB(tmpDOB);
            tmpPassenger.setPhoneNumber(tokens[6]);
            tmpPassenger.setAddress(tokens[7]);
            tmpPassenger.setEmail(tokens[8]);
            tmpPassenger.setIdType(tokens[9]);
            tmpPassenger.setIdNumber(tokens[10]);
            BankAccount bankAccount;
            bankAccount.setBankAccountName(tokens[11]);
            bankAccount.setBankAccountNumber(tokens[12]);
            bankAccount.setCVV(stoi(tokens[13]));
            bankAccount.setAccountBalance(stod(tokens[14]));
            Date expireDate(-1, -1, -1, stoi(tokens[15]), stoi(tokens[16]), stoi(tokens[17]));
            bankAccount.setExpireDate(expireDate);
            tmpPassenger.setBankAccount(bankAccount);

            // Add the driver to the list of drivers
            passengers.push_back(tmpPassenger);
            cout << "ADDED: " << tmpPassenger.getFullName();
        }
        else {
            cout << "Error: Incorrect format in line: " << line << endl;
        }
        cout << std::endl;
    }
}

void Database::loadTrips() {
    std::ifstream file("trips.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << "trips.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Split the line by commas and store in vector
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 12) {
            // Create a new Trip object
            Trip trip;

            // Set basic trip information
            trip.setDriver(tokens[0]);
            trip.setVehicle(tokens[1]);
            Date startDate(-1, -1, -1, std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
            trip.setStart(startDate);
            Date endDate(-1, -1, -1, std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]));
            trip.setEnd(endDate);
            trip.setStartLocation(tokens[8]);
            trip.setEndLocation(tokens[9]);
            trip.setAvailableSeat(std::stoi(tokens[10]));
            trip.setReferenceID(tokens[11]);

            // Process passengers (if any)
            std::vector<std::pair<std::string, int>> passengers;
            if (tokens.size() > 12) {
                std::string passengerData = tokens[12];
                size_t pos = 0;
                while ((pos = passengerData.find(',')) != std::string::npos) {
                    std::string entry = passengerData.substr(0, pos);
                    size_t colonPos = entry.find(':');
                    if (colonPos != std::string::npos) {
                        std::string passenger_username = entry.substr(0, colonPos);
                        int status = std::stoi(entry.substr(colonPos + 1));
                        passengers.push_back(std::make_pair(passenger_username, status));
                    }
                    passengerData.erase(0, pos + 1);
                }
                // Process last entry if it exists
                if (!passengerData.empty()) {
                    size_t colonPos = passengerData.find(':');
                    if (colonPos != std::string::npos) {
                        std::string passenger_username = passengerData.substr(0, colonPos);
                        int status = std::stoi(passengerData.substr(colonPos + 1));
                        passengers.push_back(std::make_pair(passenger_username, status));
                    }
                }
            }
            trip.setPassengers(passengers);
            trips.push_back(trip);
            // Add the trip to the list of trips
            trips.push_back(trip);

            // Update the totalCarPoolBooking for the respective passengers
            for (const auto& currentPassenger : passengers) {
                for (auto& tmpPassenger : this->passengers) {
                    if (tmpPassenger.getUsername() == currentPassenger.first) {
                        tmpPassenger.setTotalCarPoolBooking(trip);
                        cout << tmpPassenger.getUsername() << " " << trip.getReferenceID() << endl;
                    }
                }
            }

            cout << "ADDED TRIP: " << trip.getReferenceID() << endl;
            for (auto& tmpDriver : this->drivers) {
                if (tmpDriver.getUsername() == trip.getDriver()) {
                    tmpDriver.setRunningCarpool(trip);
                }
            }
            
        }
        else {
            std::cerr << "Error: Incorrect format in linexx: " << line << std::endl;
        }
    }

    file.close();
}




