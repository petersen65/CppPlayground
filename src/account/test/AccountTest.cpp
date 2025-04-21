#include <gtest/gtest.h>

#include "AccountMock.h"

using namespace ::testing;
using namespace banking_mock;

namespace banking {
namespace testing {
namespace {
TEST(MockSuite, MockAccount) {
    // Prepare
    MockAccount account;

    EXPECT_CALL(account, getId).Times(Exactly(1));
    EXPECT_CALL(account, getBalance).Times(Exactly(1));
    EXPECT_CALL(account, deposit).Times(Exactly(1));
    EXPECT_CALL(account, withdraw).Times(Exactly(1));

    // Execute
    // Expect
    EXPECT_NO_THROW(account.getId());
    EXPECT_NO_THROW(account.getBalance());
    EXPECT_NO_THROW(account.deposit(100.0));
    EXPECT_NO_THROW(account.withdraw(50.0));
}

TEST(BankingSuite, AccountTest) {
    // Prepare
    auto account = createAccount(1, 1000.0);

    // Execute
    auto id = account->getId();
    account->deposit(100.0);
    account->withdraw(50.0);
    auto balance = account->getBalance();

    // Expect
    EXPECT_EQ(id, 1);
    EXPECT_EQ(balance, 1050.0);
}
} // namespace
} // namespace testing
} // namespace banking