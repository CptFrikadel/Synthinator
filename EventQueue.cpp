#include "EventQueue.hpp"
#include <iostream>



void EventQueue::handleNext(){

    // Handle next event and pop



}

void EventQueue::append(float freq, Event_type type){

    std::cerr << "Event: " << freq << ", " << type << std::endl;

    Event event = {type, freq, 1};

    queue.push_back(event);


}
