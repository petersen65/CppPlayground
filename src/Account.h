#pragma once

namespace banking {
class Account {
  public:
    Account(double balance); // conversion constructor
    Account(int id, double balance);

    operator double() const; // conversion operator

    int getId() const;
    double getBalance() const;
    void deposit(double amount);
    void withdraw(double amount);

  private:
    int id;
    double balance;
};
} // namespace banking