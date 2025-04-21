#include <memory>

#include "Account.h"

namespace banking {
// internal implementation of IAccount
class Account : public IAccount {
  public:
    Account(double balance); // conversion constructor
    Account(int id, double balance);

    operator double() const; // conversion operator

    // IAccount interface
    int getId() const;
    double getBalance() const;
    void deposit(double amount);
    void withdraw(double amount);

  protected:
    int id;
    double balance;
};

// internal implementation of ISavingsAccount
class SavingsAccount final : public Account, public ISavingsAccount {
  public:
    SavingsAccount(int id, double balance, double interestRate);

    void applyInterest();

  private:
    double interestRate;
};

// factory function to create an account
std::shared_ptr<IAccount> createAccount(int id, double balance) { std::make_shared<Account>(id, balance); }

// factory function to create a savings account
std::shared_ptr<ISavingsAccount> createSavingsAccount(int id, double balance, double interestRate) {
    return std::make_shared<SavingsAccount>(id, balance, interestRate);
}

// constructors and operators for Account
Account::Account(double balance) : Account(0, balance) {}
Account::Account(int id, double balance) : id{id}, balance{balance} {}
Account::operator double() const { return balance; }

// interface methods for Account
int Account::getId() const { return id; }
double Account::getBalance() const { return balance; }
void Account::deposit(double amount) { balance += amount; }
void Account::withdraw(double amount) { balance -= amount; }

// constructors and methods for SavingsAccount
SavingsAccount::SavingsAccount(int id, double balance, double interestRate) : Account{id, balance}, interestRate{interestRate} {}
void SavingsAccount::applyInterest() { balance += balance * interestRate; }
} // namespace banking