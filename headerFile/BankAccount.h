#pragma once
#include <string>

class BankAccount {
    private:
        std::string bankAccountName;
        std::string bankAccountNumber;
        int CVV;
        double accountBalance;
        //Date expireDate;

    public:
        //Constructor
        BankAccount();

        //Destructor
        ~BankAccount();

        //Getter methods
        std::string getBankAccountName() const;
        std::string getBankAccountNumber() const;
        int getCVV() const;
        double getAccountBalance() const;
        //Date getExpireDate() const;

        //Setter methods
        void setBankAccountName(const std::string& bankAccountName);
        void setBankAccountNumber(const std::string& bankAccountNumber);
        void setCVV(const int& CVV);
        void setAccountBalance(const double& accountBalance);
        //void setExpireDate(const Date& expireDate);
};
