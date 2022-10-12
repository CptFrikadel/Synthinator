/*

    Wrapper for the input thread

*/

#ifndef _INPUT_THREAD_HPP
#define _INPUT_THREAD_HPP

#include "keyboard.hpp"
#include "EventQueue.hpp"


typedef struct {

    Event_type type;
    float freq;
    float velocity;

} InputEvent;


class InputThread{

public:
    InputThread(const std::string& keyboardDevicePath, EventQueue * _input_queue);
    ~InputThread();
    EventQueue * input_events;


private:
    bool active;
    Keyboard * kbd; // Pointer to keyboard device



};

#endif
