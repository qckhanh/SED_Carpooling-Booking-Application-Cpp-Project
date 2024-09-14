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
    //menu & sub-menu
    void welcomeScreen(User* user);
    void menu_Driver();
    void menu_Passenger();
    void menu_Admin();
    void menu_Guest();
    void VehiclesManagement();
    void changeStatusCustomerRequest();
    void CustommerRequestManagement();
    void TripManagement();
    void RequestManagement();

    //Common
    void viewMyFeedback(User* user);
    bool doFeedbackUser(string username, string owner);
    void buyCredit(User* user, bool isFirstTime);
    void editProfile(User* user);
    void ActiveDashboard(Driver* user);
    void ActiveDashboard(Passenger* user);
    void showActiveCarpool(vector<Trip*> trips);
  
    //Driver
    void addCarpool();
    void cancelACarpool();
    void Carpool_History();
    void FinishCarpool();
    void addVehicle();
    void deleteVehicle();

    //passenger
    void cancelRequest();
    void HistoryAndFeedback();
    void searchAndBook(User* user);
    void searchByDeparture(User* user, string departureLocation, int isGuest);
    void searchByDestination(User* user, string destinationLocation, int isGuest);
    void searchByStartDate(User* user, int dd, int mm, int isGuest);
    void searchByEndDate(User* user, int dd, int mm, int isGuest);

    //preprocessor
    void viewCarpool(const vector<Trip*>& trips);
    vector<Trip*> getAvailableCarpools(double myRate, float myCredit);
    string stringFormatSearch(string s);
    vector<string> getAllUsername();
    bool isOverlapTrip(Date& start, Date& end);
    vector<pair<Date, Date>> getTripTime(Driver* driver);
    bool isInsideAnother(Date& x, Date& start, Date& end);

};
