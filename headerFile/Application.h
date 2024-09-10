#pragma once
#include "User.h"
#include "Database.h"
#include "NonMember.h"
#include "UserExperience.h"

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
    UserExperience ux;
public:
    Application();
    ~Application();

    Driver* getDriver();
    Passenger* getPassenger();
    bool getLoginStatus() const;

    void start();
    void createNewAccount();
    bool logIn();

    void menu_Driver();
    void menu_Passenger();
    void menu_Admin();
    void menu_Guest();

    //Common
    void viewMyFeedback(User* user);
    void doFeedbackUser(string username, string owner);
    vector<Trip*> getAvailableCarpools(double myRate, float myCredit);
    void welcomeScreen(User* user);
    void buyCredit(User* user, bool isFirstTime);
    void editProfile(User* user);

    //Driver
    void addCarpool();
    void cancelACarpool();
    void Carpool_History();
    void FinishCarpool();
    void addVehicle();
    void deleteVehicle();
    void TripManagement();
    void CustommerRequestManagement();
    void VehiclesManagement();
    //passenger
    void RequestManagement();
    void cancelRequest();
    void HistoryAndFeedback();
    
    

};
