#include "Application.h"
#include "../headerFile/Passenger.h"

#include <string>
#include <fstream>
using namespace std;

Application::Application() {
    db.loadPassenger();
    db.loadDriver();
    db.loadVehicles();
    db.loadTrips();
    currentUser = new User();

    bool isSignIn = this->signIn();
    if (isSignIn) {
        if (userType == "driver") {
            driver = dynamic_cast<Driver*>(currentUser);
            menu_Driver();
        }
        else if (userType == "passenger") {
            passenger = dynamic_cast<Passenger*>(currentUser);
            menu_Passenger();
        }
    }
    else {
        this->createNewAccount("driver");
    }
    
}
void Application::createNewAccount(string type) {
    User* currentUser = nullptr;
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

    cout << "Enter account balance: ";
    cin >> accountBalance;

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

        BankAccount bankAccount;
        bankAccount.setBankAccountName(bankAccountName);
        bankAccount.setBankAccountNumber(bankAccountNumber);
        bankAccount.setCVV(CVV);
        bankAccount.setAccountBalance(accountBalance);
        bankAccount.setExpireDate(expireDate);

        currentUser->setBankAccount(bankAccount);

        // Add the user to the database
        if (type == "passenger") {
            Passenger* passenger = dynamic_cast<Passenger*>(currentUser);
            if (passenger) {
                fstream fout("passenger.txt", ios::out | ios::app);
                db.addPassenger(*passenger);
                fout
                    << fullName << ","
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
                fout.close();
            }
        }
        else if (type == "driver") {
            Driver* driver = dynamic_cast<Driver*>(currentUser);
            if (driver) {
                fstream fout("drivers.txt", ios::out | ios::app);
                db.addDriver(*driver);
                fout
                    << fullName << ","
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
                fout.close();
            }
        }
    }
}

bool Application::signIn() {
    cout << "1. Driver\n2. Passenger\n3. Admin";
    int opt;
    cout << "\nEnter your option: ";
    cin >> opt;

    string type, username, password;
    if (opt == 1) userType = "driver";
    if (opt == 2) userType = "passenger";
    if (opt == 3) userType = "admin";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";

    cin >> password;

    if (userType == "driver") {
        for (auto& tmp : db.getDrivers()) {
            if (tmp.getUsername() == username && tmp.getPassword() == password) {
                currentUser = &tmp;
                return true;

            }
        }
        return false;
    }
    else if (userType == "passenger") {
        for (auto& tmp : db.getPassengers()) {
            if (tmp.getUsername() == username && tmp.getPassword() == password) {
                currentUser = &tmp;
                return true;

            }
        }
        return false;
    }
    else if (userType == "admin") {
        for (auto& tmp : db.getAdmins()) {
            if (tmp.getUsername() == username && tmp.getPassword() == password) {
                return true;
            }
        }
        return false;
    }
    return false;
    
}
Driver* Application::getDriver() {
   if(driver) return driver;
   return nullptr;
}
Passenger* Application::getPassenger() {
    if(passenger) return passenger;
    return nullptr;
}
void Application::viewDriver() {
    for (const auto& x : db.getDrivers()) x.toString();
}
void Application::deleteDriver(int index) {
    db.deleteDriver(index);
    cout << "ACCOUNT " << index << "DELETED \n";
}
void Application::menu_Driver() {


    while(1){
        system("cls");
        cout << "Welcome " << driver->getFullName() << endl;
        cout << "1. Trip Management" << endl;
        cout << "2. Request Management" << endl;
        cout << "4. Edit profile" << endl;
        cout << "0. Exit";
        int opt;
        cout << "Enter your option: ";
        cin >> opt;
        if (opt == 1) {
            system("cls");
            cout << "1. Add a Carpool" << endl;
            cout << "2. Cancel a Carpool" << endl;
            cout << "0. Back to Menu" << endl;
            
            int select;
            cout << "Enter your option: ";
            cin>> select;
            if (select == 1) {
                string hh, mm, dd, mmmm, yyyy;
                string hh2, mm2, dd2, mmmm2, yyyy2, startLocation, endLocation, referenceID;
                driver->viewCarpool();
                cout << "Enter the start time: (hh mm dd mmmm yyyy)";
                cin >> hh >> mm >> dd >> mmmm >> yyyy;
                cout << "Enter the end time: (hh mm dd mmmm yyyy)";
                cin >> hh2 >> mm2 >> dd2 >> mmmm2 >> yyyy2;
                cout << "Enter start location: ";
                cin >> startLocation;
                cout << "Enter end location: ";
                cin >> endLocation;
                cout << "Enter reference ID: ";
                cin >> referenceID;
                
                driver->viewVehicle();
                int carOption;
                cout << "Enter car ID: ";
                cin >> carOption;

                string carPlate = driver->getVehicleFromIndex(carOption).getPlateNumber();
                Trip tmpTrip;
                tmpTrip.setDriver(driver->getUsername());
                tmpTrip.setVehicle(driver->getVehicleFromIndex(carOption).getPlateNumber());
                tmpTrip.setStart(Date(stoi(hh), stoi(mm), -1, stoi(dd), stoi(mmmm), stoi(yyyy)));
                tmpTrip.setEnd(Date(stoi(hh2), stoi(mm2), -1, stoi(dd2), stoi(mmmm2), stoi(yyyy2)));
                tmpTrip.setStartLocation(startLocation);
                tmpTrip.setEndLocation(endLocation);
                tmpTrip.setReferenceID(referenceID);
                tmpTrip.setAvailableSeat(driver->getVehicleFromIndex(carOption).getTotalSeat());
                driver->addActiveTrip(tmpTrip);
                driver->viewCarpool();
                cin >> select;
                
            }
            else if (select == 2) {
                driver->viewCarpool();
                int index;
                cout << "Enter the index you want to delete:";
                cin >> index;
                driver->deleteCarpool(index);
                driver->viewCarpool();
                cin >> index;

            }
            
            
            
            
        }
        else if (opt == 2) {
            system("cls");
            for (auto& x : driver->getRunningCarpool()) {
                //cout << x.toString() << endl;
                /*for (auto& y : x.getPassengers()) {
                    cout << y.first << " " << y.second << endl;
                }*/
                for (auto& x : db.getTrips()) cout << x.toString();

                int index;
                cout << "Enter the passenger id: ";
                cin >> index;
                int value;
                cout << "Enter the status value(0: Pending, 1: Accept, 2: Denied): ";
                cin >> value;
                x.changeStatusPassenger(index, value);
               
                
                for (auto& x : db.getTrips()) cout << x.toString();

                system("pause");

            }
        }
        
    }
    
    
    
    

}

void Application::menu_Passenger() {
    system("cls");
    cout << "Welcome " << passenger->getFullName() << endl;
    cout << "1. Trip Management" << endl;
    cout << "2. Request Management" << endl;
    cout << "4. Edit profile" << endl;
    int opt;
    cout << "Enter your option: ";
    cin >> opt;

    if (opt == 1) {
        for (auto x : passenger->getBooking()) cout << x.toString();
    }



}