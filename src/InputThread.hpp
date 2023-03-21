/*

    Wrapper for the input thread

*/

#ifndef _INPUT_THREAD_HPP
#define _INPUT_THREAD_HPP

#include "EventTypes.hpp"
#include "keyboard.hpp"
#include "EventQueue.hpp"
#include <memory>


class InputThread{

public:
    InputThread(const std::string& keyboardDevicePath, std::shared_ptr<EventQueue<NoteEvent>> input_queue, std::shared_ptr<EventQueue<UIEvent>> ui_queue);
    ~InputThread();


private:
    bool mActive;
    std::shared_ptr<Keyboard> mKeyboard; // Pointer to keyboard device
    std::shared_ptr<EventQueue<NoteEvent>> mInputEvents;
    std::shared_ptr<EventQueue<UIEvent>>   mUIEvents;

};

#endif
