#include<iostream>
#include "../headerFile/User.h"
#include "../headerFile/Passenger.h"
#include "../headerFile/Application.h"
#include <windows.h>  // For SetConsoleTitle

using namespace std;
#include <conio.h>
int main(){
	
	SetConsoleTitleW(L"RENTAL APPLICATION"); 
	Application application;
	
	application.start();

	return 0;
}