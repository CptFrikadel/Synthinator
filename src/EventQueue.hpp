#ifndef _EVENTQUEUE_HPP
#define _EVENTQUEUE_HPP

#include <vector>
#include <mutex>

/*
 * @brief Thread safe event queueueue. When consuming, the vector being consumed
 * is guaranteed to not be modified by the queue.
 *
 * Consuming is started by calling StartConsuming, which swaps the appending and
 * consuming queues and locks the consuming queue. When consuming is finished
 * DoneConsuming needs to be called which clears the consuming queue and unlocks
 * it.
 */
template<typename T>
class EventQueue {

public:

    void append(T event)
    {
        std::lock_guard<std::mutex> lock(appendingLock);
        forAppending.push_back(event);
    }

    std::vector<T>& StartConsuming()
    {
        consumerLock.lock();

        {
            std::lock_guard<std::mutex> lock(appendingLock);
            forConsuming.swap(forAppending);
        }

        return forConsuming;
    }


    void DoneConsuming()
    {
        forConsuming.clear();

        consumerLock.unlock();
    }

private:

    std::vector<T> forConsuming;
    std::vector<T> forAppending;

    std::mutex appendingLock;
    std::mutex consumerLock;
};

#endif
