#include "../headerFile/Database.h"

// Constructor
Database::Database() {}

// Getters
std::vector<Passenger*>& Database::getPassengers() {
    return passengers;
}

std::vector<Driver*>& Database::getDrivers() {
    return drivers;
}

std::vector<Admin*>& Database::getAdmins() {
    return admins;
}

std::vector<Vehicle*>& Database::getVehicles() {
    return vehicles;
}

std::vector<Trip*>& Database::getTrips() {
    return trips;
}

std::vector<Feedback*>& Database::getFeedbacks() {
    return feedbacks;
}

// Setters
void Database::setPassengers(const std::vector<Passenger*>& newPassengers) {
    passengers = newPassengers;
}

void Database::setDrivers(const std::vector<Driver*>& newDrivers) {
    drivers = newDrivers;
}

void Database::setAdmins(const std::vector<Admin*>& newAdmins) {
    admins = newAdmins;
}

void Database::setVehicles(const std::vector<Vehicle*>& newVehicles) {
    vehicles = newVehicles;
}

void Database::setTrips(const std::vector<Trip*>& newTrips) {
    trips = newTrips;
}

void Database::setFeedbacks(const std::vector<Feedback*>& newFeedbacks) {
    feedbacks = newFeedbacks;
}

// CRUD operations for Passengers
void Database::addPassenger(Passenger* passenger) {
    passengers.push_back(passenger);
}

Passenger* Database::getPassengerByIndex(int index) {
    if (index >= 0 && index < passengers.size()) {
        return passengers[index];
    }
    return nullptr;
}

bool Database::updatePassenger(int index, Passenger* updatedPassenger) {
    if (index >= 0 && index < passengers.size()) {
        passengers[index] = updatedPassenger;
        return true;
    }
    return false;
}

bool Database::deletePassenger(int index) {
    if (index >= 0 && index < passengers.size()) {
        passengers.erase(passengers.begin() + index);
        return true;
    }
    return false;
}

// CRUD operations for Drivers
void Database::addDriver(Driver* driver) {
    drivers.push_back(driver);
}

Driver* Database::getDriverByIndex(int index) {
    if (index >= 0 && index < drivers.size()) {
        return drivers[index];
    }
    return nullptr;
}

bool Database::updateDriver(int index, Driver* updatedDriver) {
    if (index >= 0 && index < drivers.size()) {
        drivers[index] = updatedDriver;
        return true;
    }
    return false;
}

bool Database::deleteDriver(int index) {
    if (index >= 0 && index < drivers.size()) {
        drivers.erase(drivers.begin() + index);
        return true;
    }
    return false;
}

// CRUD operations for Admins
void Database::addAdmin(Admin* admin) {
    admins.push_back(admin);
}

Admin* Database::getAdminByIndex(int index) {
    if (index >= 0 && index < admins.size()) {
        return admins[index];
    }
    return nullptr;
}

bool Database::updateAdmin(int index, Admin* updatedAdmin) {
    if (index >= 0 && index < admins.size()) {
        admins[index] = updatedAdmin;
        return true;
    }
    return false;
}

bool Database::deleteAdmin(int index) {
    if (index >= 0 && index < admins.size()) {
        admins.erase(admins.begin() + index);
        return true;
    }
    return false;
}

// CRUD operations for Vehicles
void Database::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

Vehicle* Database::getVehicleByIndex(int index) {
    if (index >= 0 && index < vehicles.size()) {
        return vehicles[index];
    }
    return nullptr;
}

bool Database::updateVehicle(int index, Vehicle* updatedVehicle) {
    if (index >= 0 && index < vehicles.size()) {
        vehicles[index] = updatedVehicle;
        return true;
    }
    return false;
}

bool Database::deleteVehicle(int index) {
    if (index >= 0 && index < vehicles.size()) {
        vehicles.erase(vehicles.begin() + index);
        return true;
    }
    return false;
}

// CRUD operations for Trips
void Database::addTrip(Trip* trip) {
    trips.push_back(trip);
}

Trip* Database::getTripByIndex(int index, int statusValue) {
    if (index >= 0 && index < trips.size()) {
        int indexFind = 0;
        for (auto& tmp : trips) {
            if (tmp->getStatus() == statusValue) {
                if (indexFind == index) {
                    return tmp;
                }
                indexFind++;
            }
        }
        return nullptr;
    }
    return nullptr;
}

bool Database::updateTrip(int index, Trip* updatedTrip) {
    if (index >= 0 && index < trips.size()) {
        trips[index] = updatedTrip;
        return true;
    }
    return false;
}

bool Database::deleteTrip(Trip* trip) {
    for (int i = 0; i < (int)trips.size(); i++) {
        if (trip == trips[i]) {
            trips.erase(trips.begin() + i);  // Erase only the element at index i
            return true;
        }
    }
    return false;
}

// CRUD operations for Feedbacks
void Database::addFeedback(Feedback* feedback) {
    feedbacks.push_back(feedback);
}

Feedback* Database::getFeedbackByIndex(int index) {
    if (index >= 0 && index < feedbacks.size()) {
        return feedbacks[index];
    }
    return nullptr;
}

bool Database::updateFeedback(int index, Feedback* updatedFeedback) {
    if (index >= 0 && index < feedbacks.size()) {
        feedbacks[index] = updatedFeedback;
        return true;
    }
    return false;
}

bool Database::deleteFeedback(int index) {
    if (index >= 0 && index < feedbacks.size()) {
        feedbacks.erase(feedbacks.begin() + index);
        return true;
    }
    return false;
}

void Database::loadDriver() {
    fstream loadDriver("../Data/drivers.txt", ios::in);
    if (!loadDriver.is_open()) {
        std::cerr << "Error opening file: " << "drivers.txt" << std::endl;
        return;
    }

    string line;
    while (std::getline(loadDriver, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split the line by commas and store in vector
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 15) {
            // Create a new Driver object
            Driver* tmpDriver = new Driver();

            // Extract and set basic user information
            tmpDriver->setFullName(tokens[0]);
            tmpDriver->setUsername(tokens[1]);
            tmpDriver->setPassword(tokens[2]);
            Date tmpDOB(-1, -1, -1, stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
            tmpDriver->setDOB(tmpDOB);
            tmpDriver->setPhoneNumber(tokens[6]);
            tmpDriver->setAddress(tokens[7]);
            tmpDriver->setEmail(tokens[8]);
            tmpDriver->setIdType(tokens[9]);
            tmpDriver->setIdNumber(tokens[10]);
            BankAccount bankAccount;
            bankAccount.setBankAccountName(tokens[11]);
            bankAccount.setBankAccountNumber(tokens[12]);
            bankAccount.setCVV(stoi(tokens[13]));
            bankAccount.setAccountBalance(stod(tokens[14]));
            Date expireDate(-1, -1, -1, stoi(tokens[15]), stoi(tokens[16]), stoi(tokens[17]));

            bankAccount.setExpireDate(expireDate);
            tmpDriver->setBankAccount(bankAccount);
            drivers.push_back(tmpDriver);
        }
        else {
            cout << "Error: Incorrect format in line: " << line << endl;
        }
    }
    loadDriver.close();
}

void Database::loadVehicles() {
    fstream loadVehicle("../Data/vehicles.txt", ios::in);
    if (!loadVehicle.is_open()) {
        std::cerr << "Error opening file: " << "vehicles.txt" << std::endl;
        return;
    }
    string line;
    while (std::getline(loadVehicle, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split the line by commas and store in vector
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 5) {
            // Create a new Vehicle object
            Vehicle* tmpVehicle = new Vehicle(tokens[0], tokens[1], tokens[2], tokens[3], stoi(tokens[4]));

            // Assign the vehicle to the correct driver based on username
            for (auto& driver : drivers) {
                if (driver->getUsername() == tmpVehicle->getOwner_username()) {
                    driver->addVehicle(tmpVehicle);
                    break;
                }
            }
            vehicles.push_back(tmpVehicle);
            //cout << "ADDED: " << tmpVehicle->getModel() << " (" << tmpVehicle->getPlateNumber() << ")" << endl;
        }
        else {
            cout << "Error: Incorrect format in line: " << line << endl;
        }
    }
    loadVehicle.close();
}

void Database::loadPassenger() {
    fstream loadPassenger("../Data/passenger.txt", ios::in);
    string line;
    if (!loadPassenger.is_open()) {
        std::cerr << "Error opening file: " << "passenger.txt" << std::endl;
        return;
    }
    while (std::getline(loadPassenger, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split the line by commas and store in vector
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 15) {
            // Create a new Passenger object
            Passenger* tmpPassenger = new Passenger();

            // Extract and set basic user information
            tmpPassenger->setFullName(tokens[0]);
            tmpPassenger->setUsername(tokens[1]);
            tmpPassenger->setPassword(tokens[2]);
            Date tmpDOB(-1, -1, -1, stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
            tmpPassenger->setDOB(tmpDOB);
            tmpPassenger->setPhoneNumber(tokens[6]);
            tmpPassenger->setAddress(tokens[7]);
            tmpPassenger->setEmail(tokens[8]);
            tmpPassenger->setIdType(tokens[9]);
            tmpPassenger->setIdNumber(tokens[10]);
            BankAccount bankAccount;
            bankAccount.setBankAccountName(tokens[11]);
            bankAccount.setBankAccountNumber(tokens[12]);
            bankAccount.setCVV(stoi(tokens[13]));
            bankAccount.setAccountBalance(stod(tokens[14]));
            Date expireDate(-1, -1, -1, stoi(tokens[15]), stoi(tokens[16]), stoi(tokens[17]));
            bankAccount.setExpireDate(expireDate);
            tmpPassenger->setBankAccount(bankAccount);

            // Add the passenger to the list of passengers
            passengers.push_back(tmpPassenger);

            //cout << "ADDED: " << tmpPassenger->getFullName() << endl;
        }
        else {
            cout << "Error: Incorrect format in line: " << line << endl;
        }
    }
    loadPassenger.close();
}

void Database::loadFeedback() {
    fstream loadPassenger("../Data/feedbacks.txt", ios::in);
    string line;
    if (!loadPassenger.is_open()) {
        std::cerr << "Error opening file: " << "feedbacks.txt" << std::endl;
        return;
    }
    while (std::getline(loadPassenger, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split the line by commas and store in vector
        while (std::getline(ss, item, '~')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 0) {
            // Create a new Passenger object
            Feedback* tmpFeedback = new Feedback();

            tmpFeedback->setOwner_username(tokens[0]);
            tmpFeedback->setAvgRate(-1.0);

            for (int i = 2; i < (int)tokens.size(); i++) {
                std::stringstream strstr(tokens[i]);
                std::string item;
                std::vector<string> cmt;
                while (std::getline(strstr, item, '*')) {
                    cmt.push_back(item);
                    //cout << item << "///";
                }
                //cout << endl;
                tmpFeedback->addFeedback(cmt[0], cmt[1], std::stoi(cmt[2]));
            }
            
            feedbacks.push_back(tmpFeedback);
            for (auto& tmp : drivers) {
                if (tmp->getUsername() == tokens[0]) {
                    tmp->setFeedback(tmpFeedback);
                    continue;
                }
            }
            for (auto& tmp : passengers) {
                if (tmp->getUsername() == tokens[0]) {
                    tmp->setFeedback(tmpFeedback);
                    continue;

                }
            }

            //cout << "ADDED: " << tmpPassenger->getFullName() << endl;
        }
        else {
            cout << "Error: Incorrect format in line: " << line << endl;
        }
    }
    loadPassenger.close();
}

void Database::loadTrips() {
    std::ifstream file("../Data/trips.txt");
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
            Trip* trip = new Trip();

            // Set basic trip information
            trip->setStatus(std::stoi(tokens[0]));
            trip->setDriver(tokens[1]);
            trip->setVehicle(tokens[2]);
            Date startDate(-1, -1, -1, std::stoi(tokens[3]), std::stoi(tokens[4]), std::stoi(tokens[5]));
            trip->setStart(startDate);
            Date endDate(-1, -1, -1, std::stoi(tokens[6]), std::stoi(tokens[7]), std::stoi(tokens[8]));
            trip->setEnd(endDate);
            trip->setStartLocation(tokens[9]);
            trip->setEndLocation(tokens[10]);
            trip->setAvailableSeat(std::stoi(tokens[11]));
            trip->setMinRate(std::stof(tokens[12]));
            trip->setCost(std::stof(tokens[13]));
            trip->setReferenceID(tokens[14]);

            // Process passengers (if any)
            std::vector<std::pair<std::string, int>> passengers;
            if (tokens.size() > 14) {
                for (int i = 15; i < (int)tokens.size(); i++){
                    std::string passengerData = tokens[i];
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
            }
            trip->setPassengers(passengers);

            // Add the trip to the list of trips
            trips.push_back(trip);
            //cout << trip->getReferenceID() << endl;
            // Update the totalCarPoolBooking for the respective passengers
            for (auto& currentPassenger : passengers) {
                for (auto& tmpPassenger : this->passengers) {
                    if (tmpPassenger->getUsername() == currentPassenger.first) {
                        tmpPassenger->addToTotalCarPoolBooking(trip);
                    }
                }
            }

            //cout << "ADDED TRIP: " << trip->getReferenceID() << endl;

            // Update driver's running carpool
            for (auto& tmpDriver : this->drivers) {
                if (tmpDriver->getUsername() == trip->getDriver()) {
                    tmpDriver->setRunningCarpool(trip);
                }
            }
        }
        else {
            std::cerr << "Error: Incorrect format in line: " << line << std::endl;
        }
    }
    file.close();
}

void Database::saveDrivers() {
    std::ofstream saveDriver("../Data/drivers.txt", std::ios::out);
    if (!saveDriver.is_open()) {
        std::cerr << "Error opening file: drivers.txt" << std::endl;
        return;
    }

    for (auto& driver : drivers) {
            saveDriver << driver->getFullName() << ","
            << driver->getUsername() << ","
            << driver->getPassword() << ","
            << driver->getDOB().getDay() << ","
            << driver->getDOB().getMonth() << ","
            << driver->getDOB().getYear() << ","
            << driver->getPhoneNumber() << ","
            << driver->getAddress() << ","
            << driver->getEmail() << ","
            << driver->getIdType() << ","
            << driver->getIdNumber() << ","
            << driver->getBankAccount().getBankAccountName() << ","
            << driver->getBankAccount().getBankAccountNumber() << ","
            << driver->getBankAccount().getCVV() << ","
            << driver->getBankAccount().getAccountBalance() << ","
            << driver->getBankAccount().getExpireDate().getDay() << ","
            << driver->getBankAccount().getExpireDate().getMonth() << ","
            << driver->getBankAccount().getExpireDate().getYear()
            << std::endl;
            

    }
    saveDriver.close();

}

void Database::saveVehicles() {
    std::ofstream saveVehicle("../Data/vehicles.txt", std::ios::out);
    if (!saveVehicle.is_open()) {
        std::cerr << "Error opening file: vehicles.txt" << std::endl;
        return;
    }

    for (const auto& vehicle : vehicles) {
        saveVehicle << vehicle->getOwner_username() << ","
            << vehicle->getModel() << ","
            << vehicle->getColor() << ","
            << vehicle->getPlateNumber() << ","
            << vehicle->getTotalSeat()
            << std::endl;
    }
    saveVehicle.close();
}

void Database::savePassengers() {
    std::ofstream savePassenger("../Data/passenger.txt", std::ios::out);
    if (!savePassenger.is_open()) {
        std::cerr << "Error opening file: passenger.txt" << std::endl;
        return;
    }

    for (auto& passenger : passengers) {
        savePassenger << passenger->getFullName() << ","
            << passenger->getUsername() << ","
            << passenger->getPassword() << ","
            << passenger->getDOB().getDay() << ","
            << passenger->getDOB().getMonth() << ","
            << passenger->getDOB().getYear() << ","
            << passenger->getPhoneNumber() << ","
            << passenger->getAddress() << ","
            << passenger->getEmail() << ","
            << passenger->getIdType() << ","
            << passenger->getIdNumber() << ","
            << passenger->getBankAccount().getBankAccountName() << ","
            << passenger->getBankAccount().getBankAccountNumber() << ","
            << passenger->getBankAccount().getCVV() << ","
            << passenger->getBankAccount().getAccountBalance() << ","
            << passenger->getBankAccount().getExpireDate().getDay() << ","
            << passenger->getBankAccount().getExpireDate().getMonth() << ","
            << passenger->getBankAccount().getExpireDate().getYear()
            << std::endl;

    }
    savePassenger.close();
}

void Database::saveTrips() {
    std::ofstream saveTrip("../Data/trips.txt", std::ios::out);
    if (!saveTrip.is_open()) {
        std::cerr << "Error opening file: trips.txt" << std::endl;
        return;
    }

    for (const auto& trip : trips) {
   saveTrip << trip->getStatus() <<","
            << trip->getDriver() << ","
            << trip->getVehicle() << ","
            << trip->getStart().getDay() << ","
            << trip->getStart().getMonth() << ","
            << trip->getStart().getYear() << ","
            << trip->getEnd().getDay() << ","
            << trip->getEnd().getMonth() << ","
            << trip->getEnd().getYear() << ","
            << trip->getStartLocation() << ","
            << trip->getEndLocation() << ","
            << trip->getAvailableSeat() << ","
            << trip->getMinRate() << ","
            << trip->getCost() << ","
            << trip->getReferenceID();

        // Save passengers and their status (if any)
        const auto& passengers = trip->getPassengers();
        if (!passengers.empty()) {
            saveTrip << ",";
            for (const auto& passenger : passengers) {
                saveTrip << passenger.first << ":" << passenger.second << ",";
            }
            saveTrip.seekp(-1, std::ios_base::end); // Remove the last comma
        }

        saveTrip << std::endl;
    }
    saveTrip.close();
}

void Database::saveDataToFile() {
    saveDrivers();
    savePassengers();
    saveVehicles();
    saveTrips();
    saveFeedback();
}

void Database::saveFeedback() {
    std::ofstream saveFeedbacks("../Data/feedbacks.txt", std::ios::out);

    for (auto& tmp : passengers) {
        saveFeedbacks << tmp->getUsername() << "~"
            << tmp->getRateScore() << "~";

        for (auto& tmpComment : tmp->getFeedback()->getComments()) {
            saveFeedbacks << tmpComment.username << "*" << tmpComment.comment << "*" << tmpComment.score << "~";
        }
        saveFeedbacks << endl;
    }

    for (auto& tmp : drivers) {
        saveFeedbacks << tmp->getUsername() << "~"
            << tmp->getRateScore() << "~";

        for (auto& tmpComment : tmp->getFeedback()->getComments()) {
            saveFeedbacks << tmpComment.username << "*" << tmpComment.comment << "*" << tmpComment.score << "~";
        }
        saveFeedbacks << endl;
    }
    
    saveFeedbacks.close();
}
