#pragma once
#include <string>
#include<iostream>
#include "Date.h"
#include "BankAccount.h"
#include "IdentityCard.h"
#include "Feedback.h"
#include "UserExperience.h"
#include<iomanip>
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
    void setFeedback(Feedback* feedback);

    // Member functions
    void receiveCredit(float creditAmount);
    void useCredit(float creditAmount);
    void showInformation(UserExperience& ux) const;

};
