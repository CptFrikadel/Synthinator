#ifndef _AUDIO_THREAD_HPP
#define _INPUT_THREAD_HPP

#include <alsa/asoundlib.h>
#include <thread>
#include <iostream>
#include <vector>

//#include "oscillator.hpp"
#include "EventQueue.hpp"
#include "Note.hpp"

class AudioThread
{
public:
    AudioThread(EventQueue * _event_queue);
    ~AudioThread();

    EventQueue * event_queue;

private:
    static const unsigned int sample_freq = 48000;
    std::thread playback_loop;

    snd_pcm_t *pcm_handle;

    int onPlayback();
    void makeSound();

    FrameBuffer buffer;
    std::vector<Note> playing;



};


#endif
