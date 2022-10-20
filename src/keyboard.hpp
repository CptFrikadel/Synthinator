
/*
    Device class to interact with the keyboard device in /dev/input/event*

    NEEDS ROOT PRIVILEGES

    Based on: https://www.keithlantz.net/2011/10/a-keyboard-handler-and-timer-in-c-for-the-linux-platform/

*/

#ifndef _KEYBOARD_HPP
#define _KEYBOARD_HPP

#include <linux/input.h>
#include <memory>
#include <thread>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include "EventQueue.hpp"

struct keyboard_state {

    signed short keys[KEY_CNT];
};

class Keyboard {

public:

    Keyboard(const std::string& devicePath, std::shared_ptr<EventQueue> queue);
    ~Keyboard();
    short getKeyState(short key);
    void keyboardLoop();

private:
    struct keyboard_state *keyboard_st;
    input_event *keyboard_ev;
    int keyboard_fd;
    std::thread loop;
    bool active;
    char name[256];

    std::shared_ptr<EventQueue> queue;

};


#endif
