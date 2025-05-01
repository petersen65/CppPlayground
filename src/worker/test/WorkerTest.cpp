#include <gtest/gtest.h>

#include "Logging.h"
#include "ProducerConsumerMock.h"

using namespace ::testing;
using namespace producer_consumer_mock;
using namespace producer_consumer;

namespace worker {
namespace testing {
namespace {
TEST(WorkerSuite, ProducerConsumerTest) {
    // Prepare
    ProducerConsumer<int, int> producerConsumer;

    // Execute
    auto finished = producerConsumer.finished();
    auto cancelled = producerConsumer.cancelled();
    auto status = producerConsumer.status();
    auto count = producerConsumer.count();

    // Expect
    EXPECT_EQ(finished, false);
    EXPECT_EQ(cancelled, false);
    EXPECT_EQ(status, 0);
    EXPECT_EQ(count, 0UL);
}
} // namespace
} // namespace testing
} // namespace worker