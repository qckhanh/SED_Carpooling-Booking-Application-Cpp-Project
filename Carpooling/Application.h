#pragma once
#include "../headerFile/User.h"
#include "Database.h"
class Application
{
private:
	Driver* driver;
	Passenger* passenger;
	Database db;
public:

	Application();
	Driver* getDriver();
	Passenger* getPassenger();
	void createNewAccount(string type);
	bool signIn();
	void viewAsGuest();
	void viewDriver();
};
