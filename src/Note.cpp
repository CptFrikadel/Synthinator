#include "Note.hpp"
#include "EnvelopeFilter.hpp"
#include "Filter.hpp"
#include "waveform.hpp"
#include <iostream>

void Note::normalize(){

    norm_freq = analog_freq / sample_freq;

}

float Note::normalize(const float freq){

    return freq / sample_freq;

}

Note::Note(const float _analog_freq, const unsigned int _sample_freq, ADSR adsr) :
    norm_freq(normalize(_analog_freq)),
    analog_freq(_analog_freq),
    sample_freq(_sample_freq),
    base_envelope(adsr)
{
}


FrameBuffer& Note::synthesize()
{
    if (base_envelope.IsFinished())
    {
        note_active = false;
        return buffer *= 0;
    }

    buffer *= 0;

    // Oscillate and sum all harmonics
    for (auto& osc : oscillators){

        buffer += osc.oscillate() *  (1 /(float) oscillators.size());
    }

    // Run filters on final buffer
    for (auto& filter: filter_chain){
        filter.doFilterings(buffer);
    }

    // Finally run base envelope
    base_envelope.doFilterings(buffer);

    return buffer;
}

void Note::signalOff(){

    // Signal the base envelope to release
    base_envelope.FinishOff();

}

void Note::addHarmonic(const float analogFreq, float amplitude, WaveType type, float phase)
{
    oscillators.emplace_back(normalize(analogFreq), amplitude, phase, type);
}


void Note::addFilter(){

}
