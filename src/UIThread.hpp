#pragma once

#include "EventQueue.hpp"
#include "EventTypes.hpp"
#include <atomic>
#include <memory>
#include <thread>


class UIThread 
{
public:

    UIThread(std::shared_ptr<EventQueue<UIEvent>> uiEventQueue)
        : mEventQueue(uiEventQueue)
    {}

    /*
     * @brief Start the UIThread and block untill it exits
     */
    void Start();

    void Stop();

private:

    std::thread mThread;
    std::atomic<bool> mActive;
    std::shared_ptr<EventQueue<UIEvent>> mEventQueue;

    void HandleUI();
};
