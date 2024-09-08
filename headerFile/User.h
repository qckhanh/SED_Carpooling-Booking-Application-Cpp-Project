#pragma once
#include <string>
#include<iostream>
#include "Date.h"
#include "BankAccount.h"
#include "IdentityCard.h"
#include "Feedback.h"
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
    BankAccount* bankAccount; 
    IdentityCard* card;
    Feedback* feedbacks;


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
    BankAccount* getBankAccount();
    IdentityCard* getCard();
    double getRateScore();
    Feedback* getFeedback();


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
    void setBankAccount(BankAccount* bankAccount);
    void setCard(IdentityCard* card);
    void setFeedback(Feedback* feedback);

    // Member functions
    void search();
    void rating();
    void verifyAccount();
    void manageInfo();
    void receiveCredit(float creditAmount);
    void useCredit(float creditAmount);
    void showInformation() const {

        cout << "Profile Information: " << endl;
        cout << "---------------------------------" << endl;
        cout << "Full Name     : " << fullName << endl;
        cout << "Username      : " << username << endl;
        cout << "Password      : " << password << endl;
        cout << "Date of Birth : " << DOB.getDay() << "/" << DOB.getMonth() << "/" << DOB.getYear() << endl;
        cout << "Phone Number  : " << phoneNumber << endl;
        cout << "Address       : " << address << endl;
        cout << "Email         : " << email << endl;
        cout << "ID Type       : " << idType << endl;
        cout << "ID Number     : " << idNumber << endl;
        cout << "Credit Points : " << creditPoint << endl;
        cout << "Verified      : " << (isVerified ? "Yes" : "No") << endl;
        // Uncomment the following lines when you implement the toString methods
        // cout << "Bank Account  : " << bankAccount->toString() << endl;
        // cout << "Identity Card : " << card->toString() << endl;
        cout << "---------------------------------" << endl;


    }
};
