/*

    Wrapper for the input thread

*/

#ifndef _INPUT_THREAD_HPP
#define _INPUT_THREAD_HPP

#include "keyboard.hpp"
#include "EventQueue.hpp"
#include <memory>


typedef struct {

    Event_type type;
    float freq;
    float velocity;

} InputEvent;


class InputThread{

public:
    InputThread(const std::string& keyboardDevicePath, std::shared_ptr<EventQueue> input_queue);
    ~InputThread();

    std::shared_ptr<EventQueue> mInputEvents;

private:
    bool mActive;
    std::shared_ptr<Keyboard> mKeyboard; // Pointer to keyboard device

};

#endif
