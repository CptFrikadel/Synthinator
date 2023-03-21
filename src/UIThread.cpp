#include "UIThread.hpp"
#include "EventTypes.hpp"
#include <chrono>
#include <thread>


void UIThread::Start()
{
    mActive = true;
    
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
        auto& events = mEventQueue->StartConsuming();

        if (events.empty())
        {
            mEventQueue->DoneConsuming();
            return;
        }


        for (auto& event : events)
        {
            if (event.type == UIEvent::QUIT)
                mActive = false;
        }

        mEventQueue->DoneConsuming();

        // Bodge 50Hz refresh rate
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
