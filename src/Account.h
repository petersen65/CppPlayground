#pragma once

#include <memory>

namespace banking {
// public interface for account management
class IAccount {
  public:
    virtual int getId() const = 0;
    virtual double getBalance() const = 0;
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

// public interface for savings account management
class ISavingsAccount : public IAccount {
  public:
    virtual void applyInterest() = 0;
};

// factory functions to create accounts 
std::shared_ptr<IAccount> createAccount(int id, double balance);
std::shared_ptr<ISavingsAccount> createSavingsAccount(int id, double balance, double interestRate);
} // namespace banking