#pragma once
#include "User.h"
#include "Database.h"

class Application {
private:
    User* currentUser;
    Driver* driver;
    Passenger* passenger;
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
    bool signIn();
    void viewAsGuest();
    void menu_Driver();
    void menu_Passenger();
    void menu_Admin();
    void menu_Guest();

    //actions
    void addCarpool();
    void cancelACarpool();
    void Carpool_History();
    void FinishCarpool();
    void viewFeeback(User* user);
    void feedbackUser(string username, string owner);
    void viewCarpool(float myRate, float myCredit);
    
    

};
