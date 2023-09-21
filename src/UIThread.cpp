#include "UIThread.hpp"
#include "EventTypes.hpp"
#include "NoteBuilder.hpp"
#include <chrono>
#include <iostream>
#include <thread>


void UIThread::Start()
{
    mActive = true;
    
    std::cerr << "Starting UIThread.." << std::endl;
    mThread = std::thread(&UIThread::HandleUI, this);

    mCursesUI.Init();

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
            mCursesUI.Update();
            continue;
        }


        for (auto& event : events)
        {
            switch (event.type){
            case UIEvent::QUIT:
            {
                mActive = false;
                mCursesUI.Exit();
                break;
            }
            case UIEvent::TOGGLE_MODE_1:
            {
                NoteBuilder noteBuilder(48000);

                noteBuilder.setBaseEnvelope({1, 10, .9, 1500})
                    .addHarmonic( .125, -3, 3.14, WaveType::WAVE_SINE)
                    .addHarmonic( .124, -3, 3.14, WaveType::WAVE_SINE)
                    .addHarmonic( .25, 3, 3.14, WaveType::WAVE_SINE)
                    .addHarmonic( .25, 6, 3.14, WaveType::WAVE_SINE)
                    .addHarmonic( 1, 0, 0, WaveType::WAVE_SINE)
                    .addHarmonic( 2, -12, 0.5*3.14, WaveType::WAVE_SINE)
                    .addHarmonic( 4, -18, 0.25*3.14, WaveType::WAVE_SQUARE);

                mAudioThread->SetNoteBuilder(noteBuilder);
                break;
            }
            case UIEvent::TOGGLE_MODE_2:
            {
                NoteBuilder noteBuilder(mAudioThread->GetSampleFreq());

                noteBuilder.setBaseEnvelope({1, 10, .9, 500})
                    .addHarmonic( 1, 0, 0, WaveType::WAVE_SQUARE);

                mAudioThread->SetNoteBuilder(noteBuilder);
                break;
            }
            }

        }

        mEventQueue->DoneConsuming();
        mCursesUI.Update();
    }

    mCursesUI.Exit();
}
