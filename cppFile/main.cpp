#include<iostream>
#include "../headerFile/Application.h"
#include <windows.h>  
#include <conio.h>

int main(){
	
	SetConsoleTitleW(L"RENTAL APPLICATION"); 
	Application application;
	
	application.start();
	
	return 0;
}