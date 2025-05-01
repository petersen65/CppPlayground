#pragma once

#include <chrono>

namespace producer_consumer {
enum class ConsumerResult { Available, Timeout, Finished };
enum class ProducerResult { Taken, Cancelled };

template <typename ITEM, typename STATUS> class IProducerConsumer {
  public:
    virtual ~IProducerConsumer() = default;
    virtual ProducerResult produce(ITEM &&item, STATUS status) = 0;
    virtual ConsumerResult consume(ITEM *item, std::chrono::milliseconds timeout = 0) = 0;
    virtual void finish(STATUS status) = 0;
    virtual void cancel(STATUS status) = 0;
    virtual bool finished() = 0;
    virtual bool cancelled() = 0;
    virtual STATUS status() const = 0;
    virtual size_t count() const = 0;
};
} // namespace producer_consumer