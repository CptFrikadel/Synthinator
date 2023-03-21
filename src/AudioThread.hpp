#ifndef _AUDIO_THREAD_HPP
#define _AUDIO_THREAD_HPP

#include <alsa/asoundlib.h>
#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

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

private:
    const unsigned int sample_freq = 48000;
    std::thread playback_loop;

    std::atomic<bool> mActive;

    snd_pcm_t *pcm_handle;

    int onPlayback();
    void makeSound();
    void handleEvents();

    FrameBuffer buffer;
    std::vector<Note> playing;
    std::shared_ptr<EventQueue<NoteEvent>> event_queue;

    NoteBuilder noteBuilder;
};


#endif
