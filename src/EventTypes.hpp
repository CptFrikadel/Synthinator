#pragma once


struct NoteEvent 
{
    enum Event_type
    {
        NOTE_OFF,
        NOTE_ON
    };

    Event_type type;
    float freq;
    int velocity;
};


struct UIEvent
{
    enum Event_type
    {
        QUIT
    };

    Event_type type;
};
