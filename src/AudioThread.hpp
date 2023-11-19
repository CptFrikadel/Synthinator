#ifndef _AUDIO_THREAD_HPP
#define _AUDIO_THREAD_HPP

#include <alsa/asoundlib.h>
#include <atomic>
#include <cstddef>
#include <thread>
#include <iostream>
#include <utility>
#include <vector>
#include <numeric>

#include "EventQueue.hpp"
#include "EventTypes.hpp"
#include "Note.hpp"
#include "NoteBuilder.hpp"

class AudioThread
{
public:
    AudioThread(std::shared_ptr<EventQueue<NoteEvent>> event_queue);
    ~AudioThread();

    void Stop(){ mActive = false; }

    void Mute(){ mMuted = true; }
    void UnMute(){ mMuted = false; }
    void ToggleMute(){ mMuted = !mMuted; }

    const NoteBuilder& GetNoteBuilder() const { return noteBuilder; }
    void SetNoteBuilder(NoteBuilder _noteBuilder) { noteBuilder = std::move(_noteBuilder); }

    unsigned int GetSampleFreq() const { return sample_freq; }

    float GetCurrentLoad() const { return mLoadAverage; }

private:
    static const unsigned int sample_freq = 48000;
    static const std::size_t LoadAverageWindowSize = 100;
    std::thread playback_loop;

    std::atomic<bool> mActive;
    std::atomic<bool> mMuted;

    snd_pcm_t *pcm_handle;

    int onPlayback();
    void makeSound();
    void handleEvents();

    FrameBuffer buffer;
    std::vector<Note> playing;
    std::shared_ptr<EventQueue<NoteEvent>> event_queue;

    std::atomic<float> mLoadAverage = 0.0f;
    std::vector<float> mInstantaneousLoads;
    std::size_t mLoadsIndex = 0;

    NoteBuilder noteBuilder;
};


#endif
