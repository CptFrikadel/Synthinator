/*

    Top level class of a single audible note

    - Each note can have a number of oscillators.
    - Each note holds its own filter structure so that:
        - Different notes can have different filters apllied
        - Time based effects are easier to implement (e.g. ADSR filters)
    - Note has an active flag which gets set to false when notehas reached the end of the envelope

*/
#ifndef _NOTE_HPP
#define _NOTE_HPP

#include <vector>
#include <memory>

#include "oscillator.hpp"
#include "Filter.hpp"
#include "EnvelopeFilter.hpp"
#include "FrameBuffer.hpp"

class Note {

public:
    Note(const float _analog_freq, const unsigned int _sample_freq);

    FrameBuffer& synthesize();
    void signalOff();
    void addHarmonic(const float _analog_freq);
    void addFilter();
    float getAnalogFreq(){return analog_freq;}
    bool isActive(){return note_active;}

    FrameBuffer buffer;
    float norm_freq;
    float analog_freq;
    unsigned int sample_freq;
    WaveType base_type = WaveType::WAVE_SINE;
    std::unique_ptr<EnvelopeFilter> base_envelope;
    State envelope_phase;

    bool note_active = true; // false when note is finished ringing out

private:
    // Some datastrucure holding the filter chain
    std::vector<Filter *> filter_chain;
    std::vector<std::shared_ptr<Oscillator>> oscillators;

    void normalize();
    float normalize(const float freq);

};

#endif
