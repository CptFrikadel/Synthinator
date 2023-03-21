#include "InputThread.hpp"
#include "EventQueue.hpp"
#include "EventTypes.hpp"
#include <memory>


InputThread::InputThread(const std::string& keyboardDevicePath, std::shared_ptr<EventQueue<NoteEvent>> input_queue, std::shared_ptr<EventQueue<UIEvent>> ui_queue)
    : mInputEvents(input_queue)
    , mUIEvents(ui_queue)
{
    // Startup the input thread
    mKeyboard = std::make_shared<Keyboard>(keyboardDevicePath, mInputEvents, mUIEvents);

    std::cerr << "Started Input Thread" << std::endl;
}

InputThread::~InputThread()
{
}
