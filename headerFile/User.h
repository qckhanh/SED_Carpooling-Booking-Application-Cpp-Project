#pragma once
#include <string>
#include "Date.h"
#include "BankAccount.h"
#include "IdentityCard.h"
#include<iostream>
#include "../Carpooling/Feedback.h"
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
    Feedback feedbacks;


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
    double getRateScore();


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
    void setFeedback(const Feedback& feedback);

    // Member functions
    void search();
    void rating();
    void verifyAccount();
    void manageInfo();
    void toString() const {

        cout << "Full Name: " << fullName << " -- ";
        cout << "Username: " << username << " -- ";
        cout << "Password: " << password << " -- ";
        cout << "Date of Birth: " << DOB.getDay() << DOB.getMonth() << DOB.getYear() << " -- ";
        cout << "Phone Number: " << phoneNumber << " -- ";
        cout << "Address: " << address << " -- ";
        cout << "Email: " << email << " -- ";
        cout << "ID Type: " << idType << " -- ";
        cout << "ID Number: " << idNumber << " -- ";
        cout << "Credit Point: " << creditPoint << " -- ";
        cout << "Verified: " << (isVerified ? "Yes" : "No") <<endl;
            //<< "Bank Account: " << bankAccount.toString() << "\n"
            //<< "Identity Card: " << card.toString() << "\n";

    }
};
