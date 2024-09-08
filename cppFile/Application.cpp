#include "../headerFile/Application.h"
#include "../headerFile/Passenger.h"
#include "../headerFile/Driver.h"
#include "../headerFile/Admin.h"
#include "../headerFile/NonMember.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <iomanip> // for setting width and alignment
#define pauseDisplay system("pause")
#define clearDisplay system("cls")
using namespace std;

Application::Application(){
    ux.setDecoratorSymbol('=');
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
        cout << "Good bye! " << endl;
    }
}
Application::~Application() {
    if (currentUser) delete currentUser;
}
bool Application::getLoginStatus() const {
    return isLoggin;
}
void Application::createNewAccount() {

    int opt = -1;
    while (opt != 0) {

        clearDisplay;
        ux.printHeader("REGISTER");
        ux.printOption(1, "I am Driver");
        ux.printOption(2, "I am Passenger");
        ux.printOption(0, "I want to leave!");
        cout << "Enter your option: ";
        cin >> opt;
        string type;
        if (opt == 1) {
            type = "driver";
            currentUser = new Driver();
        }
        else if (opt == 2) {
            type = "passenger";
            currentUser = new Passenger();
        }
        else if (opt == 0) return;
        else {
            cout << "Sorry! Invalid option! " << endl;
            continue;
        }
        ux.printHeader("FILL IN THE FORM");
        string fullName, userName, password, phoneNumber, address, email, idType, idNumber;
        int day, month, year;

        cout << "Enter full name: ";
        cin.ignore();
        getline(cin>>ws, fullName);

        cout << "Enter username: ";
        getline(cin>>ws, userName);

        cout << "Enter password: ";
        getline(cin>>ws, password);

        cout << "Enter day of birth: ";
        cin >> day;
        cout << "Enter month of birth: ";
        cin >> month;
        cout << "Enter year of birth: ";
        cin >> year;
        Date DOB(-1, -1, -1, day, month, year);

        cout << "Enter phone number: ";
        cin.ignore();
        getline(cin>>ws, phoneNumber);

        cout << "Enter address: ";
        getline(cin>>ws, address);

        cout << "Enter email: ";
        getline(cin>>ws, email);

        cout << "Enter ID type (e.g., CCCD): ";
        getline(cin>>ws, idType);

        cout << "Enter ID number: ";
        getline(cin>>ws, idNumber);

        // Bank account information
        string bankAccountName, bankAccountNumber;
        int CVV;
        double accountBalance;
        Date expireDate;

        cout << "Enter bank account name: ";
        getline(cin>>ws, bankAccountName);

        cout << "Enter bank account number: ";
        getline(cin>>ws, bankAccountNumber);

        cout << "Enter CVV: ";
        cin >> CVV;

        accountBalance = 1000;

        cout << "Enter bank account month of expiration : ";
        cin >> month;
        cout << "Enter bank account year of expiration : ";
        cin >> year;
        expireDate = Date(-1, -1, -1, -1, month, year);

        if (!ux.confirmMessage("Do you want to create account? ")) continue;
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
        return;
    }
}
bool Application::logIn() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("WELCOME");
        ux.printOption(1, "I am Driver");
        ux.printOption(2, "I am Passenger");
        ux.printOption(3, "I am Admin");
        ux.printOption(4, "I am Guest");
        ux.printOption(5, "I want to create a new account");
        ux.printOption(0, "I gotta go! ");

        cout << "Enter your option: ";
        cin >> opt;

        if (opt == 0) exit(0);
        else if (opt == 1) userType = "driver";
        else if (opt == 2) userType = "passenger";
        else if (opt == 3) userType = "admin";
        else if (opt == 4) userType = "guest";
        else if (opt == 5) {
            createNewAccount();
            continue;
        }
        else {
            cout << "Invalid option!" << endl;
            continue;
        }

        string username, password;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (!ux.confirmMessage("Sign In? ")) continue;
        if (userType == "driver") {
            for (auto& tmp : db.getDrivers()) {
                if (tmp->getUsername() == username && tmp->getPassword() == password) {
                    currentUser = tmp;
                    return true;
                }
            }
            cout << "Incorrect username or password!" << endl;
            Sleep(3);
        }
        else if (userType == "passenger") {
            for (auto& tmp : db.getPassengers()) {
                if (tmp->getUsername() == username && tmp->getPassword() == password) {
                    currentUser = tmp;
                    return true;
                }
            }
            cout << "Incorrect username or password!" << endl;
            Sleep(3);

        }
        else if (userType == "admin") {
            for (auto& tmp : db.getAdmins()) {
                if (tmp->getUsername() == username && tmp->getPassword() == password) {
                    currentUser = tmp;
                    return true;
                }
            }
            cout << "Incorrect username or password!" << endl;
            Sleep(3);

        }
        else if (userType == "guest") {
            currentUser = new User();
            return true;
        }
        pauseDisplay;
    }
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
            for (const auto& tmp : db.getDrivers()) tmp->showInformation();
            cout << "\n";
            cout << "All Passenger: " << endl;
            for (const auto& tmp : db.getPassengers()) tmp->showInformation();
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

        ux.printOption(0, "Exit");
        ux.printOption(1, "Trip Management");
        ux.printOption(2, "Request Management");
        ux.printOption(3, "My profile");
        ux.printOption(4, "My Feedback");
        ux.printOption(5, "Buy credit");
        ux.printOption(6, "Vehicle Management");

        int opt;
        cout << "Enter your option: ";
        cin >> opt;

        clearDisplay;
        if (opt == 1) TripManagement();
        if (opt == 2) CustommerRequestManagement();
        if (opt == 3) editProfile(driver);
        if (opt == 4) viewMyFeedback(driver);
        if (opt == 5) buyCredit(driver, 0);
        if (opt == 6) VehiclesManagement();
        if (opt == 0) {
            db.saveDataToFile();
            exit(0);
        }

    }
}
void Application::printHeader(const string& title) {
    int width = 45; // Total width of the header, including borders
    int padding = (width - title.length()) / 2; // Calculate padding for centering

    cout << setfill('=') << setw(width) << "=" << endl;  // Top border
    cout << setfill(' ') << setw(padding + title.length()) << title << endl;  // Title centered
    cout << setfill('=') << setw(width) << "=" << endl;  // Bottom border
    cout << setfill(' ') << left; // Reset formatting after the header

}
void Application::menu_Passenger() {

    while (1) {
        welcomeScreen(passenger);

        cout << "Welcome " << passenger->getFullName() << "Score: " << passenger->getRateScore() << endl;
        cout << "1. Book a carpool" << endl;
        cout << "2. Manage my request" << endl;
        cout << "3. Edit my profile" << endl;
        cout << "4. Buy credit" << endl;
        cout << "5. View my feedback" << endl;
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
            //passenger->
            cin >> index;

            passenger->bookACarPool(db.getTripByIndex(index, 1));
            cout << "BOOKED" << endl;
            pauseDisplay;
        }

        if (option == 4) {
            buyCredit(passenger, 0);
            pauseDisplay;
        }


        if (option == 5) {
            clearDisplay;
            viewMyFeedback(passenger);
            pauseDisplay;
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
    ux.printHeader("CUSTOMER'S REVIEW ");
    
    cout << "Your name: " << user->getFullName() << endl;
    cout << "Your rate: " << user->getRateScore() << endl;
    cout << "Comment: " << endl;
    for (auto& tmp : user->getFeedback()->getComments()) {
        cout << "User: " << tmp.username << endl;
        cout << "Rate: " << tmp.score << endl;
        cout << "Comment: " << tmp.comment << endl;
        cout << "---------------------------" << endl;
    }
    pauseDisplay;
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
void Application::viewAvailableCarpools(double myRate, float myCredit) {
    for (const auto& tmpTrip : db.getTrips()) {
        float trip_minRate = tmpTrip->getMinRate();
        float trip_requireCost = tmpTrip->getCost();
        if (myRate >= trip_minRate && myCredit >= trip_requireCost) {
            cout << tmpTrip->toString() << endl;
        }
    }
}
void Application::welcomeScreen(User* user) {
    //clearDisplay;
    ux.printHeader("RENTAL SYSTEM");
    cout << "Hello, " << user->getFullName() << "\t\t" << "Credit: " << user->getCreditPoint() << "/ Rate: " << user->getRateScore() << endl << endl;

}
void Application::buyCredit(User* user, bool isFirstTime) {
    ux.printHeader("CREDIT STORE");
    
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
    
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("CREDIT STORE");
        cout << "You credit: " << user->getCreditPoint() << endl;
        ux.printOption(1, "Buy Credit");
        ux.printOption(0, "Back to menu");

        cout << "Enter your option";
        cin >> opt;
        
        if (opt == 0) return;
        else {
            cout << "Enter your amount: ";
            cin >> buyAmount;
            if (user->getBankAccount()->getAccountBalance() < buyAmount) {
                cout << "Not enough." << endl;
                return;
            }
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(2) << buyAmount;
            std::string formattedAmount = stream.str();

            std::string s = "Do you want to use $" + formattedAmount + " to purchase " + formattedAmount + " credit? ";
            if (ux.confirmMessage(s)) {
                user->receiveCredit(buyAmount);
                user->getBankAccount()->setAccountBalance(user->getBankAccount()->getAccountBalance() - buyAmount);
                cout << "Transaction done! " << endl;
            }
            else {
                cout << "Cancel transaction! " << endl;
            }
            
        }
        pauseDisplay;
    }
    
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
    bool isConfirmed = ux.confirmMessage("Do you want to add vehicle? ");
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
void Application::editProfile(User* user) {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("PROFILE MANAGEMENT");
        driver->showInformation();
        ux.printOption(1, "Edit Full Name");
        ux.printOption(2, "Edit Password");
        ux.printOption(3, "Edit Date of Birth");
        ux.printOption(4, "Edit Phone Number");
        ux.printOption(5, "Edit Address");
        ux.printOption(6, "Edit Email");
        ux.printOption(7, "Edit ID Type");
        ux.printOption(8, "Edit ID Number");
        ux.printOption(9, "View Credit Points");
        ux.printOption(10, "Verify Account");
        ux.printOption(0, "Back to memu");

        cout << "Enter your option: ";
        cin >> opt;

        if (opt == 0) { return; }
        else if (opt == 1) {
            string newName;
            cout << "Enter your new name: ";
            getline(cin >> ws, newName);

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setFullName(newName);
            cout << "Action done!" << endl;
        }
        else if (opt == 2) {
            string newPassword;
            cout << "Enter your new password: ";
            cin >> newPassword;

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setPassword(newPassword);
            cout << "Action done!" << endl;
        }
        else if (opt == 3) {
            int dd, mm, yyyy;
            cout << "Enter your day of birth ";
            cin >> dd;
            cout << "Enter your month of birth ";
            cin >> mm;
            cout << "Enter your year of birth ";
            cin >> yyyy;
            Date newDOB(-1, -1, -1, dd, mm, yyyy);


            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setDOB(newDOB);
            cout << "Action done!" << endl;
        }
        else if (opt == 4) {
            string newPhoneNumber;
            cout << "Enter your new phone number: ";
            cin >> newPhoneNumber;

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setPhoneNumber(newPhoneNumber);
            cout << "Action done!" << endl;
        }
        else if (opt == 5) {
            string newAddress;
            cout << "Enter your new address: ";
            cin >> newAddress;

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setAddress(newAddress);
            cout << "Action done!" << endl;
        }
        else if (opt == 6) {
            string newEmail;
            cout << "Enter your new email: ";
            cin >> newEmail;

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setEmail(newEmail);
            cout << "Action done!" << endl;
        }
        else if (opt == 7) {
            string newIDType;
            cout << "Enter your new ID type: ";
            cin >> newIDType;

            string newIDNumber;
            cout << "Enter your new ID number: ";
            cin >> newIDNumber;

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) {
                driver->setIdType(newIDType);
                driver->setIdNumber(newIDNumber);
            }
            cout << "Action done!" << endl;
        }
        else if (opt == 8) {
            string newIDNumber;
            cout << "Enter your new ID number: ";
            cin >> newIDNumber;

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) driver->setIdNumber(newIDNumber);
            cout << "Action done!" << endl;
        }
        else if (opt == 9) {
            // Assuming you have a function to edit bank account info
            string cardName, number, cvv;
            cout << "Enter your carholder's name: ";
            cin >> cardName;
            cout << "Enter card's number: ";
            cin >> number;
            cout << "Enter card's CVV: ";
            cin >> cvv;
            int mm, yyyy;
            cout << "Enter card's expire month: ";
            cin >> mm;
            cout << "Enter card's expire year: ";
            cin >> yyyy;
            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) {
                Date tmp(-1, -1, -1, -1, mm, yyyy);
                BankAccount* newAccount = new BankAccount();
                newAccount->setBankAccountName(cardName);
                newAccount->setBankAccountNumber(cardName);
                newAccount->setCVV(stoi(cvv));
                newAccount->setExpireDate(tmp);
                newAccount->setAccountBalance(99999);
                user->setBankAccount(newAccount);

            }
            cout << "Action done!" << endl;
        }
        else if (opt == 10) {
            bool isConfirm = ux.confirmMessage("Do you want to verify your account?");
            if (isConfirm) user->verifyAccount();
            cout << "Account verified!" << endl;
        }
        else {
            cout << "Invalid option selected!" << endl;
        }
        pauseDisplay;
    }
    
}
void Application::TripManagement() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("TRIP MANAGEMENT");
        ux.printOption(1, "Add a Carpool");
        ux.printOption(2, "Cancel a Carpool");
        ux.printOption(3, "Finish a carppol");
        ux.printOption(4, "View History");
        ux.printOption(0, "Back to menu");

        cout << "Enter your option: ";
        cin >> opt;

        if (opt == 1) addCarpool();
        else if (opt == 2) cancelACarpool();
        else if (opt == 3) FinishCarpool();
        else if (opt == 4) Carpool_History();
        else if (opt == 0) return;
        pauseDisplay;
    }
    
}
void Application::CustommerRequestManagement() {
    int opt = -1;

    while (opt != 0) {
        clearDisplay;
        ux.printHeader("REQUEST MANAGEMENT");
        ux.printOption(1, "View Requests");
        ux.printOption(2, "Change status's customer request");
        ux.printOption(0, "Back to menu");

        cout << "Enter your option: ";
        cin >> opt;
        if (opt == 0) return;
        else if (opt == 1) {
            driver->viewCarpool(1);
        }
        else if (opt == 2) {
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
        pauseDisplay;
    }

}
void Application::VehiclesManagement() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("VEHICLE MANAGEMENT");

        ux.printOption(1, "Add Vehicle");
        ux.printOption(2, "Delete Vehicle");
        ux.printOption(3, "Edit vehicle");
        ux.printOption(0, "Back to menu");

        cout << "Enter your option: ";
        cin >> opt;
        if (opt == 1) addVehicle(driver);
        if (opt == 2) deleteVehicle(driver);
        if (opt == 3) continue;
        if (opt == 0) return;
        pauseDisplay;
    }

}

