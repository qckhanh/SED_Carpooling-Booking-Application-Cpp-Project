#include "../headerFile/Application.h"
#include "../headerFile/Passenger.h"
#include "../headerFile/Driver.h"
#include "../headerFile/Admin.h"
#include "../headerFile/NonMember.h"
#include <string>
#include <fstream>
#include <iostream>
#define pauseDisplay system("pause")
#define clearDisplay system("cls")
using namespace std;

Application::Application(){
    this->currentUser = nullptr;
    this->driver = nullptr;
    this->passenger = nullptr;
    this-> admin = nullptr;
    this->guest = nullptr;

    db.loadPassenger();
    db.loadDriver();
    db.loadAdmins();
    db.loadVehicles();
    db.loadTrips();
    db.loadFeedback();

     this->isLoggin = this->logIn();
    if (isLoggin) {
        if (userType == "driver") {
            driver = dynamic_cast<Driver*>(currentUser);
        }
        else if (userType == "passenger") {
            passenger = dynamic_cast<Passenger*>(currentUser);
        }
        else if (userType == "admin") {
            admin = dynamic_cast<Admin*>(currentUser);
        }
        else if (userType == "guest") {
            guest = dynamic_cast<NonMember*>(currentUser);
        }
    }
    else {
        this->createNewAccount(userType);
    }
}
Application::~Application() {
    if (currentUser) delete currentUser;
}
bool Application::getLoginStatus() const {
    return isLoggin;
}
void Application::createNewAccount(string type) {
    string fullName, userName, password, phoneNumber, address, email, idType, idNumber;
    int day, month, year;

    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Enter username: ";
    getline(cin, userName);

    cout << "Enter password: ";
    getline(cin, password);

    cout << "Enter date of birth (day month year): ";
    cin >> day >> month >> year;
    Date DOB(-1, -1, -1, day, month, year);

    cout << "Enter phone number: ";
    cin.ignore();
    getline(cin, phoneNumber);

    cout << "Enter address: ";
    getline(cin, address);

    cout << "Enter email: ";
    getline(cin, email);

    cout << "Enter ID type (e.g., CCCD): ";
    getline(cin, idType);

    cout << "Enter ID number: ";
    getline(cin, idNumber);

    // Bank account information
    string bankAccountName, bankAccountNumber;
    int CVV;
    double accountBalance;
    Date expireDate;

    cout << "Enter bank account name: ";
    getline(cin, bankAccountName);

    cout << "Enter bank account number: ";
    getline(cin, bankAccountNumber);

    cout << "Enter CVV: ";
    cin >> CVV;

    /*cout << "Enter account balance: ";
    cin >> accountBalance;*/
    accountBalance = 1000;

    cout << "Enter bank account expiration date (day month year): ";
    cin >> day >> month >> year;
    expireDate = Date(-1, -1, -1, day, month, year);


    if (type == "passenger") {
        currentUser = new Passenger();
    }
    else if (type == "driver") {
        currentUser = new Driver();
    }

    if (currentUser) {
        currentUser->setFullName(fullName);
        currentUser->setUsername(userName);
        currentUser->setPassword(password);
        currentUser->setAddress(address);
        currentUser->setDOB(DOB);
        currentUser->setPhoneNumber(phoneNumber);
        currentUser->setEmail(email);
        currentUser->setIdType(idType);
        currentUser->setIdNumber(idNumber);

        BankAccount* bankAccount = new BankAccount();
        bankAccount->setBankAccountName(bankAccountName);
        bankAccount->setBankAccountNumber(bankAccountNumber);
        bankAccount->setCVV(CVV);
        bankAccount->setAccountBalance(accountBalance);
        bankAccount->setExpireDate(expireDate);

        currentUser->setBankAccount(bankAccount);
        buyCredit(currentUser, 1);
        // Add the user to the database
        if (type == "passenger") {
            Passenger* passenger = dynamic_cast<Passenger*>(currentUser);
            if (passenger) {
                db.addPassenger(passenger);
                db.savePassengers();
                cout << "Signed Up Passenger!" << endl;

            }
        }
        else if (type == "driver") {
            Driver* driver = dynamic_cast<Driver*>(currentUser);
            if (driver) {
                db.addDriver(driver);
                db.saveDrivers();
                cout << "Signed Up Driver!" << endl;


            }
        }
    }
}
bool Application::logIn() {
    cout << "1. Driver" << endl;
    cout << "2. Passenger" << endl;
    cout << "3. Admin" << endl;
    cout << "4. Guest" << endl;
    int opt;
    cout << "Enter your option: ";
    cin >> opt;

    if (opt == 1) userType = "driver";
    if (opt == 2) userType = "passenger";
    if (opt == 3) userType = "admin";
    if (opt == 4) userType = "guest";

    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (userType == "driver") {
        for (auto& tmp : db.getDrivers()) {
            if (tmp->getUsername() == username && tmp->getPassword() == password) {
                currentUser = tmp;
                return true;
            }
        }
        return false;
    }
    else if (userType == "passenger") {
        for (auto& tmp : db.getPassengers()) {
            if (tmp->getUsername() == username && tmp->getPassword() == password) {
                currentUser = tmp;
                return true;
            }
        }
        return false;
    }
    else if (userType == "admin") {
        for (auto& tmp : db.getAdmins()) {
            if (tmp->getUsername() == username && tmp->getPassword() == password) {
                currentUser = tmp;
                return true;
            }
        }
        return false;
    }
    else if (userType == "guest") {
        currentUser = new User();
        return true;
    }
    return false;
}
Driver* Application::getDriver() {
    return driver;
}
Passenger* Application::getPassenger() {
    return passenger;
}
void Application::start() {
    if (!isLoggin) {
        cout << "You havent logged in yet";
        return;
    }
    if (userType == "driver") menu_Driver();
    if (userType == "passenger") menu_Passenger();
    if (userType == "admin") menu_Admin();
    if (userType == "guest") menu_Guest();
}
void Application::menu_Admin() {
    
    while (1) {
        welcomeScreen(admin);
        cout << "1. View all drivers" << endl;
        cout << "2. View all carpools" << endl;
        cout << "3. View all vehicles" << endl;
        
        int opt;        
        cout << "Enter your option: ";
        cin >> opt;
        clearDisplay;
        if (opt == 1) {
            cout << "All Drivers: " << endl;
            for (const auto& tmp : db.getDrivers()) tmp->toString();
            cout << "\n";
            cout << "All Passenger: " << endl;
            for (const auto& tmp : db.getPassengers()) tmp->toString();
        }
        else if (opt == 2) {
            cout << "All Carpools: " << endl;
            for (const auto& tmp : db.getTrips()) cout << tmp->toString() << endl;
        }
        else if (opt == 3) {
            cout << "All Vehicles: " << endl;
            for (const auto& tmp : db.getVehicles()) tmp->toString();
        }
        pauseDisplay;
        
    }


}
void Application::menu_Guest() {
    welcomeScreen(guest);

}

void Application::menu_Driver() {
    while (true) {
        clearDisplay;
        welcomeScreen(driver);

        cout << "0. Exit " << endl;
        cout << "1. Trip Management " << endl;
        cout << "2. Request Management" << endl;
        cout << "3. My profile" << endl;
        cout << "4. My Feedback" << endl;
        cout << "5. Buy credit " << endl;
        cout << "6. Vehicle Management" << endl;

        int opt;
        cout << "Enter your option: ";
        cin >> opt;
        if (opt == 1) {
            clearDisplay;

            cout << "1. Add a Carpool" << endl;
            cout << "2. Cancel a Carpool" << endl;
            cout << "3. Finish a carppol" << endl;
            cout << "4. History" << endl;
            cout << "5. Back to menu" << endl;

            int select;
            cout << "Enter your option: ";
            cin >> select;

            if (select == 1) addCarpool();
            else if (select == 2) cancelACarpool();
            else if (select == 3) FinishCarpool();
            else if (select == 4) Carpool_History();

            pauseDisplay;
        }
        if (opt == 2) {
            clearDisplay;

            cout << "1. View a request\n2. Update status of a request\n";
            int reqOption;
            cout << "Enter your option: ";
            cin >> reqOption;

            if (reqOption == 1) {
                system("cls");
                driver->viewCarpool(1);
                int tripID, passID, value;
                cout << "Enter the trip ID";
                cin >> tripID;
                cout << "Enter the passenger id: ";
                cin >> passID;
                cout << "Enter the status value(0: Pending, 1: Accept, 2: Denied): ";
                cin >> value;
                driver->changeStatusOfPassengerInTrip(tripID, passID, value);      // already saved to databse

                cout << "UPDATED" << endl;
                for (auto x : db.getTrips()) cout << x->toString() << endl;

                
            }
        }
        if (opt == 3) {
            clearDisplay;

            driver->toString();
            
            int option;
            cin >> option;
            cout << "Choose option you want to change";
            if (option == 1) driver->setFullName("abc");


        }
        if (opt == 4) {
            clearDisplay;
            viewMyFeedback(driver);
        }
        if (opt == 5) {
            buyCredit(driver, 0);
        }
        if (opt == 6) {
            clearDisplay;
            cout << "1. Add Vehicle" << endl;
            cout << "2. Delete Vehicle" << endl;
            cout << "3. Edit vehicle" << endl;

            int opt2;
            cout << "Enter your option: ";
            cin >> opt2;
            if (opt2 == 1) addVehicle(driver);
            if (opt2 == 2) deleteVehicle(driver);
        }
        if (opt == 0) {
            db.saveDataToFile();
            exit(0);
        }

        pauseDisplay;
    }
}
void Application::menu_Passenger() {

    while (1) {
        welcomeScreen(passenger);

        cout << "Welcome " << passenger->getFullName() << "Score: " << passenger->getRateScore() << endl;
        cout << "1. Book a carpool" << endl;
        cout << "2. Manage my request" << endl;
        cout << "3. Edit my profile" << endl;
        cout << "4. Buy credit" << endl;
        cout << "0.Exit app" << endl;

        int option;
        cout << "Enter your option: ";
        cin >> option;
        if (option == 0) {
            db.saveDataToFile();
            exit(0);
        }
        if (option == 1) {
            viewAvailableCarpools(passenger->getRateScore(), passenger->getCreditPoint());
            int index;
            cout << "Enter your trip you want to choose";
            cin >> index;

            passenger->bookACarPool(db.getTripByIndex(index, 1));
            cout << "BOOKED" << endl;
            pauseDisplay;
        }

        if (option == 4) {
            buyCredit(passenger, 0);
        }
    }
}
void Application::addCarpool() {
    string hh, mm, dd, mmmm, yyyy;
    string hh2, mm2, dd2, mmmm2, yyyy2, startLocation, endLocation, referenceID;
    float minRate, cost;

    driver->viewCarpool(1);

    cout << "Enter the start time: (hh mm dd mmmm yyyy): ";
    cin >> hh >> mm >> dd >> mmmm >> yyyy;

    cout << "Enter the end time: (hh mm dd mmmm yyyy): ";
    cin >> hh2 >> mm2 >> dd2 >> mmmm2 >> yyyy2;

    cout << "Enter start location: ";
    cin >> startLocation;

    cout << "Enter end location: ";
    cin >> endLocation;

    cout << "Enter reference ID: ";
    cin >> referenceID;

    cout << "Enter min rate : ";
    cin >> minRate;

    cout << "Enter cost: ";
    cin >> cost;

    driver->viewVehicle();
    int carID;
    cout << "Select your carpool: ";
    cin >> carID;

    Trip* tmpTrip = new Trip();
    tmpTrip->setStatus(1);
    tmpTrip->setDriver(driver->getUsername());
    tmpTrip->setVehicle(driver->getDriverVehicles()[carID]->getPlateNumber());
    tmpTrip->setAvailableSeat(driver->getDriverVehicles()[carID]->getTotalSeat());
    tmpTrip->setStart(Date(stoi(hh), stoi(mm), -1, stoi(dd), stoi(mmmm), stoi(yyyy)));
    tmpTrip->setEnd(Date(stoi(hh2), stoi(mm2), -1, stoi(dd2), stoi(mmmm2), stoi(yyyy2)));
    tmpTrip->setStartLocation(startLocation);
    tmpTrip->setEndLocation(endLocation);
    tmpTrip->setReferenceID(referenceID);
    tmpTrip->setMinRate(minRate);
    tmpTrip->setCost(cost);

    driver->addActiveTrip(tmpTrip);
    db.addTrip(tmpTrip);      // add to database
}
void Application::cancelACarpool() {
    driver->viewCarpool(1);
    cout << "Enter the index to delete: ";
    int index;
    cin >> index;

    driver->changeStatusCarpool(index, 0);
    cout << "DELETED" << endl;

    driver->viewCarpool(0);
}
void Application::Carpool_History() {
    driver->viewCarpool(2);
}
void Application::FinishCarpool() {
    driver->viewCarpool(1);
    cout << "Enter the index to finish: ";
    int index;
    cin >> index;


    cout << "Passenger: " << endl;
    for (auto& tmp : driver->getCarpoolFromIndex(index, 1)->getPassengers()) {
        cout << tmp.first << endl;
        doFeedbackUser(tmp.first, driver->getUsername());
    }
    
    float amount = driver->getCarpoolFromIndex(index, 2)->getCost();
    driver->receiveCredit(amount);
    driver->changeStatusCarpool(index, 2);
    driver->viewCarpool(2);
    cout << "FINISHED" << endl;


}
void Application::viewMyFeedback(User* user) {
    cout << "Your name: " << user->getFullName() << endl;
    cout << "Your rate: " << user->getRateScore() << endl;
    cout << "Comment: " << endl;
    for (auto& tmp : user->getFeedback()->getComments()) {
        cout << "User: " << tmp.username << endl;
        cout << "Rate: " << tmp.score << endl;
        cout << "Comment: " << tmp.comment << endl;
        cout << "---------------------------" << endl;
    }
}
void Application::doFeedbackUser(string username, string owner) {
    int rate;
    string comment;
    cin.ignore();
    cout << "Your comment on " << username << " : " << endl;
    getline(cin, comment);
    cout << "Your score on " << username << " : " << endl;
    cin >> rate;

    for (auto& tmpUser : db.getPassengers()) {
        if (tmpUser->getUsername() == username) {
            tmpUser->getFeedback()->addFeedback(owner, comment, rate);
            cout << "DONE ! " << endl;
            return;
        }
    }
    for (auto& tmpUser : db.getDrivers()) {
        if (tmpUser->getUsername() == username) {
            tmpUser->getFeedback()->addFeedback(owner, comment, rate);
            cout << "DONE ! " << endl;
            return;
        }
    }
}
void Application::viewAvailableCarpools(float myRate, float myCredit) {
    for (const auto& tmpTrip : db.getTrips()) {
        float trip_minRate = tmpTrip->getMinRate();
        float trip_requireCost = tmpTrip->getCost();
        if (myRate >= trip_minRate && myCredit >= trip_requireCost) {
            cout << tmpTrip->toString() << endl;
        }
    }
}

void Application::welcomeScreen(User* user) {
    clearDisplay;
    cout << "============ RENTAL CARSYSTEM===========" << endl;
    cout << "Hello, " << user->getFullName() << "\t\t" << "Credit: " << user->getCreditPoint() << "/ Rate: " << user->getRateScore() << endl;
    cout << "==============WELCOME======================" << endl;
}


void Application::buyCredit(User* user, bool isFirstTime) {
    float buyAmount;
    if (isFirstTime) {
        buyAmount = 10.0;
        cout << "Entry fee is " << buyAmount << endl;
        if (user->getBankAccount()->getAccountBalance() < buyAmount) {
            cout << "Not enough. too poor" << endl;
            return;
        }
        user->receiveCredit(buyAmount);
        user->getBankAccount()->setAccountBalance(user->getBankAccount()->getAccountBalance() - buyAmount);
        return;
    }
    clearDisplay;
    cout << "Enter your amount: ";
    cin >> buyAmount;
    if (user->getBankAccount()->getAccountBalance() < buyAmount) {
        cout << "Not enough." << endl;
        return;
    }
    user->receiveCredit(buyAmount);
    user->getBankAccount()->setAccountBalance(user->getBankAccount()->getAccountBalance() - buyAmount);
    cout << "Transaction done! ";
    return;
}
bool Application::confirmMessage(const string& message) {
    cout << message << endl;
    cout << "1. Yes | 0.No ? ";
    int ans; 
    cin >> ans;
    return ans;
}
void Application::addVehicle(Driver* driver) {
    clearDisplay;

    string model, plateNumber, seats, color;
    cout << "Enter the vehicel's brand: ";
    cin >> model;
    cout << "Enter the vehicle's color: ";
    cin >> color;
    cout << "Enter the vehicle's plate: ";
    cin >> plateNumber;
    cout << "Enter the vehicle' seat number: ";
    cin >> seats;

    for (const auto& tmp : db.getVehicles()) {
        if (tmp->getPlateNumber() == plateNumber) {
            cout << "Sorry! This vehicles has already added! ";
            return;
        }
    }
    Vehicle* tmpVehicle = new Vehicle();
    tmpVehicle->setOwner_username(driver->getUsername());
    tmpVehicle->setModel(model);
    tmpVehicle->setColor(color);
    tmpVehicle->setPlateNumber(plateNumber);
    tmpVehicle->setTotalSeat(stoi(seats));
    cout << "Preview: " << endl;
    tmpVehicle->toString();
    bool isConfirmed = confirmMessage("Do you want to add vehicle? ");
    if (isConfirmed == 1) {
        driver->addVehicle(tmpVehicle);
        db.addVehicle(tmpVehicle);
        cout << "Add vehicle successfully! " << endl;
    }
    else {
        return;
    }
}

void Application::deleteVehicle(Driver* driver) {
    int index = 0;
    for (const auto& tmp : driver->getDriverVehicles()) {
        cout << index << ": ";
        tmp->toString();
        index++;
    }
    int vehicleIndex;
    cout << "Enter the vehicle' index: ";
    cin >> vehicleIndex;
   /* Vehicle* tmp = driver->getVehicleFromIndex(index);
    int i = 0;
    for (auto& tmp : driver->getDriverVehicles()) {
        if(tmp == driver->getVehicleFromIndex(index)) dr
    }*/
    
    

    
}
