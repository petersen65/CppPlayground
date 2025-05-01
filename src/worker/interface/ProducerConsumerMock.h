#pragma once

#include <gmock/gmock.h>

#include "ProducerConsumer.h"

using namespace producer_consumer;

namespace producer_consumer_mock {
template <typename ITEM, typename STATUS>
class ProducerConsumerMock : public IProducerConsumer<ITEM, STATUS> {
  public:
    MOCK_METHOD(ProducerResult, produce, (ITEM && item, STATUS status), (override));
    MOCK_METHOD(ConsumerResult, consume, (ITEM * item, std::chrono::milliseconds timeout), (override));
    MOCK_METHOD(void, finish, (STATUS status), (override));
    MOCK_METHOD(void, cancel, (STATUS status), (override));
    MOCK_METHOD(bool, finished, (), (const, override));
    MOCK_METHOD(bool, cancelled, (), (const, override));
    MOCK_METHOD(STATUS, status, (), (const, override));
    MOCK_METHOD(size_t, count, (), (const, override));
};
} // namespace producer_consumer_mock