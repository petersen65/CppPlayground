/// @file ProducerConsumer.h
/// @brief Mocks for C++ templates which implement thread-safe producer-consumer patterns
/// @date 2025
/// @author Michael Petersen

#pragma once

#include <gmock/gmock.h>

#include "ProducerConsumer.h"

using namespace producer_consumer;

namespace producer_consumer_mock {
/// @brief Mock C++ class template for a producer-consumer pattern implementation.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
template <typename ITEM, typename STATUS>
class ProducerConsumerMock : public IProducerConsumer<ITEM, STATUS> {
  public:
    MOCK_METHOD(ProducerResult, produce, (ITEM && item), (override));
    MOCK_METHOD(ProducerResult, produceAndFinish, (ITEM && item, STATUS status), (override));
    MOCK_METHOD(ConsumerResult, consume, (ITEM * item, std::chrono::milliseconds timeout), (override));
    MOCK_METHOD(void, finishProducer, (STATUS status), (override));
    MOCK_METHOD(void, cancelConsumer, (STATUS status), (override));
    MOCK_METHOD(bool, finished, (), (const, override));
    MOCK_METHOD(bool, cancelled, (), (const, override));
    MOCK_METHOD(STATUS, status, (), (const, override));
    MOCK_METHOD(size_t, count, (), (const, override));
};
} // namespace producer_consumer_mock