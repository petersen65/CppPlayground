/// @file WorkerTest.cpp
/// @brief Unit tests for the worker library using Google Test.
/// @date 2025
/// @author Michael Petersen

#include <chrono>
#include <gtest/gtest.h>

#include "Logging.h"
#include "ProducerConsumerMock.h"

using namespace std::chrono_literals;
using namespace ::testing;
using namespace producer_consumer_mock;
using namespace producer_consumer;

namespace worker {
namespace testing {
namespace {
/// @brief Unit test for the ProducerConsumer class.
TEST(WorkerSuite, ProducerConsumerTest) {
    // Prepare
    ProducerConsumer<int, int> producerConsumer;

    // Execute
    auto producerResult1 = producerConsumer.produce(1);
    auto producerResult2 = producerConsumer.produceAndFinish(2, 0);
    auto count = producerConsumer.count();

    int item;
    auto consumerResult = producerConsumer.consume(&item, 100ms);

    producerConsumer.finishProducer(-1);
    producerConsumer.cancelConsumer(-2);

    auto finished = producerConsumer.finished();
    auto cancelled = producerConsumer.cancelled();
    auto status = producerConsumer.status();

    // Expect
    EXPECT_EQ(producerResult1, ProducerResult::Taken);
    EXPECT_EQ(producerResult2, ProducerResult::Taken);
    EXPECT_EQ(count, 2UL);
    EXPECT_EQ(item, 1);
    EXPECT_EQ(consumerResult, ConsumerResult::Available);
    EXPECT_EQ(finished, true);
    EXPECT_EQ(cancelled, true);
    EXPECT_EQ(status, -2);
    EXPECT_EQ(count, 2UL);
}
} // namespace
} // namespace testing
} // namespace worker