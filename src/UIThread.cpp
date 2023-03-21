#include "UIThread.hpp"
#include "EventTypes.hpp"
#include <chrono>
#include <iostream>
#include <thread>


void UIThread::Start()
{
    mActive = true;
    
    std::cerr << "Starting UIThread.." << std::endl;
    mThread = std::thread(&UIThread::HandleUI, this);

    mThread.join();
}


void UIThread::Stop()
{
    mActive = false;
}


void UIThread::HandleUI()
{
    while (mActive)
    {
        // Bodge 50Hz refresh rate
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        auto& events = mEventQueue->StartConsuming();

        if (events.empty())
        {
            mEventQueue->DoneConsuming();
            continue;
        }


        for (auto& event : events)
        {
            if (event.type == UIEvent::QUIT)
            {
                mActive = false;
            }
        }

        mEventQueue->DoneConsuming();
    }
}
