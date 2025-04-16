#include "Account.h"

namespace banking {
Account::Account(double balance) : Account(0, balance) {}
Account::Account(int id, double balance) : id{id}, balance{balance} {}
Account::operator double() const { return balance; }
int Account::getId() const { return id; }
double Account::getBalance() const { return balance; }
void Account::deposit(double amount) { balance += amount; }
void Account::withdraw(double amount) { balance -= amount; }
} // namespace banking