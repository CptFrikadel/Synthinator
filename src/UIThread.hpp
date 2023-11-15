#pragma once

#include "AudioThread.hpp"
#include "EventQueue.hpp"
#include "EventTypes.hpp"
#include "CursesUI.hpp"
#include "PresetManager.hpp"
#include <atomic>
#include <memory>
#include <thread>


class UIThread 
{
public:

    UIThread(std::shared_ptr<EventQueue<UIEvent>> uiEventQueue, AudioThread& audioThread)
        : mEventQueue(uiEventQueue)
        , mAudioThread(audioThread)
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
    AudioThread& mAudioThread;

    CursesUI mCursesUI;

    std::shared_ptr<YamlPresetFile> mPresetFile;

    void HandleUI();
};
