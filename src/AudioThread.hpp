#ifndef _AUDIO_THREAD_HPP
#define _AUDIO_THREAD_HPP

#include <alsa/asoundlib.h>
#include <thread>
#include <iostream>
#include <vector>

#include "EventQueue.hpp"
#include "Note.hpp"

class AudioThread
{
public:
    AudioThread(std::shared_ptr<EventQueue> event_queue);
    ~AudioThread();

    std::shared_ptr<EventQueue> event_queue;

private:
    const unsigned int sample_freq = 48000;
    std::thread playback_loop;

    snd_pcm_t *pcm_handle;

    int onPlayback();
    void makeSound();

    FrameBuffer buffer;
    std::vector<std::shared_ptr<Note>> playing;

};


#endif
