#pragma once

namespace banking
{
    class Account
    {
    public:
        Account(int id, double balance);

        int getId() const;
        double getBalance() const;
        void deposit(double amount);
        void withdraw(double amount);

    private:
        int id;
        double balance;
    };
}