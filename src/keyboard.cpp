#include "keyboard.hpp"
#include "Notes.hpp"


/*

Path to the keyboard device. Take care that the device name ends in "kbd" else
it will only create events when more than six or so keys are pressed simultaneously

As of now, the device can only populate six key events at the same time.

The other devices get events when more than six keys are held..

*/
//const char * Keyboard::keyboard_device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";

Keyboard::Keyboard(const std::string& devicePath, std::shared_ptr<EventQueue> eventQueue) 
    : queue(eventQueue)
{
    active = false;

    keyboard_ev = new input_event();
    keyboard_st = new keyboard_state();

    keyboard_fd = 0;
    keyboard_fd = open(devicePath.c_str(), O_RDONLY);

    if (keyboard_fd > 0){

        ioctl(keyboard_fd, EVIOCGNAME(256), name);
        std::cerr << "Keyboard Device: " << name << std::endl;

        active = true;
        loop = std::thread(&Keyboard::keyboardLoop, this);
    }

}

Keyboard::~Keyboard(){

    if (keyboard_fd > 0){

        active = false;
        loop.join();
        close(keyboard_fd);
    }

    delete keyboard_ev;
    delete keyboard_st;
    keyboard_fd = 0;
}

static float getNote(int key_code){

    switch (key_code){
    case KEY_Z:         return Notes::getFreq(NOTE_C4);
    case KEY_S:         return Notes::getFreq(NOTE_CS4);
    case KEY_X:         return Notes::getFreq(NOTE_D4);
    case KEY_D:         return Notes::getFreq(NOTE_DS4);
    case KEY_C:         return Notes::getFreq(NOTE_E4);
    case KEY_V:         return Notes::getFreq(NOTE_F4);
    case KEY_G:         return Notes::getFreq(NOTE_FS4);
    case KEY_B:         return Notes::getFreq(NOTE_G4);
    case KEY_H:         return Notes::getFreq(NOTE_GS4);
    case KEY_N:         return Notes::getFreq(NOTE_A4);
    case KEY_J:         return Notes::getFreq(NOTE_AS4);
    case KEY_M:         return Notes::getFreq(NOTE_B4);
    case KEY_COMMA:     return Notes::getFreq(NOTE_C5);
    case KEY_L:         return Notes::getFreq(NOTE_CS5);
    case KEY_DOT:       return Notes::getFreq(NOTE_D5);
    case KEY_SEMICOLON: return Notes::getFreq(NOTE_DS5);
    case KEY_SLASH:     return Notes::getFreq(NOTE_E5);
    }

    return 0;
}


void Keyboard::keyboardLoop(){

    while (active){

        int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));

        if (bytes > 0){

            if (keyboard_ev->type & EV_KEY){

                if (keyboard_st->keys[keyboard_ev->code] != keyboard_ev->value && keyboard_ev->value != 2){

                    keyboard_st->keys[keyboard_ev->code] = keyboard_ev->value;

                    float freq = getNote(keyboard_ev->code);
                    Event_type type;

                    switch(keyboard_ev->value){
                    case 0: type = NOTE_OFF; break;
                    case 1: type = NOTE_ON; break;
                    }

                    queue->append(freq, type);
                }
            }

        }
    }

}

short Keyboard::getKeyState(short key){

    return keyboard_st->keys[key];
}
