#include "EventQueue.hpp"
#include <cassert>
#include <mutex>
#include <vector>


void EventQueue::append(float freq, Event_type type)
{
    Event event = {type, freq, 1};

    std::lock_guard<std::mutex> lock(appendingLock);
    forAppending.push_back(event);
}


std::vector<Event>& EventQueue::StartConsuming()
{
    consumerLock.lock();

    {
        std::lock_guard<std::mutex> lock(appendingLock);
        forConsuming.swap(forAppending);
    }

    return forConsuming;
}


void EventQueue::DoneConsuming()
{
    forConsuming.clear();

    consumerLock.unlock();

}
