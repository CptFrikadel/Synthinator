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
        QUIT,
        TOGGLE_MODE_1,
        TOGGLE_MODE_2,
        TOGGLE_MODE_3,
        TOGGLE_MODE_4,
        TOGGLE_MODE_5,
        RELOAD_PRESETS,
        MUTE,
    };

    Event_type type;
};
