#include "InputThread.hpp"
#include "EventTypes.hpp"


InputThread::InputThread(const std::string& keyboardDevicePath, std::shared_ptr<EventQueue<NoteEvent>> input_queue)
    : mInputEvents(input_queue)
{
    // Startup the input thread
    mKeyboard = std::make_shared<Keyboard>(keyboardDevicePath, mInputEvents);

    std::cerr << "Started Input Thread" << std::endl;
}

InputThread::~InputThread()
{
}
