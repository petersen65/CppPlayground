#pragma once

#include <chrono>
#include <condition_variable>
#include <queue>
#include <shared_mutex>

namespace producer_consumer {
enum class ConsumerResult { Available, Timeout, Finished };
enum class ProducerResult { Taken, Cancelled };

template <typename ITEM, typename STATUS>
class IProducerConsumer {
  public:
    virtual ~IProducerConsumer() = default;
    virtual ProducerResult produce(ITEM &&item, STATUS status) = 0;
    virtual ConsumerResult consume(ITEM *item, std::chrono::milliseconds timeout = 0) = 0;
    virtual void finish(STATUS status) = 0;
    virtual void cancel(STATUS status) = 0;
    virtual bool finished() const = 0;
    virtual bool cancelled() const = 0;
    virtual STATUS status() const = 0;
    virtual size_t count() const = 0;
};

template <typename ITEM, typename STATUS>
class ProducerConsumer final : public IProducerConsumer<ITEM, STATUS> {
  public:
    ~ProducerConsumer() override = default;

    ProducerResult produce(ITEM &&item, STATUS status) override;
    ConsumerResult consume(ITEM *item, std::chrono::milliseconds timeout = 0) override;
    void finish(STATUS status) override;
    void cancel(STATUS status) override;
    bool finished() const override;
    bool cancelled() const override;
    STATUS status() const override;
    size_t count() const override;

  private:
    bool isFinished{false};
    bool isCancelled{false};
    STATUS lastStatus{};
    std::shared_timed_mutex sharedOrExclusiveAccess;
    std::condition_variable_any itemCondition;
    std::queue<ITEM> itemQueue;
};

template <typename ITEM, typename STATUS>
inline bool ProducerConsumer<ITEM, STATUS>::finished() const {
    std::shared_lock reader(sharedOrExclusiveAccess);
    return isFinished;
}

template <typename ITEM, typename STATUS>
inline bool ProducerConsumer<ITEM, STATUS>::cancelled() const {
    std::shared_lock reader(sharedOrExclusiveAccess);
    return isCancelled;
}

template <typename ITEM, typename STATUS>
inline STATUS ProducerConsumer<ITEM, STATUS>::status() const {
    std::shared_lock reader(sharedOrExclusiveAccess);
    return lastStatus;
}

template <typename ITEM, typename STATUS>
inline size_t ProducerConsumer<ITEM, STATUS>::count() const {
    std::shared_lock reader(sharedOrExclusiveAccess);
    return itemQueue.size();
}
} // namespace producer_consumer