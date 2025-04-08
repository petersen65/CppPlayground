#include "Account.h"

banking::Account::Account(int id, double balance)
    : id{id}, balance{balance}
{
}

int banking::Account::getId() const
{
    return id;
}

double banking::Account::getBalance() const
{
    return balance;
}

void banking::Account::deposit(double amount)
{
    balance += amount;
}

void banking::Account::withdraw(double amount)
{
    balance -= amount;
}