/// @file ProducerConsumer.h
/// @brief C++ templates which implement thread-safe producer-consumer patterns
/// @date 2025
/// @author Michael Petersen

#pragma once

#include <chrono>
#include <condition_variable>
#include <queue>
#include <shared_mutex>

namespace producer_consumer {
/// @brief For a producer of items, the interest of the consumer in the next item is defined through this enumeration
enum class ProducerResult { Taken, Cancelled };

/// @brief For a consumer of items, the availability of the next produced item is defined through this enumeration    
enum class ConsumerResult { Available, Timeout, Finished };

/// @brief Abstract class that provides the contract for a producer-consumer pattern implementation
/// @tparam ITEM    Typename for produced and consumed items
/// @tparam STATUS  Status typename when the producer finishes its work or the consumer cancels its interest
template <typename ITEM, typename STATUS>
class IProducerConsumer {
  public:
    virtual ~IProducerConsumer() = default;
    virtual ProducerResult produce(ITEM &&item) = 0;
    virtual ProducerResult produceAndFinish(ITEM &&item, STATUS status) = 0;
    virtual ConsumerResult consume(ITEM *item, std::chrono::milliseconds timeout = 0) = 0;
    virtual void finishProducer(STATUS status) = 0;
    virtual void cancelConsumer(STATUS status) = 0;
    virtual bool finished() const = 0;
    virtual bool cancelled() const = 0;
    virtual STATUS status() const = 0;
    virtual size_t count() const = 0;
};

/// @brief Producer-Consumer pattern implemented as a thread-safe C++ class template
/// @tparam ITEM    Typename for produced and consumed items
/// @tparam STATUS  Status typename when the producer finishes its work or the consumer cancels its interest
template <typename ITEM, typename STATUS>
class ProducerConsumer final : public IProducerConsumer<ITEM, STATUS> {
  public:
    ~ProducerConsumer() override = default;

    ProducerResult produce(ITEM &&item) override;
    ProducerResult produceAndFinish(ITEM &&item, STATUS status) override;
    ConsumerResult consume(ITEM *item, std::chrono::milliseconds timeout = 0) override;
    void finishProducer(STATUS status) override;
    void cancelConsumer(STATUS status) override;
    bool finished() const override;
    bool cancelled() const override;
    STATUS status() const override;
    size_t count() const override;

  private:
    bool isFinished{false};
    bool isCancelled{false};
    STATUS lastStatus{};
    mutable std::shared_timed_mutex sharedOrExclusiveAccess;
    std::condition_variable_any itemCondition;
    std::queue<ITEM> itemQueue;
};

/// @brief 
/// @tparam ITEM 
/// @tparam STATUS 
/// @param item 
/// @return 
template <typename ITEM, typename STATUS>
inline ProducerResult ProducerConsumer<ITEM, STATUS>::produce(ITEM &&item) {
    std::unique_lock writer{sharedOrExclusiveAccess};

    if (isFinished || isCancelled) {
        return ProducerResult::Cancelled;
    }

    itemQueue.push(std::move(item));
    itemCondition.notify_one();
    return ProducerResult::Taken;
}

template <typename ITEM, typename STATUS>
inline ProducerResult ProducerConsumer<ITEM, STATUS>::produceAndFinish(ITEM &&item, STATUS status) {
    std::unique_lock writer{sharedOrExclusiveAccess};

    if (isFinished || isCancelled) {
        return ProducerResult::Cancelled;
    }

    itemQueue.push(std::move(item));
    isFinished = true;
    lastStatus = status;
    itemCondition.notify_all();
    return ProducerResult::Taken;
}

template <typename ITEM, typename STATUS>
inline ConsumerResult ProducerConsumer<ITEM, STATUS>::consume(ITEM *item, std::chrono::milliseconds timeout) {
    std::unique_lock writer{sharedOrExclusiveAccess};

    if ((isFinished || isCancelled) && itemQueue.empty()) {
        return ConsumerResult::Finished;
    }

    if (timeout.count() > 0) {
        itemCondition.wait_for(writer, timeout, [this] { return !itemQueue.empty() || isFinished || isCancelled; });
    } else {
        itemCondition.wait(writer, [this] { return !itemQueue.empty() || isFinished || isCancelled; });
    }

    if (!itemQueue.empty()) {
        *item = std::move(itemQueue.front());
        itemQueue.pop();
        return ConsumerResult::Available;
    }

    if (isFinished || isCancelled) {
        return ConsumerResult::Finished;
    }

    return ConsumerResult::Timeout;
}

template <typename ITEM, typename STATUS>
inline void ProducerConsumer<ITEM, STATUS>::finishProducer(STATUS status) {
    std::unique_lock writer{sharedOrExclusiveAccess};
    isFinished = true;
    lastStatus = status;
    itemCondition.notify_all();
}

template <typename ITEM, typename STATUS>
inline void ProducerConsumer<ITEM, STATUS>::cancelConsumer(STATUS status) {
    std::unique_lock writer{sharedOrExclusiveAccess};
    isCancelled = true;
    lastStatus = status;
    itemCondition.notify_all();
}

template <typename ITEM, typename STATUS>
inline bool ProducerConsumer<ITEM, STATUS>::finished() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return isFinished;
}

template <typename ITEM, typename STATUS>
inline bool ProducerConsumer<ITEM, STATUS>::cancelled() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return isCancelled;
}

template <typename ITEM, typename STATUS>
inline STATUS ProducerConsumer<ITEM, STATUS>::status() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return lastStatus;
}

template <typename ITEM, typename STATUS>
inline size_t ProducerConsumer<ITEM, STATUS>::count() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return itemQueue.size();
}
} // namespace producer_consumer