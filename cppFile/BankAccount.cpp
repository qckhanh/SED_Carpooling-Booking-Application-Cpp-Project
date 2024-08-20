#include "../headerFile/BankAccount.h"
#include <string>

//Constructor
BankAccount::BankAccount(): bankAccountName(""), bankAccountNumber(""), CVV(0), accountBalance(0) {}

//Destructor
BankAccount::~BankAccount() {};

//Getter methods
std::string BankAccount::getBankAccountName() const { return bankAccountName; }
std::string BankAccount::getBankAccountNumber() const { return bankAccountNumber; }
int BankAccount::getCVV() const { return CVV; }
double BankAccount::getAccountBalance() const { return accountBalance; }
//Date BankAccount::getExpireDate() const { return expireDate; }

//Setter methods
void BankAccount::setBankAccountName(const std::string& bankAccountName) { this->bankAccountName = bankAccountName; }
void BankAccount::setBankAccountNumber(const std::string& bankAccountNumber) { this->bankAccountNumber = bankAccountNumber; }
void BankAccount::setCVV(const int& CVV) {this->CVV = CVV;}
void BankAccount::setAccountBalance(const double& accountBalance) { this-> accountBalance = accountBalance;}
//void BankAccount::setExpireDate(const Date& expireDate) { this->expireDate = expireDate; }
