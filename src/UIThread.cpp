#include "UIThread.hpp"
#include "EventTypes.hpp"
#include "NoteBuilder.hpp"
#include "PresetManager.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>


void UIThread::Start()
{
    mPresetFile = std::make_shared<YamlPresetFile>();
    mPresetFile->ReadFromFile("presets.yaml");
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
                auto presets = mPresetFile->GetNotePresets();
                mAudioThread.SetNoteBuilder(presets[0]);
                break;
            }
            case UIEvent::TOGGLE_MODE_2:
            {
                auto presets = mPresetFile->GetNotePresets();

                if (presets.size() >= 2)
                    mAudioThread.SetNoteBuilder(presets[1]);
                break;
            }
            case UIEvent::TOGGLE_MODE_3:
            {
                auto presets = mPresetFile->GetNotePresets();

                if (presets.size() >= 3)
                    mAudioThread.SetNoteBuilder(presets[2]);
                break;
            }
            case UIEvent::TOGGLE_MODE_4:
            {
                auto presets = mPresetFile->GetNotePresets();

                if (presets.size() >= 4)
                    mAudioThread.SetNoteBuilder(presets[3]);
                break;
            }
            case UIEvent::TOGGLE_MODE_5:
            {
                auto presets = mPresetFile->GetNotePresets();

                if (presets.size() >= 5)
                    mAudioThread.SetNoteBuilder(presets[4]);
                break;
            }
            case UIEvent::RELOAD_PRESETS:
            {
                mPresetFile->ReadFromFile("presets.yaml");
                break;
            }
            case UIEvent::MUTE:
            {
                mAudioThread.ToggleMute();
                break;
            }
            }

        }

        mEventQueue->DoneConsuming();
        mCursesUI.Update();
    }

    mCursesUI.Exit();
}
