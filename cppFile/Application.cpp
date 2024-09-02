#include "../headerFile/Application.h"
#include "../headerFile/Passenger.h"
#include "../headerFile/Driver.h"
#include <string>
#include <fstream>
#include <iostream>
#define pauseDisplay system("pause")
#define clearDisplay system("cls")
using namespace std;

Application::Application() : currentUser(nullptr), driver(nullptr), passenger(nullptr) {
    db.loadPassenger();
    db.loadDriver();
    db.loadVehicles();
    db.loadTrips();
    db.loadFeedback();

     this->isLoggin = this->signIn();
    if (isLoggin) {
        if (userType == "driver") {
            driver = dynamic_cast<Driver*>(currentUser);
        }
        else if (userType == "passenger") {
            passenger = dynamic_cast<Passenger*>(currentUser);
        }
    }
    else {
        this->createNewAccount("driver");
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
        cout << "Signed Up Passenger!" << endl;
    }
    else if (type == "driver") {
        currentUser = new Driver();
        cout << "Signed Up Driver!" << endl;
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
                //fstream fout("passenger.txt", ios::out | ios::app);
                /*fout << fullName << ","
                    << userName << ","
                    << password << ","
                    << DOB.getDay() << "," << DOB.getMonth() << "," << DOB.getYear() << ","
                    << phoneNumber << ","
                    << address << ","
                    << email << ","
                    << idType << ","
                    << idNumber << ","
                    << bankAccountName << ","
                    << bankAccountNumber << ","
                    << CVV << ","
                    << accountBalance << ","
                    << expireDate.getDay() << "," << expireDate.getMonth() << "," << expireDate.getYear()
                    << std::endl;
                fout.close();*/
                db.savePassengers();
            }
        }
        else if (type == "driver") {
            Driver* driver = dynamic_cast<Driver*>(currentUser);
            if (driver) {
                db.addDriver(driver);
                /*fstream fout("drivers.txt", ios::out | ios::app);
                fout << fullName << ","
                    << userName << ","
                    << password << ","
                    << DOB.getDay() << "," << DOB.getMonth() << "," << DOB.getYear() << ","
                    << phoneNumber << ","
                    << address << ","
                    << email << ","
                    << idType << ","
                    << idNumber << ","
                    << bankAccountName << ","
                    << bankAccountNumber << ","
                    << CVV << ","
                    << accountBalance << ","
                    << expireDate.getDay() << "," << expireDate.getMonth() << "," << expireDate.getYear()
                    << std::endl;
                fout.close();*/
                db.saveDrivers();
            }
        }
    }
}
bool Application::signIn() {
    cout << "1. Driver\n2. Passenger\n3. Admin\n";
    int opt;
    cout << "Enter your option: ";
    cin >> opt;

    if (opt == 1) userType = "driver";
    if (opt == 2) userType = "passenger";
    if (opt == 3) userType = "admin";

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
}
void Application::menu_Driver() {
    while (true) {
        clearDisplay;
        cout << "Welcome " << driver->getFullName() << "/ Score: " << driver->getRateScore() << endl;

        cout << "0. Exit " << endl;
        cout << "1. Trip Management " << endl;
        cout << "2. Request Management" << endl;
        cout << "3. My profile" << endl;
        cout << "4. My Feedback" << endl;

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
            viewFeeback(driver);
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
        clearDisplay;
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
            viewCarpool(passenger->getRateScore(), passenger->getCreditPoint());
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
        feedbackUser(tmp.first, driver->getUsername());
    }
    
    driver->changeStatusCarpool(index, 2);
    driver->viewCarpool(2);
    cout << "FINISHED" << endl;


}
void Application::viewFeeback(User* user) {
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
void Application::feedbackUser(string username, string owner) {
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
void Application::viewCarpool(float myRate, float myCredit) {
    for (const auto& tmpTrip : db.getTrips()) {
        float trip_minRate = tmpTrip->getMinRate();
        float trip_requireCost = tmpTrip->getCost();
        if (myRate >= trip_minRate && myCredit >= trip_requireCost) {
            cout << tmpTrip->toString() << endl;
        }
    }
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
    cout << "Enter your amount: ";
    cin >> buyAmount;
    if (user->getBankAccount()->getAccountBalance() < buyAmount) {
        cout << "Not enough." << endl;
        return;
    }
    user->receiveCredit(buyAmount);
    user->getBankAccount()->setAccountBalance(user->getBankAccount()->getAccountBalance() - buyAmount);
    return;
}
