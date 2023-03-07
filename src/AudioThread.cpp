#include "AudioThread.hpp"


AudioThread::AudioThread(std::shared_ptr<EventQueue> eventQueue)
    : event_queue(eventQueue)
{

    if (snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0){

        std::cerr << "Error opening soud device yo!" << std::endl;
        exit(-1);

    }

    if (snd_pcm_set_params(pcm_handle,
                SND_PCM_FORMAT_FLOAT_LE,
                SND_PCM_ACCESS_RW_INTERLEAVED,
                1,
                sample_freq,
                0,
                10000) < 0){

        fprintf(stderr, "Playback open error!");
        exit(-1);
    }

    playback_loop = std::thread(&AudioThread::makeSound, this);

}

AudioThread::~AudioThread(){

    playback_loop.join();

}


void AudioThread::makeSound(){


    std::cerr << "Soundshizz" << std::endl;

    //Setup pollstuff
    int nfds = snd_pcm_poll_descriptors_count(pcm_handle);
    struct pollfd *pfds = (struct pollfd*) alloca(sizeof(struct pollfd) * nfds);

    snd_pcm_poll_descriptors(pcm_handle, pfds, nfds);


    std::cerr << "Buffer size: " << FrameBuffer::frame_size << std::endl;

    while(1){

        if (poll(pfds, nfds, 1000) > 0){
            if (pfds->revents > 0){
                if (onPlayback() < (int) FrameBuffer::frame_size){
                    // Buffer underrun, restart
                    fprintf(stderr, "Underrun!\n");
                    snd_pcm_prepare(pcm_handle);
                }
            }
        }
    }

    snd_pcm_close(pcm_handle);

}

void AudioThread::handleEvents()
{
    auto& events = event_queue->StartConsuming();

    if (events.empty())
    {
        event_queue->DoneConsuming();
        return;
    }


    for (auto& event : events)
    {
        // check what event it was
        if (event.type == NOTE_OFF && event.freq != 0)
        {
            // NOTE_OFF so remove from vector of playing notes
            for (auto it: playing)
            {
                if (it->analog_freq == event.freq)
                {
                    //std::cerr << "NOTE OFF " << it->analog_freq << std::endl;
                    it->signalOff();
                }
            }
        } 
        else if (event.type == NOTE_ON && event.freq != 0) 
        {
            // NOTE_ON create new oscillator and add to playing notes
            auto note = std::make_shared<Note>(event.freq, sample_freq);
            playing.push_back(note);
            //std::cerr << "NOTE ON " << event.freq << std::endl;
        }
    }

    event_queue->DoneConsuming();
}


int AudioThread::onPlayback(){

    handleEvents();

    // Reset buffer
    buffer *= 0;

    if (!playing.empty()){


        // Erase inactive notes from playing vector before synthesizing
        for (auto note = playing.begin(); note < playing.end(); note++){

            if (!(*note)->isActive()){
                note = playing.erase(note);
            }
        }

        std::cerr << "\r\e[K" << std::flush;

		// oscillate all running oscillators
        for (auto note : playing){

            // Print currently playing freqs
            std::cerr << note->analog_freq << "\t";

            buffer += (note->synthesize() * 0.15);
        }
    }


    return snd_pcm_writei(pcm_handle, buffer.get(), FrameBuffer::frame_size);
}
