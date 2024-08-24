#pragma once
#include <string>
#include "Date.h"
#include "BankAccount.h"
#include "IdentityCard.h"
#include<iostream>
using namespace std;
class User {
protected:
    std::string username;
    std::string password;
    std::string fullName;
    Date DOB; 
    std::string phoneNumber;
    std::string address;
    std::string email;
    std::string idType;
    std::string idNumber;
    float creditPoint;
    bool isVerified;
    BankAccount bankAccount; 
    IdentityCard card; 

public:
    // Constructor
    User();

    // Destructor
    virtual ~User();

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    Date getDOB() const;
    std::string getPhoneNumber() const;
    std::string getAddress() const;
    std::string getEmail() const;
    std::string getIdType() const;
    std::string getIdNumber() const;
    float getCreditPoint() const;
    bool getIsVerified() const;
    BankAccount getBankAccount() const;
    IdentityCard getCard() const;

    // Setters
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setFullName(const std::string& fullName);
    void setDOB(const Date& DOB);
    void setPhoneNumber(const std::string& phoneNumber);
    void setAddress(const std::string& address);
    void setEmail(const std::string& email);
    void setIdType(const std::string& idType);
    void setIdNumber(const std::string& idNumber);
    void setCreditPoint(float creditPoint);
    void setIsVerified(bool isVerified);
    void setBankAccount(const BankAccount& bankAccount);
    void setCard(const IdentityCard& card);

    // Member functions
    void search();
    void rating();
    void verifyAccount();
    void manageInfo();
    void toString() const {

        cout << "Full Name: " << fullName << "\n";
        cout << "Username: " << username << "\n";
        cout << "Password: " << password << "\n";
        cout << "Date of Birth: " << DOB.getDay() << DOB.getMonth() << DOB.getYear() << "\n";
        cout << "Phone Number: " << phoneNumber << "\n";
        cout << "Address: " << address << "\n";
        cout << "Email: " << email << "\n";
        cout << "ID Type: " << idType << "\n";
        cout << "ID Number: " << idNumber << "\n";
        cout << "Credit Point: " << creditPoint << "\n";
        cout << "Verified: " << (isVerified ? "Yes" : "No") << "\n";
            //<< "Bank Account: " << bankAccount.toString() << "\n"
            //<< "Identity Card: " << card.toString() << "\n";

    }
};
