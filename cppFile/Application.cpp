#include "../headerFile/Application.h"
#include "../headerFile/Passenger.h"
#include "../headerFile/Driver.h"
#include "../headerFile/Admin.h"
#include "../headerFile/NonMember.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <iomanip> 
#define pauseDisplay system("pause")
#define clearDisplay system("cls")
using namespace std;
//getter and setter
Application::Application(){
    ux.setDecoratorSymbol('=');
    this->currentUser = nullptr;
    this->driver = nullptr;
    this->passenger = nullptr;
    this-> admin = nullptr;
    this->guest = nullptr;
    this->isLoggin = false;
    db.loadPassenger();
    db.loadDriver();
    db.loadAdmins();
    db.loadVehicles();
    db.loadTrips();
    db.loadFeedback();

   
}
Application::~Application() {
    if (currentUser) delete currentUser;
}
bool Application::getLoginStatus() const {
    return isLoggin;
}
void Application::createNewAccount() {

    int opt = -1;
    while (opt != 0) {

        clearDisplay;
        ux.printHeader("REGISTER");
        ux.printOption(1, "I am Driver");
        ux.printOption(2, "I am Passenger");
        ux.printOption(0, "I want to leave!");
        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 2);

        string type;
        if (opt == 1) {
            type = "driver";
            currentUser = new Driver();
        }
        else if (opt == 2) {
            type = "passenger";
            currentUser = new Passenger();
        }
        else if (opt == 0) return;
        else {
            cout << "Sorry! Invalid option! " << endl;
            continue;
        }
        ux.printHeader("FILL IN THE FORM");

        cin.ignore();
        string fullName = ux.getValidInput<string>("Enter you full name: ", &UserExperience::isValidName);
        std::vector<std::string> allUsernames = getAllUsername();
        string userName;
        while (1) {
            userName = ux.getValidInput<string>("Enter username: ", &UserExperience::isValidUsername);
            vector<string> usernames = getAllUsername();
            if (find(usernames.begin(), usernames.end(), userName) == usernames.end()) break;
            else cout << userName << " already existed! Try another username! " << endl;
        }
        
        string password, RePassword;
        while (1) {
            cout << "Enter your password: ";
           
            password = ux.getPasswordInput();
            if (!ux.isValidPassword(password)) {
                cout << "Password must be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, one number, and one special character, please re-enter" << endl;
                continue;
            }

            cout << "Re-enter your password: ";
            RePassword = ux.getPasswordInput();

            if (password == RePassword) break;
            else {
                cout << "Password doesnt match! Please re-eneter your password!" << endl;
            }
        }
        Date DOB;
        while (1) {
            int day = ux.getValidInput<int>("Enter day of birth: ", &UserExperience::isValidOption, 1, 31);
            int month = ux.getValidInput<int>("Enter month of birth: ", &UserExperience::isValidOption, 1, 12);
            int year = ux.getValidInput<int>("Enter year of birth: ", &UserExperience::isValidOption, 0, 2006);
            if (ux.isValidDate(day, month, year)) {
                DOB.setDay(day);
                DOB.setMonth(month);
                DOB.setYear(year);
                break;
            }
            else {
                cout << "Invalid birthdate! Please try again!" << endl;
            }
        }
        
        string phoneNumber = ux.getValidInput<string>("Enter phone number: ", &UserExperience::isValidPhoneNumber);
        string address = ux.getValidInput<string>("Enter address: ", &UserExperience::isValidLocation);
        string email = ux.getValidInput<std::string>("Enter a email: ",&UserExperience::isValidEmail);

        cout << "We support 2 Identity Verification type: " << endl;
        ux.printOption(1, "Passport");
        ux.printOption(2, "Identity Card");
        int opt = ux.getValidInput<int>("Enter your ID type: ", &UserExperience::isValidOption, 1, 2);
        string IDType, idNumber;
        if (opt == 1) {
            IDType = "Passport";
            idNumber = ux.getValidInput<string>("Enter your Passport number: ", &UserExperience::isValidPassportNumber);
        }
        else if (opt == 2) {
            IDType = "Idenity Card";
            idNumber = ux.getValidInput<string>("Enter your Identity card number: ", &UserExperience::isValidIdentityNumber);
        }

        Date expireDate;
        string bankAccountName = ux.getValidInput<string>("Enter bank account name: ", &UserExperience::isValidName);
        string bankAccountNumber = ux.getValidInput<string>("Enter bank account number: ", &UserExperience::isValidCardNumber);
        double accountBalance = 1000;
        while (1) {
            int month = ux.getValidInput<int>("Enter bank account month of expiration : ", &UserExperience::isValidOption, 1, 12);
            int year = ux.getValidInput<int>("Enter bank account year of expiration : ", &UserExperience::isValidOption, 2025, 2100);
            expireDate = Date(-1, -1, -1, -1, month, year);
            if (ux.isValidDateTrip(expireDate)) break;
            else {
                cout << "Invalid date!" << endl;
            }
        }
        int CVV = ux.getValidInput<int>("Enter CVV code: ", &UserExperience::isValidCVV);
 
        if (!ux.confirmMessage("Do you want to create account? ")) continue;

        if (currentUser) {
            currentUser->setFullName(fullName);
            currentUser->setUsername(userName);
            currentUser->setPassword(password);
            currentUser->setAddress(address);
            currentUser->setDOB(DOB);
            currentUser->setPhoneNumber(phoneNumber);
            currentUser->setEmail(email);
            currentUser->setIdType(IDType);
            currentUser->setIdNumber(idNumber);

            BankAccount* bankAccount = new BankAccount();
            bankAccount->setBankAccountName(bankAccountName);
            bankAccount->setBankAccountNumber(bankAccountNumber);
            bankAccount->setCVV(CVV);
            bankAccount->setAccountBalance(accountBalance);
            bankAccount->setExpireDate(expireDate);

            currentUser->setBankAccount(bankAccount);
            buyCredit(currentUser, 1);
            // Add the user to the database
            if (type == "passenger") {
                Passenger* passenger = dynamic_cast<Passenger*>(currentUser);
                if (passenger) {
                    db.addPassenger(passenger);
                    db.savePassengers();
                    cout << "Signed Up Passenger!" << endl;

                }
            }
            else if (type == "driver") {
                Driver* driver = dynamic_cast<Driver*>(currentUser);
                if (driver) {
                    db.addDriver(driver);
                    db.saveDrivers();
                    cout << "Signed Up Driver!" << endl;
                }
            }
        }
        return;
    }
}
bool Application::logIn() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("WELCOME");
        ux.printOption(1, "I am Driver");
        ux.printOption(2, "I am Passenger");
        ux.printOption(3, "I am Admin");
        ux.printOption(4, "I am Guest");
        ux.printOption(5, "I want to create a new account");
        ux.printOption(0, "I gotta go! ");

        int opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 5);

        if (opt == 0) exit(0);
        else if (opt == 1) userType = "driver";
        else if (opt == 2) userType = "passenger";
        else if (opt == 3) userType = "admin";
        else if (opt == 4) userType = "guest";
        else if (opt == 5) {
            createNewAccount();
            continue;
        }
        else {
            cout << "Invalid option!" << endl;
            continue;
        }
        string username, password;

        if (opt != 4) {

            cin.ignore();
            cout << "Enter your username: ";
            getline(cin, username);
            cout << "Enter your password: ";
            password = ux.getPasswordInput();
            if (!ux.confirmMessage("Sign In? ")) return 0;
        }
        if (userType == "driver") {
            for (auto& tmp : db.getDrivers()) {
                if (tmp->getUsername() == username && tmp->getPassword() == password) {
                    currentUser = tmp;
                    return true;
                }
            }
            cout << "Incorrect username or password!" << endl;
            Sleep(3);
        }
        else if (userType == "passenger") {
            for (auto& tmp : db.getPassengers()) {
                if (tmp->getUsername() == username && tmp->getPassword() == password) {
                    currentUser = tmp;
                    return true;
                }
            }
            cout << "Incorrect username or password!" << endl;
            Sleep(3);

        }
        else if (userType == "admin") {
            for (auto& tmp : db.getAdmins()) {
                if (tmp->getUsername() == username && tmp->getPassword() == password) {
                    currentUser = tmp;
                    return true;
                }
            }
            cout << "Incorrect username or password!" << endl;
            Sleep(3);

        }
        else if (userType == "guest") {
            currentUser = new User();
            currentUser->setFullName("Guest");
            currentUser->setCreditPoint(100000);
            return true;
        }
        pauseDisplay;
    }
    return 0;
}
Driver* Application::getDriver() {
    return driver;
}
Passenger* Application::getPassenger() {
    return passenger;
}
void Application::start() {
    while (1) {
        this->isLoggin = this->logIn();
        if (isLoggin) {
            if (userType == "driver") {
                driver = dynamic_cast<Driver*>(currentUser);
            }
            else if (userType == "passenger") {
                passenger = dynamic_cast<Passenger*>(currentUser);
            }
            else if (userType == "admin") {
                admin = dynamic_cast<Admin*>(currentUser);
            }
            else if (userType == "guest") {
                guest = dynamic_cast<NonMember*>(currentUser);
            }
            if (userType == "driver") menu_Driver();
            if (userType == "passenger") menu_Passenger();
            if (userType == "admin") menu_Admin();
            if (userType == "guest") menu_Guest();
        }
        else {
            cout << "Good bye! " << endl;
        }
    }
    

}
void Application::welcomeScreen(User* user) {
    ux.printHeader("RENTAL SYSTEM");
    cout << "Hello, " << user->getFullName() << "\t\t" << "Credit: " << user->getCreditPoint() << "/ Rate: " << user->getRateScore() << endl << endl;

}

//menu and sub-menu
void Application::menu_Admin() {
    int opt = -1;
    while (opt  != 0) {
        welcomeScreen(admin);
        ux.printOption(1, "View all driver");
        ux.printOption(2, "View all passengers");
        ux.printOption(3, "View all carpools");
        ux.printOption(4, "View all vehicles");
        ux.printOption(0, "Exit");
        
        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 4);

        clearDisplay;
        if (opt == 0) return;
        else if (opt == 1) {
            ux.printHeader("ALL DRIVERS");
            for (const auto& tmp : db.getDrivers()) tmp->showInformation(ux);
        }
        else if (opt == 2) {
            ux.printHeader("ALL PASSENGERS");
            for (const auto& tmp : db.getPassengers()) tmp->showInformation(ux);
        }
        else if (opt == 3) {
            ux.printHeader("ALL CARPOOLS");
            for (const auto& tmp : db.getTrips()) tmp->showInformation(ux);
        }
        else if (opt == 4) {
            ux.printHeader("ALL VEHICLES");
            for (const auto& tmp : db.getVehicles()) tmp->showInformation(ux);
        }
        else {
            cout << "Invalid option" << endl;
        }
        pauseDisplay;
        
    }


}
void Application::menu_Guest() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        welcomeScreen(currentUser);
        vector<Trip*> trips = getAvailableCarpools(3, currentUser->getCreditPoint());
        showActiveCarpool(trips);
        cout << endl << endl;
        ux.printOption(1, "See detailed carpool");
        ux.printOption(2, "Search a carpoool");
        ux.printOption(3, "Register as memeber");
        ux.printOption(0, "Exit guest mode");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 3);
        if (opt == 0) return;
        else if (opt == 1) {
            clearDisplay;
            viewCarpool(trips);
            pauseDisplay;
        }
        else if ( opt == 2) {
            clearDisplay;
            searchAndBook(currentUser);
        }
        else {
            createNewAccount();

        }
    }


}
void Application::menu_Driver() {
    while (true) {
        clearDisplay;
        welcomeScreen(driver);
        ActiveDashboard(driver);
        ux.printOption(1, "Trip Management");
        ux.printOption(2, "Request Management");
        ux.printOption(3, "My profile");
        ux.printOption(4, "My Feedback");
        ux.printOption(5, "Buy credit");
        ux.printOption(6, "Vehicle Management");
        ux.printOption(0, "Exit");


        int opt;
        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 6);

        if (opt == 1) TripManagement();
        if (opt == 2) CustommerRequestManagement();
        if (opt == 3) editProfile(driver);
        if (opt == 4) viewMyFeedback(driver);
        if (opt == 5) buyCredit(driver, 0);
        if (opt == 6) VehiclesManagement();
        if (opt == 0) {
            db.saveDataToFile();
            return;
        }

    }
}
void Application::menu_Passenger() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("ACTIVE DASHBOARD");
        ActiveDashboard(passenger);
        welcomeScreen(passenger);
        ux.printOption(1, "Search and Book");
        ux.printOption(2, "Request Management");
        ux.printOption(3, "Edit my profile");
        ux.printOption(4, "Buy credit");
        ux.printOption(5, "View my feedback");
        ux.printOption(0, "Exit");


        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 5);
        
        if (opt == 1) searchAndBook(passenger);
        else if (opt == 2) RequestManagement();
        else if (opt == 3) editProfile(passenger);
        else if (opt == 4) buyCredit(passenger, 0);
        else if (opt == 5) viewMyFeedback(passenger);
        else if (opt == 0) {
            db.saveDataToFile();
            return;
        }
        else cout << "Invalid option" << endl;
    }
}
void Application::VehiclesManagement() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("VEHICLE MANAGEMENT");
        ux.printOption(1, "Add Vehicle");
        ux.printOption(2, "Delete Vehicle");
        ux.printOption(0, "Back to menu");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 2);
        if (opt == 1) addVehicle();
        if (opt == 2) deleteVehicle();
        if (opt == 0) return;
        pauseDisplay;
    }

}
void Application::RequestManagement() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("REQUEST MANAGEMENT");
        ux.printOption(1, "Cancel my request");
        ux.printOption(2, "History and feedback");
        ux.printOption(0, "Back to menu");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 2);

        if (opt == 1) cancelRequest();
        else if (opt == 2) HistoryAndFeedback();
        else if (opt == 0) return;
        else {
            cout << "Invalid option" << endl;
            return;
        }
    }
}
void Application::CustommerRequestManagement() {
    int opt = -1;

    while (opt != 0) {
        clearDisplay;
        ux.printHeader("REQUEST MANAGEMENT");
        ux.printOption(1, "View Requests");
        ux.printOption(2, "Change status's customer request");
        ux.printOption(0, "Back to menu");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 2);
        if (opt == 0) return;
        else if (opt == 2) {
            changeStatusCustomerRequest();
        }
        else if (opt == 1) {
            clearDisplay;
            ux.printHeader("ALL REQUEST");
            if (driver->getCarpoolWithStatus(1).size() < 1) {
                cout << "Sorry, nothing to show here! " << endl;
                pauseDisplay;
                continue;
            }
            else viewCarpool(driver->getCarpoolWithStatus(1));
            pauseDisplay;
        }
        
    }

}
void Application::TripManagement() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("TRIP MANAGEMENT");
        ux.printOption(1, "Add a Carpool");
        ux.printOption(2, "Cancel a Carpool");
        ux.printOption(3, "Finish a carppol");
        ux.printOption(4, "View History");
        ux.printOption(0, "Back to menu");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 4);

        if (opt == 1) addCarpool();
        else if (opt == 2) cancelACarpool();
        else if (opt == 3) FinishCarpool();
        else if (opt == 4) Carpool_History();
        else if (opt == 0) return;
        pauseDisplay;
    }

}

//preprocessor methods
void Application::viewCarpool(const vector<Trip*>& trips) {
    int index = 1;
    for (const auto& current : trips) {
        cout << index << ": " << "Reference ID: " << current->getReferenceID() << ": " << endl;
        current->showInformation(ux);
        cout << endl;
        index++;
    }
}
string Application::stringFormatSearch(string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    for (auto& it : s) {
        it = tolower(it);
    }
    return s;
}
vector<Trip*> Application::getAvailableCarpools(double myRate, float myCredit) {
    vector<Trip*> tmp;
    for (auto& tmpTrip : db.getTrips()) {
        int trip_minRate = tmpTrip->getMinRate();
        float trip_requireCost = tmpTrip->getCost();
        if ((myRate >= trip_minRate || myRate == -1) && myCredit >= trip_requireCost) {
            if (tmpTrip->getStatus() == 1) {
                tmp.push_back(tmpTrip);
            }
        }
    }
    return tmp;
}
vector<pair<Date, Date>> Application::getTripTime(Driver* driver) {
    vector<pair<Date, Date>> tmp = {};
    for (auto& currentTrip : driver->getCarpoolWithStatus(1)) {
         Date st = currentTrip->getStart();
         Date en = currentTrip->getEnd();
         tmp.push_back(make_pair(st, en));
    }

    return tmp;
}
bool Application::isInsideAnother(Date& x, Date& start, Date& end) {
    return (start <= x) && (x <= end);
}
bool Application::isOverlapTrip(Date& start, Date& end) {
    vector<pair<Date, Date>> allTime = getTripTime(driver);
    for (auto& x : allTime) {
        if (isInsideAnother(start, x.first, x.second)) return true;
        if (isInsideAnother(end, x.first, x.second)) return true;
    }
    return false;
}
vector<string> Application::getAllUsername() {
    vector<string> usernames;
    for (auto& tmp : db.getPassengers()) {
        usernames.push_back(tmp->getUsername());
    }
    for (auto& tmp : db.getDrivers()) {
        usernames.push_back(tmp->getUsername());
    }
    for (auto& tmp : db.getAdmins()) {
        usernames.push_back(tmp->getUsername());
    }
    return usernames;
}
//common
void Application::viewMyFeedback(User* user) {
    clearDisplay;
    // Print the header using UserExperience's method
    ux.printHeader("CUSTOMER'S REVIEW");
    // Display user's basic information
    std::cout << std::left;
    std::cout << "Your Name   : " << user->getFullName() << std::endl;
    std::cout << "Your Rating : " << user->getRateScore() << "/5" << std::endl;
    std::cout << "Comments    :" << std::endl;
    if (user->getFeedback()->getComments().size() < 1) {
        cout << "Nothing to show here! " << endl;
        return;
    }
    // Print each feedback comment
    std::cout << "---------------------------------------------" << std::endl;
    for (const auto& tmp : user->getFeedback()->getComments()) {
        std::cout << std::setw(10) << "User" << ": " << tmp.username << std::endl;
        std::cout << std::setw(10) << "Rating" << ": " << tmp.score << "/5" << std::endl;
        std::cout << std::setw(10) << "Comment" << ": " << tmp.comment << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }
    pauseDisplay;
}
bool Application::doFeedbackUser(string receiver, string myUsername) {
    std::string comment;
    cin.ignore();
    cout << "Your comment on " << receiver << ": " << endl;
    getline(cin, comment);
    string message = "Please rate " + receiver + " (1 to 5) : ";
    int rate = ux.getValidInput<int>(message, &UserExperience::isValidRating);
    

    for (auto& tmpUser : db.getPassengers()) {
        if (tmpUser->getUsername() == receiver) {
            if (!ux.confirmMessage("Send? ")) return 0;
            tmpUser->getFeedback()->addFeedback(myUsername, comment, rate);
            return 1;
        }
    }
    for (auto& tmpUser : db.getDrivers()) {
        if (tmpUser->getUsername() == receiver) {
            if (!ux.confirmMessage("Send? ")) return 0;
            tmpUser->getFeedback()->addFeedback(myUsername, comment, rate);
            return 1;
        }
    }
    return 0;
}
void Application::editProfile(User* user) {
    int opt = -1;
    while (1) {
        clearDisplay;
        ux.printHeader("PROFILE MANAGEMENT");

        string password;
        cout << "Enter your password: ";
        password = ux.getPasswordInput();
        if (password != user->getPassword()) {
            cout << "Incorrect password! Try again!" << endl;
            if (ux.confirmMessage("Exit?")) return;
            continue;
        }
        else {
            break;
        }
    }
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("PROFILE MANAGEMENT");
        user->showInformation(ux);
        ux.printOption(1, "Edit Full Name");
        ux.printOption(2, "Edit Password");
        ux.printOption(3, "Edit Date of Birth");
        ux.printOption(4, "Edit Phone Number");
        ux.printOption(5, "Edit Address");
        ux.printOption(6, "Edit Email");
        ux.printOption(7, "Edit ID Type");
        ux.printOption(8, "Edit ID Number");
        ux.printOption(9, "Edit bank account");
        ux.printOption(10, "Verify Account");
        ux.printOption(0, "Back to memu");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 10);

        if (opt == 0) { return; }
        else if (opt == 1) {
            string newName = ux.getValidInput<string>("Enter your new name: ", &UserExperience::isValidName);

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setFullName(newName);
            cout << "Action done!" << endl;
        }
        else if (opt == 2) {
            string newPassword = ux.getValidInput<string>("Enter your new password: ", &UserExperience::isValidPassword);

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setPassword(newPassword);
            cout << "Action done!" << endl;
        }
        else if (opt == 3) {
            int dd, mm, yyyy;
            cout << "Enter your day of birth ";
            cin >> dd;
            cout << "Enter your month of birth ";
            cin >> mm;
            cout << "Enter your year of birth ";
            cin >> yyyy;
            Date newDOB(-1, -1, -1, dd, mm, yyyy);          // need fix

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setDOB(newDOB);
            cout << "Action done!" << endl;
        }
        else if (opt == 4) {
            string newPhoneNumber = ux.getValidInput<string>("Enter your new phone number: ", &UserExperience::isValidPhoneNumber);

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setPhoneNumber(newPhoneNumber);
            cout << "Action done!" << endl;
        }
        else if (opt == 5) {
            string newAddress = ux.getValidInput<string>("Enter your new address: ", &UserExperience::isValidLocation);         // need more config


            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setAddress(newAddress);
            cout << "Action done!" << endl;
        }
        else if (opt == 6) {
            string newEmail = ux.getValidInput<string>("Enter your new phone email: ", &UserExperience::isValidEmail);
         
            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setEmail(newEmail);
            cout << "Action done!" << endl;
        }
        else if (opt == 7) {
            string newIDType;
            cout << "Enter your new ID type: ";
            ux.printOption(1, "Passport");
            ux.printOption(2, "Identity Card");
            ux.printOption(0, "Exit");

            int opt = ux.getValidInput<int>("Enter your new type: ", &UserExperience::isValidOption, 0, 2);
            string number;
            if (opt == 1) {
               newIDType = "Passport";
               number = ux.getValidInput<string>("Enter your Passport number: ", &UserExperience::isValidPassportNumber);
            }
            else if(opt == 2) {
                newIDType = "Idenity Card";
                number = ux.getValidInput<string>("Enter your Identity card number: ", &UserExperience::isValidIdentityNumber);
            }
            else {
                break;
            }
            
            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) {
                user->setIdType(newIDType);
                user->setIdNumber(number);
            }
            cout << "Action done!" << endl;
        }
        else if (opt == 8) {
            string newIDNumber;

            if (user->getIdType() == "Passport") {
                newIDNumber = ux.getValidInput<string>("Enter your new Passport number: ", &UserExperience::isValidPassportNumber);
            }
            else{
                newIDNumber = ux.getValidInput<string>("Enter your new Identity card number: ", &UserExperience::isValidIdentityNumber);
            }
            
            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) user->setIdNumber(newIDNumber);
            cout << "Action done!" << endl;
        }
        else if (opt == 9) {
            // Assuming you have a function to edit bank account info
            string bankAccountName = ux.getValidInput<string>("Enter bank account name: ", &UserExperience::isValidName);
            string bankAccountNumber = ux.getValidInput<string>("Enter bank account number: ", &UserExperience::isValidCardNumber);
            double accountBalance = 1000;
            Date expireDate;
            while (1) {
                int month = ux.getValidInput<int>("Enter bank account month of expiration : ", &UserExperience::isValidOption, 1, 12);
                int year = ux.getValidInput<int>("Enter bank account year of expiration : ", &UserExperience::isValidOption, 2025, 2100);
                expireDate = Date(-1, -1, -1, -1, month, year);
                if (ux.isValidDateTrip(expireDate)) break;
                else {
                    cout << "Invalid date!" << endl;
                }
            }
            int CVV = ux.getValidInput<int>("Enter CVV code: ", &UserExperience::isValidCVV);

            bool isConfirm = ux.confirmMessage("Do you want to save changes?");
            if (isConfirm) {
                BankAccount* newAccount = new BankAccount();
                newAccount->setBankAccountName(bankAccountName);
                newAccount->setBankAccountNumber(bankAccountNumber);
                newAccount->setCVV(CVV);
                newAccount->setExpireDate(expireDate);
                newAccount->setAccountBalance(99999);
                user->setBankAccount(newAccount);

            }
            cout << "Action done!" << endl;
        }
        else if (opt == 10) {
            bool isConfirm = ux.confirmMessage("Do you want to verify your account?");
            if (isConfirm) user->verifyAccount();
            cout << "Account verified!" << endl;
        }
        else {
            cout << "Invalid option selected!" << endl;
        }
        pauseDisplay;
    }

}
void Application::buyCredit(User* user, bool isFirstTime) {
    ux.printHeader("CREDIT STORE");

    float buyAmount;
    if (isFirstTime) {
        buyAmount = 10.0;
        cout << "Entry fee is " << buyAmount << endl;
        if (user->getBankAccount()->getAccountBalance() < buyAmount) {
            cout << "Your balance is insufficient! " << endl;
            pauseDisplay;
            return;
        }
        user->receiveCredit(buyAmount);
        user->getBankAccount()->setAccountBalance(user->getBankAccount()->getAccountBalance() - buyAmount);
        return;
    }

    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("CREDIT STORE");
        cout << "You credit: " << user->getCreditPoint() << endl;
        ux.printOption(1, "Buy Credit");
        ux.printOption(0, "Back to menu");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 1);

        if (opt == 0) return;
        else {
            buyAmount = ux.getValidInput<float>("Enter the credit amount:", &UserExperience::isValidRange);

            if (user->getBankAccount()->getAccountBalance() < buyAmount) {
                cout << "Your balance is insufficient! " << endl;
                pauseDisplay;
                continue;
            }
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(2) << buyAmount;
            std::string formattedAmount = stream.str();

            std::string s = "Do you want to use $" + formattedAmount + " to purchase " + formattedAmount + " credit? ";
            if (ux.confirmMessage(s)) {
                user->receiveCredit(buyAmount);
                user->getBankAccount()->setAccountBalance(user->getBankAccount()->getAccountBalance() - buyAmount);
                cout << "Transaction done! " << endl;
            }
            else {
                cout << "Cancel transaction! " << endl;
            }

        }
        pauseDisplay;
    }

}
void Application::ActiveDashboard(Driver* driver) {

    vector<Trip*> trips = driver->getCarpoolWithStatus(1);
    cout << " >>> Your active carpools" << endl;
    showActiveCarpool(trips);
    cout << endl << endl;

}
void Application::ActiveDashboard(Passenger* passenger) {

    vector<Trip*> trips = getAvailableCarpools(passenger->getRateScore(), passenger->getCreditPoint());
    cout << " >>> Active carpools: " << endl;
    showActiveCarpool(trips);
    cout << endl << endl;
    cout << " >>> My active bookings: " << endl;
    trips.clear();
    for (auto& tmp : passenger->getTripByStatus(1)) {
        for (auto& pass : tmp->getPassengers()) {
            if (pass.first == passenger->getUsername() && pass.second == 1) {
                trips.push_back(tmp);
                break;
            }
        }
    }
    showActiveCarpool(trips);
    cout << endl << endl;


}

void Application::showActiveCarpool(vector<Trip*> trips) {
    int id = 1;
    for (const auto& tmp : trips) {
        std::ostringstream oss;

        // Set a fixed width and align text to the left
        oss << "Reference ID: " << std::left << std::setw(10) << tmp->getReferenceID()
            << " | Time: " << std::left << std::setw(15) << tmp->getStart().toString()
            << " -> " << std::left << std::setw(15) << tmp->getEnd().toString()
            << " | From: " << std::left << std::setw(13) << tmp->getStartLocation()
            << " -> " << std::left << std::setw(13) << tmp->getEndLocation();

        ux.printOption(id, oss.str());
        id++;
    }
}
//passsenger
void Application::searchAndBook(User* user) {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("Search and Book");
        ux.printOption(1, "Search by dept location");
        ux.printOption(2, "Search by dest location");
        ux.printOption(3, "Search by start date");
        ux.printOption(4, "Search by end date");
        ux.printOption(0, "Exit");

        opt = ux.getValidInput<int>("Enter your option: ", &UserExperience::isValidOption, 0, 4);
        if (opt == 0) break;
        else if (opt == 1) {
            string dept;
            cout << "Enter depature location: " << endl;
            getline(cin >> ws, dept);
            searchByDeparture(user, dept, 0);
        }
        else if (opt == 2) {
            cout << "Enter destination location: " << endl;
            string dest;
            getline(cin >> ws, dest);
            searchByDestination(user, dest, 0);
        }
        else if (opt == 3) {
            int dd = ux.getValidInput<int>("Enter date: ", &UserExperience::isValidOption, 1, 31);
            int mm = ux.getValidInput<int>("Enter month: ", &UserExperience::isValidOption, 1, 12);
            searchByStartDate(user, dd, mm, 0);
        }

        else if (opt == 4) {
            int dd = ux.getValidInput<int>("Enter date: ", &UserExperience::isValidOption, 1, 31);
            int mm = ux.getValidInput<int>("Enter month: ", &UserExperience::isValidOption, 1, 12);
            searchByEndDate(user, dd, mm, 0);
        }
    }

}
void Application::searchByDeparture(User* user, string departureLocation, int isGuest) {
    
        int index = 1;
        vector<Trip*> tmpTrip;
        for (auto& it : getAvailableCarpools(user->getRateScore(), user->getCreditPoint())) {
            string dept = stringFormatSearch(it->getStartLocation());
            string substr = stringFormatSearch(departureLocation);
            bool isFound = (dept.find(substr) != string::npos);
            if (isFound) tmpTrip.push_back(it);
        }
        if (tmpTrip.size() < 1) {
            cout << "Sorry! We could not find a match!" << endl;
            pauseDisplay;
            return;
        }
        viewCarpool(tmpTrip);

        if (userType == "guest") {
            cout << "To book carpool, please REGIESTER AS MEMBER! UNLIMNITED ACCESS! " << endl;
            if (!ux.confirmMessage("REGIESTER? ")) return;
            createNewAccount();
            return;
        }
        if (passenger) {
            int opt = ux.getValidInput<int>("Enter the trip's index: ( '0' to exit )", &UserExperience::isValidOption, 0, (int)tmpTrip.size());
            if (opt <= 0) return;

            if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + tmpTrip[opt - 1]->getReferenceID() + "?")) return;
            passenger->bookACarPool(tmpTrip[opt - 1]);

            pauseDisplay;
        }
    
}
void Application::searchByDestination(User* user, string destinationLocation, int isGuest) {
    if (!isGuest) {
        int index = 1;
        vector<Trip*> tmpTrip;
        for (auto& it : getAvailableCarpools(user->getRateScore(), user->getCreditPoint())) {
            string dept = stringFormatSearch(it->getEndLocation());
            string substr = stringFormatSearch(destinationLocation);
            bool isFound = (dept.find(substr) != string::npos);
            if (isFound) tmpTrip.push_back(it);
        }
        if (tmpTrip.size() < 1) {
            cout << "Sorry! We could not find a match!" << endl;
            pauseDisplay;
            return;
        }
        viewCarpool(tmpTrip);
        if (userType == "guest") {
            cout << "To book carpool, please REGIESTER AS MEMBER! UNLIMNITED ACCESS! " << endl;
            if (!ux.confirmMessage("REGIESTER? ")) return;
            createNewAccount();
            return;
        }
        if (passenger) {
            int opt = ux.getValidInput<int>("Enter the trip's index : ", &UserExperience::isValidOption, 1, (int)tmpTrip.size());
            if (opt <= 0) return;

            if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + tmpTrip[opt - 1]->getReferenceID() + "?")) return;
            passenger->bookACarPool(tmpTrip[opt - 1]);

            pauseDisplay;
        }
        
    }
}
void Application::searchByStartDate(User* user, int dd, int mm, int isGuest) {
    if (!isGuest) {
        vector<Trip*> tmpTrips;
        int index = 1;
        for (auto& it : getAvailableCarpools(user->getRateScore(), user->getCreditPoint())) {
            if (it->getStart().getDay() == dd && it->getStart().getMonth() == mm) tmpTrips.push_back(it);
        }
        if (tmpTrips.size() < 1) {
            cout << "Sorry! We could not find a match!" << endl;
            pauseDisplay;
            return;
        }
        viewCarpool(tmpTrips);
        if (userType == "guest") {
            cout << "To book carpool, please REGIESTER AS MEMBER! UNLIMNITED ACCESS! " << endl;
            if (!ux.confirmMessage("REGIESTER? ")) return;
            createNewAccount();
            return;
        }
        if (passenger) {
            int opt = ux.getValidInput<int>("Enter the trip's index: ( '0' to exit )", &UserExperience::isValidOption, 0, (int)tmpTrips.size());
            if (opt <= 0) return;
            if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + tmpTrips[opt - 1]->getReferenceID() + "?")) return;
            passenger->bookACarPool(tmpTrips[opt - 1]);
            pauseDisplay;
        }
    }

}
void Application::searchByEndDate(User* user, int dd, int mm, int isGuest) {
    if (!isGuest) {
        vector<Trip*> tmpTrips;
        int index = 1;
        for (auto& it : getAvailableCarpools(user->getRateScore(), user->getCreditPoint())) {
            if (it->getEnd().getDay() == dd && it->getEnd().getMonth() == mm) tmpTrips.push_back(it);
        }
        if (tmpTrips.size() < 1) {
            cout << "Sorry! We could not find a match!" << endl;
            pauseDisplay;
            return;
        }
        viewCarpool(tmpTrips);
        if (userType == "guest") {
            cout << "To book carpool, please REGIESTER AS MEMBER! UNLIMNITED ACCESS! " << endl;
            if (!ux.confirmMessage("REGIESTER? ")) return;
            createNewAccount();
        }
        if (passenger) {
            int opt = ux.getValidInput<int>("Enter the trip's index : ", &UserExperience::isValidOption, 1, (int)tmpTrips.size());
            if (opt <= 0) return;

            if (!ux.confirmMessage("Do you want to book carpool: Reference ID:  " + tmpTrips[opt - 1]->getReferenceID() + "?")) return;
            passenger->bookACarPool(tmpTrips[opt - 1]);
            pauseDisplay;
        }
    }

}
void Application::HistoryAndFeedback() {
    vector<Trip*> unratedTrips;
    for (auto& tmp : passenger->getTripByStatus(2)) {
        for (const auto& currentPassenger : tmp->getPassengers()) {
            if (currentPassenger.first == passenger->getUsername() && currentPassenger.second == 1) {
                unratedTrips.push_back(tmp);
                break;
            }
        }
    }
    if (unratedTrips.size() < 1) {
        cout << "Sorry! Nothing to show here!" << endl;
        pauseDisplay;
        return;
    }
    viewCarpool(unratedTrips);
    int index = ux.getValidInput<int>("Enter the trip's index: ( '0' to exit )", &UserExperience::isValidOption, 0, (int)unratedTrips.size());
    if (index <= 0) return;
    
    Trip* currentTrip = unratedTrips[index - 1];
    if (!ux.confirmMessage("Do you want to feedback this trip: Reference ID: " + currentTrip->getReferenceID() + "?")) return;
    if (!doFeedbackUser(currentTrip->getDriver(), passenger->getUsername())) return;
    currentTrip->setPassengerStatus(passenger->getUsername(), 3);
    cout << "Thank you using our services! " << endl;
    pauseDisplay;

}
void Application::cancelRequest() {
    int opt = -1;
    while (opt != 0) {
        clearDisplay;
        ux.printHeader("CANCEL REQUEST");
        ux.printOption(1, "Cancel pending request");
        ux.printOption(2, "Cancel denied requests");
        ux.printOption(0, "Exit");

        opt = ux.getValidInput<int>("Enter your option : ", &UserExperience::isValidOption, 0, 2);


        if (opt == 0) return;
        else if (opt == 1) {
            vector<Trip*> tmpTrips = passenger->getTripByStatus(0);
            if (tmpTrips.size() < 1) {
                cout << "Nothing to show here! " << endl;
                pauseDisplay;
                continue;
            }
            viewCarpool(tmpTrips);

            int opt2 = ux.getValidInput<int>("Enter your trip's index( '0' to exit) : ", &UserExperience::isValidOption, 0, (int)tmpTrips.size());

            if (opt2 <= 0) continue;
            if (!ux.confirmMessage("Do you want to cancel this request " + tmpTrips[opt2 - 1]->getReferenceID() + "?")) continue;
            passenger->cancelRequest(tmpTrips[opt2 - 1], 0);
            cout << "Request canceled ! " << endl;
        }
        else if (opt == 2) {
            vector<Trip*> tmpTrips;
            for (auto& tmp : passenger->getTripByStatus(1)) {
                for (auto pass : tmp->getPassengers()) {
                    if (pass.first == passenger->getUsername() && pass.second == 2) {
                        tmpTrips.push_back(tmp);
                        break;
                    }
                }
            }
            if (tmpTrips.size() < 1) {
                cout << "Nothing to show here! " << endl;
                pauseDisplay;
                continue;
            }
            viewCarpool(tmpTrips);

            int opt2 = ux.getValidInput<int>("Enter your trip's index( '0' to exit) : ", &UserExperience::isValidOption, 0, (int)tmpTrips.size());

            if (opt2 <= 0) continue;
            if (!ux.confirmMessage("Do you want to cancel this request " + tmpTrips[opt2 - 1]->getReferenceID() + "?")) continue;
            passenger->cancelRequest(tmpTrips[opt2 - 1], 2);
            cout << "Request canceled ! " << endl;

        }
        pauseDisplay;



    }

}

//drivers
void Application::addCarpool() {
    
    int minRate;
    float cost;
    Date startDate, endDate;

    while (1) {
        clearDisplay;
        ux.printHeader("CREATE NEW CARPOOL");
        ux.printOption(1, "Depature Time Detail");
        int hh = ux.getValidInput<int>("Enter the hour: ", &UserExperience::isValidOption, 0, 24);
        int mm = ux.getValidInput<int>("Enter the minute: ", &UserExperience::isValidOption, 0, 60);
        int dd = ux.getValidInput<int>("Enter the day: ", &UserExperience::isValidOption, 1, 31);
        int mmmm = ux.getValidInput<int>("Enter the month: ", &UserExperience::isValidOption, 1, 12);
        int yyyy = ux.getValidInput<int>("Enter the year: ", &UserExperience::isValidOption, 0, 2100);
        ux.printOption(2, "End Time Detail");
        int hh2 = ux.getValidInput<int>("Enter the hour: ", &UserExperience::isValidOption, 0, 24);
        int mm2 = ux.getValidInput<int>("Enter the minute: ", &UserExperience::isValidOption, 0, 60);
        int dd2 = ux.getValidInput<int>("Enter the day: ", &UserExperience::isValidOption, 1, 31);
        int mmmm2 = ux.getValidInput<int>("Enter the month: ", &UserExperience::isValidOption, 1, 12);
        int yyyy2 = ux.getValidInput<int>("Enter the year: ", &UserExperience::isValidOption, 0, 2100);

        startDate = Date(hh, mm, -1, dd, mmmm, yyyy);
        endDate = Date(hh2, mm2, -1, dd2, mmmm2, yyyy2);
        if (!ux.isValidDateTrip(startDate)) {
            cout << "Invalid date type!" << endl;
            pauseDisplay;
            continue;
        }
        if (!ux.isValidDateTrip(endDate)) {
            cout << "Invalid date type!" << endl;
            pauseDisplay;
            continue;
        }
        if (endDate <= startDate) {
            cout << "start Time < endTime" << endl;
            pauseDisplay;
            continue;
        }
        if (isOverlapTrip(startDate, endDate)) {
            cout << "Overlapping with other(s)!" << endl;
            pauseDisplay;
            continue;
        }
        

        break;
    }
    string startLocation = ux.getValidInput<string>("Enter start location: ", &UserExperience::isValidLocation);
    string endLocation = ux.getValidInput<string>("Enter end location: ", &UserExperience::isValidLocation);
    string referenceID;
    referenceID = ux.ReferenceIDGenerator(startDate);
    minRate = ux.getValidInput<int>("Enter min rate: ", &UserExperience::isValidRatingScore);
    cost = ux.getValidInput<float>("Enter the required credit amount: ", &UserExperience::isValidRange);

    driver->viewVehicle(ux);
    int carID = ux.getValidInput<int>("Enter your vehicle's index( '0' to exit) ", &UserExperience::isValidOption, 0, (int)driver->getDriverVehicles().size());
    if (carID == 0) return;

    if (!ux.confirmMessage("Do you want to add a new carpool? ")) return;
    Trip* tmpTrip = new Trip();
    Vehicle* currentCar = driver->getDriverVehicles()[carID - 1];
    tmpTrip->setDriverP(driver);
    tmpTrip->setStatus(1);
    tmpTrip->setDriver(driver->getUsername());
    tmpTrip->setVehicle(currentCar->getPlateNumber());
    tmpTrip->setAvailableSeat(currentCar->getTotalSeat());
    tmpTrip->setStart(startDate);
    tmpTrip->setEnd(endDate);
    tmpTrip->setStartLocation(startLocation);
    tmpTrip->setEndLocation(endLocation);
    tmpTrip->setReferenceID(referenceID);
    tmpTrip->setMinRate(minRate);
    tmpTrip->setCost(cost);
    tmpTrip->setDriverP(driver);
    tmpTrip->setVehicleP(currentCar);
    driver->addActiveTrip(tmpTrip);
    db.addTrip(tmpTrip);      // add to database

    cout << "New Carpool added!" << endl;
}
void Application::cancelACarpool() {
    clearDisplay;
    ux.printHeader("CANCEL A CARPOOL");
    vector<Trip*> trips;
    for (auto& tmp : driver->getCarpoolWithStatus(1)) {
        if (tmp->getPassengers().size() == 0) trips.push_back(tmp);
        else {
            bool isOnlyDenied = true;
            for (auto& tmpPass: tmp->getPassengers()) {
                if (tmpPass.second != 2) {
                    isOnlyDenied = false;
                    break;
                }
            }
            if (isOnlyDenied) trips.push_back(tmp);
        }
    }
    if ((int)trips.size() < 1) {
        cout << "Sorry! Nothing to show here! " << endl;
        return;
    }
    viewCarpool(trips);
    int index = ux.getValidInput<int>("Enter your trip's index( '0' to exit) : ", &UserExperience::isValidOption, 0, (int)trips.size());
    if (index == 0) return;

    Trip* currentTrip = trips[index - 1];
    for (const auto& tmp : currentTrip->getPassengers()) {
        if (tmp.second == 1 || tmp.second == 0) {
            cout << "Sorry, can not cancel this carpool!" << endl;
            return;
        }
    }
    if (!ux.confirmMessage("Do you want to cancel carpool with Reference ID:" + currentTrip->getReferenceID() + "?")) return;
    currentTrip->setStatus(2);
    cout << "Carpool deleted! " << endl;

}
void Application::Carpool_History() {
    clearDisplay;
    ux.printHeader("CARPOOL HISTORY");
    if ((int)driver->getCarpoolWithStatus(2).size() < 1) {
        cout << "Sorry! Nothing to show here! " << endl;
        return;
    }
    viewCarpool(driver->getCarpoolWithStatus(2));     // need fix
}
void Application::FinishCarpool() {
    clearDisplay;
    ux.printHeader("FINSIH CARPOOL");
    vector<Trip*> trips;
    for (auto& tmp : driver->getCarpoolWithStatus(1)) {
        for (auto& tmpPass : tmp->getPassengers()) {
            if (tmpPass.second == 1) {
                trips.push_back(tmp);
                break;
            }
        }
    }
    if ((int)trips.size() < 1) {
        cout << "Sorry! Nothing to show here! " << endl;
        return;
    }
    viewCarpool(trips);

    int tripIndex = ux.getValidInput<int>("Enter your trip's index( '0' to exit) : ", &UserExperience::isValidOption, 0, (int)trips.size());
    if (tripIndex == 0) return;

    Trip* currenTrip = trips[tripIndex - 1];
    if (!ux.confirmMessage("Do you to finish carpool with Reference ID: " + currenTrip->getReferenceID() + "?")) return;

    if (currenTrip->getPassengers().size() < 1) {
        cout << "Cannot finish this trip!" << endl;
        return;
    }
    for (auto& tmp : currenTrip->getPassengers()) {
        if (tmp.second == 0) {
            cout << "Cannot finish this trip!" << endl;
            return;
        }
    }
    cout << "Passenger: " << endl;
    for (auto& tmp : currenTrip->getPassengers()) {
        cout << tmp.first << endl;
        if (tmp.second == 1) doFeedbackUser(tmp.first, driver->getUsername());
    }

    float amount = currenTrip->getTotalCredit();
    cout << "Receive + " << amount << " to your account!" << endl;
    driver->receiveCredit(amount);
    driver->changeStatusCarpool(tripIndex, 2);
    cout << "Changes saved! " << endl;


}
void Application::addVehicle() {
    clearDisplay;
    ux.printHeader("FILL IN THE FORM");

    string model = ux.getValidInput<string>("Enter the vehicel's brand: ", &UserExperience::isValidVehicleModel);
    string color = ux.getValidInput<string>("Enter the vehicle's color: ", &UserExperience::isValidColor);
    string plateNumber = ux.getValidInput<string>("Enter the vehicle's plate: ", &UserExperience::isValidPlateNumber);
    int seats = ux.getValidInput<int>("Enter the vehicle' seat number: ", &UserExperience::isValidSeatNumber);

    for (const auto& tmp : db.getVehicles()) {
        if (tmp->getPlateNumber() == plateNumber && tmp->getStatus() == 1) {
            cout << "Sorry! This vehicles has already added! ";
            return;
        }
    }

    Vehicle* tmpVehicle = new Vehicle();
    tmpVehicle->setOwner_username(driver->getUsername());
    tmpVehicle->setModel(model);
    tmpVehicle->setColor(color);
    tmpVehicle->setPlateNumber(plateNumber);
    tmpVehicle->setTotalSeat(seats);
    tmpVehicle->setStatus(1);

    cout << "Preview: " << endl;
    tmpVehicle->showInformation(ux);
    if (!ux.confirmMessage("Do you want to add vehicle? ")) return;
    driver->addVehicle(tmpVehicle);
    db.addVehicle(tmpVehicle);
    cout << "Add vehicle successfully!" << endl;

}
void Application::deleteVehicle() {
    clearDisplay;
    int index = 1;
    vector<Vehicle*> vehicles;
    for (auto& tmp : driver->getDriverVehicles()) {
        if (tmp->getStatus() == 1) {
            cout << endl;
            ux.printOption(index, tmp->getModel());
            tmp->showInformation(ux);
            vehicles.push_back(tmp);
            index++;
        }
    }

    int vehicleIndex = ux.getValidInput<int>("Enter the vehicle' index: ( '0' to exit) : ", &UserExperience::isValidOption, 0, (int)vehicles.size());
    if (vehicleIndex == 0) return;

    Vehicle* currentVehicle = vehicles[vehicleIndex - 1];
    if (!ux.confirmMessage("Do you want to remove vehicle with Plate number: " + currentVehicle->getPlateNumber() + "?")) return;
    currentVehicle->setStatus(0);
    cout << "Vehicle removed! " << endl;
    pauseDisplay;

}
void Application::changeStatusCustomerRequest() {
    clearDisplay;
    ux.printHeader("CUSTOMER REQUEST");

    vector<Trip*> trips;
    for (auto& tmpTrip: driver->getCarpoolWithStatus(1)) {
        for (auto& tmpPassenger : tmpTrip->getPassengers()) {
            if (tmpPassenger.second == 0) {
                trips.push_back(tmpTrip);
                break;
            }
        }
    }
    if (trips.size() <= 0) {
        cout << "Sorry! Nothing to show here!" << endl;
        pauseDisplay;
        return;
    }
    viewCarpool(trips);

    int tripID = ux.getValidInput<int>("Enter the trip's index: ( '0' to exit ): ", &UserExperience::isValidOption, 0, (int)trips.size());
    if (tripID <= 0) return;

    Trip* currentTrip = trips[tripID - 1];

    cout << "Enter the passenger id: ";
    int passID = ux.getValidInput<int>("Enter the passenger's index: ( '0' to exit ): ", &UserExperience::isValidOption, 0, (int)currentTrip->getPassengers().size());
    ux.printOption(1, "Accept Request");
    ux.printOption(2, "Deny Request");
    int value = ux.getValidInput<int>("Enter new status: ", &UserExperience::isValidOption, 1, 2);

    if (currentTrip->getPassengers().size() < 1 || currentTrip->getPassengers()[passID - 1].second == 1) {
        cout << "Sorry! Can not change status of customer" << endl;
        pauseDisplay;
        return;
    }

    cout << "Preview: " << endl;
    cout << "Trip Refernce ID:" << currentTrip->getReferenceID() << endl;
    string status = ((value == 1) ? "Accepted" : "Denied");
    cout << "New status of passenger " << currentTrip->getPassengers()[passID - 1].first << ": Pending" << " --> " << status << endl;
    if (!ux.confirmMessage("Do you want to save changes? ")) return;

    driver->changeStatusOfPassengerInTrip(currentTrip, passID - 1, value);
    if (value == 1) currentTrip->setAvailableSeat(currentTrip->getAvailableSeat() - 1);
    if (value == 2) {
        for (auto& tmp : db.getPassengers()) {
            if (tmp->getUsername() == currentTrip->getPassengers()[passID - 1].first) {
                tmp->setCreditPoint(tmp->getCreditPoint() + currentTrip->getCost());
            }
        }
    }
    
    cout << "Passenger request updated! " << endl;
    pauseDisplay;

}
