/*

    Wrapper class for event queue handling

    Queue entries are IDed by their base frequency

*/

#ifndef _EVENTQUEUE_HPP
#define _EVENTQUEUE_HPP

#include <vector>
#include <mutex>

enum Event_type{
        NOTE_OFF,
        NOTE_ON
};

typedef struct {

    Event_type type;
    float freq;
    int velocity;

} Event;

class EventQueue {

public:

    void append(float freq, Event_type type);

    std::vector<Event>& StartConsuming();
    void DoneConsuming();

private:

    std::vector<Event> forConsuming;
    std::vector<Event> forAppending;

    std::mutex consumerLock;

};


#endif
