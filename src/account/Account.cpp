#include "Account.h"

namespace banking {
// internal implementation of IAccount
class Account : public IAccount {
  public:
    Account(int id, double balance); // constructor
    Account(double balance);         // conversion constructor
    ~Account() override = default;   // virtual destructor

    operator double() const; // conversion operator

    // IAccount interface
    int getId() const override final; // cannot be overridden by derived classes
    double getBalance() const override;
    void deposit(double amount) override;
    void withdraw(double amount) override;

  protected:
    int id;
    double balance;
};

// internal implementation of ISavingsAccount
class SavingsAccount final : public Account, public ISavingsAccount {
  public:
    SavingsAccount(int id, double balance, double interestRate); // constructor
    ~SavingsAccount() override = default;                        // virtual destructor

    // ISavingsAccount interface
    void applyInterest() override;

  private:
    double interestRate;
};

// factory function to create an account
std::shared_ptr<IAccount> createAccount(int id, double balance) { return std::make_shared<Account>(id, balance); }

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

// constructors and interface methods for SavingsAccount
SavingsAccount::SavingsAccount(int id, double balance, double interestRate) : Account{id, balance}, interestRate{interestRate} {}
void SavingsAccount::applyInterest() { balance += balance * interestRate; }
} // namespace banking