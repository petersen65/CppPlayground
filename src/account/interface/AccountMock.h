#pragma once

#include <gmock/gmock.h>

#include "Account.h"

using namespace banking;

namespace banking_mock {
class AccountMock : public IAccount {
    public:
    MOCK_METHOD(int, getId, (), (const, override));
    MOCK_METHOD(double, getBalance, (), (const, override));
    MOCK_METHOD(void, deposit, (double amount), (override));
    MOCK_METHOD(void, withdraw, (double amount), (override));
};

class MockSavingsAccount : public ISavingsAccount {
    public:
    MOCK_METHOD(void, applyInterest, (), (override));
};
} // namespace banking_mock