#include "../headerFile/Application.h"
#include "../headerFile/Passenger.h"
#include "../headerFile/Driver.h"
#include "../headerFile/Admin.h"
#include "../headerFile/NonMember.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <iomanip> 
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
    return 0;
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
    int opt = -1;
    while (opt  != 0) {
        welcomeScreen(admin);
        ux.printOption(1, "View all driver");
        ux.printOption(2, "View all passengers");
        ux.printOption(3, "View all carpools");
        ux.printOption(4, "View all vehicles");
        ux.printOption(0, "Exit");
        
        cout << "Enter your option: ";
        cin >> opt;

        clearDisplay;
        if (opt == 0) exit(0);
        else if (opt == 1) {
            ux.printHeader("ALL DRIVERS");
            for (const auto& tmp : db.getDrivers()) tmp->showInformation(ux);
        }
        else if (opt == 2) {
            ux.printHeader("ALL PASSENGERS");
            for (const auto& tmp : db.getPassengers()) tmp->showInformation(ux);
        }
        else if (opt == 3) {
            ux.printHeader("ALL CARPOOLS");
            for (const auto& tmp : db.getTrips()) tmp->showInformation(ux);
        }
        else if (opt == 4) {
            ux.printHeader("ALL VEHICLES");
            for (const auto& tmp : db.getVehicles()) tmp->showInformation(ux);
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

        ux.printOption(1, "Trip Management");
        ux.printOption(2, "Request Management");
        ux.printOption(3, "My profile");
        ux.printOption(4, "My Feedback");
        ux.printOption(5, "Buy credit");
        ux.printOption(6, "Vehicle Management");
        ux.printOption(0, "Exit");


        int opt;
        cout << "Enter your option: ";
        cin >> opt;

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
void Application::menu_Passenger() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        welcomeScreen(passenger);
        ux.printOption(1, "Search and Book");
        ux.printOption(2, "Request Management");
        ux.printOption(3, "Edit my profile");
        ux.printOption(4, "Buy credit");
        ux.printOption(5, "View my feedback");
        ux.printOption(0, "Exit");


        cout << "Enter your option: ";
        cin >> opt;
        
        if (opt == 1) searchAndBook();
        else if (opt == 2) RequestManagement();
        else if (opt == 3) editProfile(passenger);
        else if (opt == 4) buyCredit(passenger, 0);
        else if (opt == 5) viewMyFeedback(passenger);
        else if (opt == 0) {
            db.saveDataToFile();
            exit(0);
        }
        else cout << "Invalid option" << endl;
    }
}
void Application::addCarpool() {
    clearDisplay;
    ux.printHeader("CREATE NEW CARPOOL");
    string hh, mm, dd, mmmm, yyyy;
    string hh2, mm2, dd2, mmmm2, yyyy2, startLocation, endLocation, referenceID;
    float minRate, cost;

    cout << "Enter the start hour: ";
    cin >> hh;
    cout << "Enter the start minute: ";
    cin >> mm;
    cout << "Enter the start day: ";
    cin >> dd;
    cout << "Enter the start month: ";
    cin >> mmmm;
    cout << "Enter the start year: ";
    cin >> yyyy;

    cout << "Enter the end hour: ";
    cin >> hh2;
    cout << "Enter the end minute: ";
    cin >> mm2;
    cout << "Enter the end day: ";
    cin >> dd2;
    cout << "Enter the end month: ";
    cin >> mmmm2;
    cout << "Enter the end year: ";
    cin >> yyyy2;

    cout << "Enter start location: ";
    getline(cin >> ws, startLocation);

    cout << "Enter end location: ";
    getline(cin >> ws, endLocation);

    cout << "Enter reference ID: ";
    cin >> referenceID;

    cout << "Enter min rate : ";
    cin >> minRate;

    cout << "Enter cost: ";
    cin >> cost;

    driver->viewVehicle(ux);
    int carID;
    cout << "Select the vehicle: ";
    cin >> carID;

    if (!ux.confirmMessage("Do you want to add a new carpool? ")) return;
    Trip* tmpTrip = new Trip();
    tmpTrip->setStatus(1);
    tmpTrip->setDriver(driver->getUsername());
    tmpTrip->setVehicle(driver->getDriverVehicles()[carID  - 1]->getPlateNumber());
    tmpTrip->setAvailableSeat(driver->getDriverVehicles()[carID - 1]->getTotalSeat());
    tmpTrip->setStart(Date(stoi(hh), stoi(mm), -1, stoi(dd), stoi(mmmm), stoi(yyyy)));
    tmpTrip->setEnd(Date(stoi(hh2), stoi(mm2), -1, stoi(dd2), stoi(mmmm2), stoi(yyyy2)));
    tmpTrip->setStartLocation(startLocation);
    tmpTrip->setEndLocation(endLocation);
    tmpTrip->setReferenceID(referenceID);
    tmpTrip->setMinRate(minRate);
    tmpTrip->setCost(cost);

    driver->addActiveTrip(tmpTrip);
    db.addTrip(tmpTrip);      // add to database

    cout << "New Carpool added!" << endl;
}
void Application::cancelACarpool() {
    clearDisplay;
    ux.printHeader("CANCEL A CARPOOL");
    driver->viewCarpool(ux, 1);
    cout << "Enter the index to delete('0' to exit) : ";
    int index;
    cin >> index;
    if (index == 0) return;

    Trip* currentTrip = driver->getCarpoolFromIndex(index, 1);
    for (const auto& tmp : currentTrip->getPassengers()) {
        if (tmp.second == 1) {
            cout << "Sorry, can not cancel this carpool!" << endl;
            return;
        }
    }
    if (!ux.confirmMessage("Do you want to cancel carpool with Reference ID:" + currentTrip->getReferenceID() + "?")) return;
    currentTrip->setStatus(2);
    cout << "Carpool deleted! " << endl;

}
void Application::Carpool_History() {
    clearDisplay;
    ux.printHeader("CARPOOL HISTORY");
    driver->viewCarpool(ux, 2);
}
void Application::FinishCarpool() {
    clearDisplay;
    ux.printHeader("FINSIH CARPOOL");
    driver->viewCarpool(ux, 1);
    vector<Trip*> trips = driver->getCarpoolWithStatus(1);
  
    cout << "Enter the index to finish: ";
    int tripIndex;
    cin >> tripIndex;
    Trip* currenTrip = trips[tripIndex - 1];
    if (!ux.confirmMessage("Do you to finish carpool with Reference ID: " + currenTrip->getReferenceID() + "?")) return;

    if (currenTrip->getPassengers().size() < 1) {
        cout << "Cannot finish this trip!" << endl;
        return;
    }
    for (auto& tmp : currenTrip->getPassengers()) {
        if (tmp.second == 0) {
            cout << "Cannot finish this trip!" << endl;
            return;
        }
    }
    cout << "Passenger: " << endl;
    for (auto& tmp : currenTrip->getPassengers()) {
        cout << tmp.first << endl;
        if(tmp.second == 1) doFeedbackUser(tmp.first, driver->getUsername());
    }
    
    float amount = currenTrip->getTotalCredit();
    cout << "Receive + " << amount << " to your account!" << endl;
    driver->receiveCredit(amount);
    driver->changeStatusCarpool(tripIndex, 2);
    cout << "Changes saved! " << endl;


}
void Application::viewMyFeedback(User* user) {
    clearDisplay;
    // Print the header using UserExperience's method
    ux.printHeader("CUSTOMER'S REVIEW");
    // Display user's basic information
    std::cout << std::left;
    std::cout << "Your Name   : " << user->getFullName() << std::endl;
    std::cout << "Your Rating : " << user->getRateScore() << "/5" << std::endl;
    std::cout << "Comments    :" << std::endl;

    // Print each feedback comment
    std::cout << "---------------------------------------------" << std::endl;
    for (const auto& tmp : user->getFeedback()->getComments()) {
        std::cout << std::setw(10) << "User" << ": " << tmp.username << std::endl;
        std::cout << std::setw(10) << "Rating" << ": " << tmp.score << "/5" << std::endl;
        std::cout << std::setw(10) << "Comment" << ": " << tmp.comment << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }
    pauseDisplay;
}
void Application::doFeedbackUser(string username, string owner) {
    int rate;
    std::string comment;
    cin.ignore(); 
    cout << "Your comment on " << username << ": " << endl;
    getline(cin, comment);
    while (true) {
        cout << "Please rate " << username << " (1 to 5): ";
        cin >> rate;

        if (cin.fail() || rate < 1 || rate > 5) {
            cin.clear(); // Clear the error state
            cin.ignore(); // Discard invalid input
            cout << "Invalid input! Please enter a valid score between 1 and 5." << endl;
        }
        else {
            break; // Exit loop if input is valid
        }
    }


    for (auto& tmpUser : db.getPassengers()) {
        if (tmpUser->getUsername() == username) {
            if (!ux.confirmMessage("Send? ")) return;
            tmpUser->getFeedback()->addFeedback(owner, comment, rate);
            return;
        }
    }
    for (auto& tmpUser : db.getDrivers()) {
        if (tmpUser->getUsername() == username) {
            if (!ux.confirmMessage("Send? ")) return;
            tmpUser->getFeedback()->addFeedback(owner, comment, rate);
            return;
        }
    }
}
vector<Trip*> Application::getAvailableCarpools(double myRate, float myCredit) {
    vector<Trip*> tmp;
    for (auto& tmpTrip : db.getTrips()) {
        float trip_minRate = tmpTrip->getMinRate();
        float trip_requireCost = tmpTrip->getCost();
        if ((myRate >= trip_minRate || myRate == -1) && myCredit >= trip_requireCost) {
            if (tmpTrip->getStatus() == 1) {
                tmp.push_back(tmpTrip);
            }
        }
    }
    return tmp;
}
void Application::welcomeScreen(User* user) {
    clearDisplay;
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
void Application::addVehicle() {
    clearDisplay;
    ux.printHeader("FILL IN THE FORM");
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
        if (tmp->getPlateNumber() == plateNumber && tmp->getStatus()) {
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
    tmpVehicle->setStatus(1);
    cout << "Preview: " << endl;
    tmpVehicle->showInformation(ux);
    if (!ux.confirmMessage("Do you want to add vehicle? ")) return;
    driver->addVehicle(tmpVehicle);
    db.addVehicle(tmpVehicle);
    cout << "Add vehicle successfully! " << endl;
    
}
void Application::deleteVehicle() {
    clearDisplay;
    int index = 1;
    for (const auto& tmp : driver->getDriverVehicles()) {
        if (tmp->getStatus() == 1) {
            cout << endl;
            ux.printOption(index, tmp->getModel());
            tmp->showInformation(ux);
            index++;
        }
    }
    int vehicleIndex;
    cout << "Enter the vehicle' index: ";
    cin >> vehicleIndex;

    index = 1;
    for (auto& tmp : driver->getDriverVehicles()) {
        if (tmp->getStatus() == 1) {
            if (index == vehicleIndex) {
                string s = "Do you want to remove vehicle with plate " + tmp->getPlateNumber() + "?";
                if (!ux.confirmMessage(s)) return;
                tmp->setStatus(0);
                cout << "Vehicle removed! " << endl;
                return;
            }
            index++;
        }
    }
 
}
void Application::editProfile(User* user) {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("PROFILE MANAGEMENT");
        user->showInformation(ux);
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
                user->setIdType(newIDType);
                user->setIdNumber(newIDNumber);
            }
            cout << "Action done!" << endl;
        }
        else if (opt == 8) {
            string newIDNumber;
            cout << "Enter your new ID number: ";
            cin >> newIDNumber;

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setIdNumber(newIDNumber);
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
            clearDisplay;
            ux.printHeader("ALL REQUEST");
            driver->viewCarpool(ux, 1);
        }
        else if (opt == 2) {
            clearDisplay;
            ux.printHeader("CUSTOMER REQUEST");

            /*driver->viewCarpool(ux, 1);*/
            vector<Trip*> trips = driver->getCarpoolWithStatus(1);
            int index = 1;
            for (auto& tmp : trips) {
                cout << index << ": " << tmp->getReferenceID() << ": " << endl;
                tmp->showInformation(ux);
                index++;
            }
            
            int tripID, passID, value;
            cout << "Enter the trip ID ( '0' to exit) ";
            cin >> tripID;
            if (tripID == 0) return;

            Trip* currentTrip = trips[tripID - 1];
            if (currentTrip->getPassengers().size() < 1) {
                cout << "Sorry! This carpool have no request!" << endl;
                pauseDisplay;
                return;
            }
            cout << "Enter the passenger id: ";
            cin >> passID;
            cout << "Enter the status value(0: Pending, 1: Accept, 2: Denied): ";
            cin >> value;

            
            cout << "Preview: " << endl;
            cout << "Trip Refernce ID:" << currentTrip->getReferenceID() << endl;
            cout << "New status of passenger " << currentTrip->getPassengers()[passID - 1].first << currentTrip->getPassengers()[passID - 1].second << " --> " << value << endl;
            if (!ux.confirmMessage("Do you want to save changes? ")) return;
        
            driver->changeStatusOfPassengerInTrip(currentTrip, passID - 1, value);

            cout << "Passenger request updated! " << endl;
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
        ux.printOption(0, "Back to menu");

        cout << "Enter your option: ";
        cin >> opt;
        if (opt == 1) addVehicle();
        if (opt == 2) deleteVehicle();
        if (opt == 0) return;
        pauseDisplay;
    }

}
void Application::RequestManagement() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("REQUEST MANAGEMENT");
        ux.printOption(1, "Cancel my request");
        ux.printOption(2, "History and feedback");
        ux.printOption(0, "Back to menu");

        cout << "Enter your option";
        cin >> opt;

        if (opt == 1) cancelRequest();
        else if (opt == 2) continue;
        else if (opt == 0) return;
        else {
            cout << "Invalid option" << endl;
            return;
        }
        

    }
}
void Application::cancelRequest() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("CANCEL REQUEST");
        ux.printOption(1, "Cancel pending request");
        ux.printOption(2, "Cancel denied requests");
        ux.printOption(0, "Exit");

        cout <<  "Enter your option: ";
        cin >> opt;
        
        if (opt == 0) return;
        else if (opt == 1) {
            vector<Trip*> tmpTrips = passenger->getTripByStatus(0);
            for (auto& it : tmpTrips) it->showInformation(ux);
           
            int opt2;
            cout << "Enter the trip's index: ('0' to exit)" << endl;
            cin >> opt2;

            if (opt2 <= 0) continue;
            if (!ux.confirmMessage("Do you want to cancel this request " + tmpTrips[opt2 - 1]->getReferenceID() + "?")) continue;
            passenger->cancelRequest(tmpTrips[opt2 - 1], 0);
            cout << "Request canceled ! " << endl;
            

        }
        else if (opt == 2) {
            vector<Trip*> tmpTrips = passenger->getTripByStatus(2);
            for (auto& it : tmpTrips) it->showInformation(ux);

            int opt2;
            cout << "Enter the trip's index: ('0' to exit)" << endl;
            cin >> opt2;

            if (opt2 <= 0) continue;
            if (!ux.confirmMessage("Do you want to cancel this request " + tmpTrips[opt2 - 1]->getReferenceID() + "?")) continue;
            passenger->cancelRequest(tmpTrips[opt2 - 1], 2);
            cout << "Request canceled ! " << endl;

        }
        pauseDisplay;
        
        
        
    }
    
}

void Application::searchAndBook() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("Search and Book");
        ux.printOption(1, "Search by dept location");
        ux.printOption(2, "Search by dest location");
        ux.printOption(3, "Search by start date");
        ux.printOption(4, "Search by end date");
        ux.printOption(0, "Exit");

        cout << "Enter option" << endl;
        cin >> opt;

        if (opt == 1) {
            string dept;
            cout << "Enter depature location: " << endl;
            getline(cin >> ws, dept);
            searchByDeparture(dept, 0);
        }
        else if (opt == 2) {
            cout << "Enter destination location: " << endl;
            string dest;
            getline(cin >> ws, dest);
            searchByDestination(dest, 0);
        }
        else if (opt == 3) {
            int dd, mm;
            cout << "Enter date: ";
            cin >> dd;
            cout << "Enter month: ";
            cin >> mm;
            searchByStartDate(dd, mm, 0);
        }

        else if (opt == 4) {
            int dd, mm;
            cout << "Enter date: ";
            cin >> dd;
            cout << "Enter month: ";
            cin >> mm;
            searchByEndDate(dd, mm, 0);
        }
    }

}


void Application::searchByDeparture(string departureLocation, int isGuest) {
    if (!isGuest) {
        int index = 1;
        vector<Trip*> tmpTrip;
        for (auto& it : getAvailableCarpools(passenger->getRateScore(), passenger->getCreditPoint())) {
            string dept = stringFormatSearch(it->getStartLocation());
            string substr = stringFormatSearch(departureLocation);
            bool isFound = (dept.find(substr) != string::npos);
            if (isFound) {
                cout << index << ": Reference ID: " << it->getReferenceID() << " :" << endl;
                it->showInformation(ux);
                tmpTrip.push_back(it);
                index++;
            }
        }

        int opt;
        cout << "Enter the trip's index";
        cin >> opt;
    
        if (opt <= 0) return;
        if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + tmpTrip[opt - 1]->getReferenceID() + "?")) return;
        passenger->bookACarPool(tmpTrip[opt - 1]);

        pauseDisplay;
    }
}

void Application::searchByDestination(string destinationLocation, int isGuest) {
    if (!isGuest) {
        int index = 1;
        vector<Trip*> tmpTrip;
        for (auto& it : getAvailableCarpools(passenger->getRateScore(), passenger->getCreditPoint())) {
            string dest = stringFormatSearch(it->getEndLocation());
            string substr = stringFormatSearch(destinationLocation);
            bool isFound = (dest.find(substr) != string::npos);
            if (isFound) {
                cout << index << ": Reference ID: " << it->getReferenceID() << " :" << endl;
                it->showInformation(ux);
                tmpTrip.push_back(it);
                index++;
            }
        }

        int opt;
        cout << "Enter the trip's index";
        cin >> opt;

        if (opt <= 0) return;
        if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + tmpTrip[opt - 1]->getReferenceID() + "?")) return;
        passenger->bookACarPool(tmpTrip[opt - 1]);

        pauseDisplay;
    }
}

void Application::searchByStartDate(int dd, int mm, int isGuest) {
    if (!isGuest) {
        vector<Trip*> t;
        int index = 1;
        for (auto& it : getAvailableCarpools(passenger->getRateScore(), passenger->getCreditPoint())) {
            if (it->getStart().getDay() == dd && it->getStart().getMonth() == mm) {
                cout << index << ": Reference ID: " << it->getReferenceID() << " :" << endl;
                it->showInformation(ux);
                t.push_back(it);
                index++;
            }
        }
        int opt;
        cout << "Enter the trip's index";
        cin >> opt;

        if (opt <= 0) return;
        if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + t[opt - 1]->getReferenceID() + "?")) return;
        passenger->bookACarPool(t[opt - 1]);
        pauseDisplay;
    }
    
}

void Application::searchByEndDate(int dd, int mm, int isGuest) {
    if (!isGuest) {
        vector<Trip*> t;
        int index = 1;
        for (auto& it : getAvailableCarpools(passenger->getRateScore(), passenger->getCreditPoint())) {
            if (it->getEnd().getDay() == dd && it->getEnd().getMonth() == mm) {
                cout << index << ": Reference ID: " << it->getReferenceID() << " :" << endl;
                it->showInformation(ux);
                t.push_back(it);
                index++;
            }
        }

        int opt;
        cout << "Enter the trip's index";
        cin >> opt;

        if (opt <= 0) return;
        if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + t[opt - 1]->getReferenceID() + "?")) return;
        passenger->bookACarPool(t[opt - 1]);
        pauseDisplay;
    }

}

string Application::stringFormatSearch(string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    for (auto& it : s) {
        it = tolower(it);
    }
    return s;
}

