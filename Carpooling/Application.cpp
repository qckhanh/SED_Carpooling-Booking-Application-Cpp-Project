#include "Application.h"
#include "../headerFile/Passenger.h"

#include <string>
#include <fstream>
using namespace std;

Application::Application() {
    db.loadData();
    bool isLogIn = this->signIn();
    if (isLogIn) {
        cout << "LOGGED IN";
        system("cls");
    }
    else cout << "WROGN PASS";
}
void Application::createNewAccount(string type) {
    User* currentUser = nullptr;
    string fullName = "Khong Quoc Khanh";
    string userName = "quockhanh";
    string password = "1102";
    Date DOB(-1, -1, -1, 11, 2, 2005);
    string phoneNumber = "0948865333";
    string address = "Hanoi";
    string email = "abc@example.com";
    string idType = "CCCD";
    string idNumber = "111xxx";

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

        // Add the user to the database
        if (type == "passenger") {
            passenger = dynamic_cast<Passenger*>(currentUser);
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
                    << idNumber << std::endl;
                fout.close();
            }
        }
        else if (type == "driver") {
            driver = dynamic_cast<Driver*>(currentUser);
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
                    << idNumber << std::endl;
                fout.close();


            }
        }
    }

}
bool Application::signIn() {
    cout << "1. Driver\n2. Passenger";
    int opt;
    cin >> opt;
    string type, username, password;
    if (opt == 1) type = "driver";
    if (opt == 2) type = "passenger";
    cin >> username;
    cin >> password;

    if (type == "driver") {
        for (const auto& tmp : db.getDrivers()) {
            if (tmp.getUsername() == username && tmp.getPassword() == password) return true;
        }
        return false;
    }
    else if (type == "passenger") {
        for (auto& tmp : db.getPassengers()) {
            if (tmp.getUsername() == username && tmp.getPassword() == password) return true;
        }
        return false;
    }
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