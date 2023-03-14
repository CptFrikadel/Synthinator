#include <iostream>

#include "EventTypes.hpp"
#include "InputThread.hpp"
#include "EventQueue.hpp"
#include "AudioThread.hpp"


int main (int argc, char *argv[]){

    // TODO: make log file instead of stderr
    std::cerr << "Yo Whaddup!" << std::endl;

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [Keyboard device path] \n"
            "\nPath to the keyboard device. When keyboard has n-key rollover, take care that the device name ends in 'kbd' else"
            " it will only create events when more than six keys are pressed simultaneously"
            "\n\nAs of now, only six-key rollover is implemented."
            << std::endl;

        return -1;
    }

    std::string keyboard_device = argv[1];

    auto event_queue = std::make_shared<EventQueue<NoteEvent>>();

    InputThread input_thread(keyboard_device, event_queue);
    AudioThread audio_thread(event_queue);

    return 0;
}
