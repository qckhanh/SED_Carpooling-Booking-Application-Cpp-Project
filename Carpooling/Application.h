#pragma once
#include "../headerFile/User.h"
#include "Database.h"
class Application
{
private:
	User* currentUser;
	Driver* driver;
	Passenger* passenger;
	Database db;
	string userType;
public:

	Application();
	Driver* getDriver();
	Passenger* getPassenger();
	void createNewAccount(string type);
	bool signIn();
	void viewAsGuest();
	void viewDriver();
	void deleteDriver(int index);
	void menu_Driver();
	void menu_Passenger();
	void menu_Admin();
	void menu_Guest();
};
