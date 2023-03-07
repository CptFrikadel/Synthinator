#include "EventQueue.hpp"
#include <cassert>
#include <mutex>
#include <vector>


void EventQueue::append(float freq, Event_type type)
{
    Event event = {type, freq, 1};

    forAppending.push_back(event);
}


std::vector<Event>& EventQueue::StartConsuming()
{
    consumerLock.lock();

    forConsuming.swap(forAppending);

    return forConsuming;
}


void EventQueue::DoneConsuming()
{
    forConsuming.clear();

    consumerLock.unlock();

}
