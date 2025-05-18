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
/// @brief For a producer of items, the interest of the consumer in the next item is defined through this enumeration.
/// @details The producer is either able to produce an item or it can be informed that no consumer is interested in the item anymore.
enum class ProducerResult { Taken, Cancelled };

/// @brief For a consumer of items, the availability of the next produced item is defined through this enumeration.
/// @details The consumer can receive an item, it can time out waiting for the next item, or it can be informed that the producer has finished its work.
enum class ConsumerResult { Available, Timeout, Finished };

/// @brief Abstract class that provides the contract for a producer-consumer pattern implementation.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
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

/// @brief Producer-Consumer pattern implemented as a thread-safe C++ class template.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
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

/// @brief Produce an item for any consumer.
/// @details The item is moved into the queue. If the producer is finished or the consumer is cancelled, the item is not added to the queue.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @param item    Item will be moved to the consumer
/// @return        Consumer will take the item or is not interested (item not moved in this case)
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

/// @brief Produce an item for any consumer and finish the producer.
/// @details The item is moved into the queue. If the producer is finished or the consumer is cancelled, the item is not added to the queue.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @param item    Item will be moved to the consumer
/// @param status  Detailed status from the producer why it finished its work
/// @return        Consumer will take the item or is not interested anymore
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

/// @brief Consume an existing item from a producer or wait for one until it is produced or a timeout happened.
/// @details The item is moved from the queue. If the producer is finished or the consumer is cancelled, the item is not removed from the queue.
///          If the timeout is zero, the consumer will wait infinitely until an item is available.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @param item    Item to be consumed that will be removed from the queue
/// @param timeout Duration in milliseconds to wait for an item to be produced or zero for an infinite wait
/// @return        Producer has produced an item, the consumer timed out waiting for an item, or the producer has finished its work
template <typename ITEM, typename STATUS>
inline ConsumerResult ProducerConsumer<ITEM, STATUS>::consume(ITEM *item, std::chrono::milliseconds timeout) {
    std::unique_lock writer{sharedOrExclusiveAccess};

    if ((isFinished || isCancelled) && itemQueue.empty()) {
        return ConsumerResult::Finished;
    }

    // Wait for a new item to be produced or for a producer to finish or for a consumer to cancel:
    //   1. Release the unique lock 'writer' and wait for 'itemCondition.notify*()' (atomic operation)
    //   2. If 'itemCondition.wait*()' wakes up internally (notify, spurious), acquire unique lock 'writer'
    //   3. Call lamba and evaluate its return value while holding the unique lock 'writer'
    //   4. If lambda returns false, release the unique lock 'writer' and wait again (atomic operation)
    //   5. If lambda returns true, keep the unique lock 'writer' acquired and continue
    //   6. If 'itemCondition.wait*()' wakes up externally (timeout), keep unique lock 'writer' acquired and continue
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

/// @brief This producer-consumer instance is finished and no items will be produced any more.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @param status
template <typename ITEM, typename STATUS>
inline void ProducerConsumer<ITEM, STATUS>::finishProducer(STATUS status) {
    std::unique_lock writer{sharedOrExclusiveAccess};
    isFinished = true;
    lastStatus = status;
    itemCondition.notify_all();
}

/// @brief This producer-consumer instance is cancelled and no consumer is interested in new items anymore.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @param status
template <typename ITEM, typename STATUS>
inline void ProducerConsumer<ITEM, STATUS>::cancelConsumer(STATUS status) {
    std::unique_lock writer{sharedOrExclusiveAccess};
    isCancelled = true;
    lastStatus = status;
    itemCondition.notify_all();
}

/// @brief Retrieve whether this producer-consumer instance is finished.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @return This producer-consumer instance is finished
template <typename ITEM, typename STATUS>
inline bool ProducerConsumer<ITEM, STATUS>::finished() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return isFinished;
}

/// @brief Retrieve whether this producer-consumer instance is cancelled.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @return This producer-consumer instance is cancelled
template <typename ITEM, typename STATUS>
inline bool ProducerConsumer<ITEM, STATUS>::cancelled() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return isCancelled;
}

/// @brief Retrieve status from last produce or consume operation.
/// @details The status is only valid if this producer-consumer instance is finished or cancelled.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @return
template <typename ITEM, typename STATUS>
inline STATUS ProducerConsumer<ITEM, STATUS>::status() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return lastStatus;
}

/// @brief Retrieve the number of currently stored items from all producers.
/// @tparam ITEM   Typename for produced and consumed items
/// @tparam STATUS Status typename when the producer finishes its work or the consumer cancels its interest
/// @return Number of currently stored items
template <typename ITEM, typename STATUS>
inline size_t ProducerConsumer<ITEM, STATUS>::count() const {
    std::shared_lock reader{sharedOrExclusiveAccess};
    return itemQueue.size();
}
} // namespace producer_consumer