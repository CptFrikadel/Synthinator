#include <iostream>

#include "InputThread.hpp"
#include "EventQueue.hpp"
#include "AudioThread.hpp"


int main (int argc, char *argv[]){

    // TODO: make log file instead of stderr
    std::cerr << "Yo Whaddup!" << std::endl;

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [Keyboard device path]" << std::endl;
        return -1;
    }

    std::string keyboard_device = argv[1];

    EventQueue event_queue;


    InputThread input_thread(keyboard_device, &event_queue);
    AudioThread audio_thread(&event_queue);

    return 0;
}
