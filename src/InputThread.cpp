



#include "InputThread.hpp"


InputThread::InputThread(const std::string& keyboardDevicePath, std::shared_ptr<EventQueue> input_queue)
    : input_events(input_queue)
{
    // Startup the input thread
    kbd = std::make_shared<Keyboard>(keyboardDevicePath, input_events);

    std::cerr << "Started Input Thread" << std::endl;
}

InputThread::~InputThread()
{
}
