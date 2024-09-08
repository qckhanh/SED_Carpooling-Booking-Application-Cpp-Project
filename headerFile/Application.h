#pragma once
#include "User.h"
#include "Database.h"
#include "NonMember.h"

class Application {
private:
    User* currentUser;
    Driver* driver;
    Passenger* passenger;
    Admin* admin;
    NonMember* guest;
    
    Database db;
    string userType;
    bool isLoggin;

public:
    Application();
    ~Application();

    Driver* getDriver();
    Passenger* getPassenger();
    bool getLoginStatus() const;

    void start();
    void createNewAccount(string type);
    bool logIn();

    void menu_Driver();
    void menu_Passenger();
    void menu_Admin();
    void menu_Guest();

    //Common
    void viewMyFeedback(User* user);
    void doFeedbackUser(string username, string owner);
    void viewAvailableCarpools(float myRate, float myCredit);
    void welcomeScreen(User* user);
    void buyCredit(User* user, bool isFirstTime);
    bool confirmMessage(const string& message);
    //Driver
    void addCarpool();
    void cancelACarpool();
    void Carpool_History();
    void FinishCarpool();
    void addVehicle(Driver* driver);
    void deleteVehicle(Driver* driver);
    void editProfile(User* user);
    //passenger
    

};
