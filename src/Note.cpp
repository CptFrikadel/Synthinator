#include "Note.hpp"
#include "EnvelopeFilter.hpp"
#include "Filter.hpp"
#include <iostream>

void Note::normalize(){

    norm_freq = analog_freq / sample_freq;

}

float Note::normalize(const float freq){

    return freq / sample_freq;

}

Note::Note(const float _analog_freq, const unsigned int _sample_freq) :
    analog_freq(_analog_freq),
    sample_freq(_sample_freq)
{

    norm_freq = normalize(_analog_freq);
    // Add the base oscillator
    oscillators.emplace_back(std::make_shared<Oscillator>(norm_freq, WaveType::WAVE_SINE));

    oscillators.emplace_back(std::make_shared<Oscillator>(norm_freq / 2, WaveType::WAVE_SINE));
    oscillators.emplace_back(std::make_shared<Oscillator>(norm_freq / 4, WaveType::WAVE_SINE));
    oscillators.emplace_back(std::make_shared<Oscillator>(norm_freq * 2, WaveType::WAVE_SINE));
    oscillators.emplace_back(std::make_shared<Oscillator>(norm_freq * 4, WaveType::WAVE_SINE));

    /*
        Initialize the base envelope and place at first position in chain
    */
    base_envelope = std::make_unique<EnvelopeFilter>(5000, 1000, 0.95, 6000);

}


FrameBuffer& Note::synthesize()
{
    if (base_envelope->IsFinished())
    {
        note_active = false;
        return buffer *= 0;
    }

    buffer *= 0;

    // Oscillate and sum all harmonics
    for (auto osc : oscillators){

        buffer += osc->oscillate() *  (1 /(float) oscillators.size());
    }

    // Run filters on final buffer
    for (auto filter: filter_chain){
        filter->doFilterings(buffer);
    }

    // Finally run base envelope
    base_envelope->doFilterings(buffer);

    return buffer;
}

void Note::signalOff(){

    // Signal the base envelope to release
    base_envelope->FinishOff();

}

void Note::addHarmonic(const float freq){

    oscillators.emplace_back(std::make_shared<Oscillator>(normalize(freq), WaveType::WAVE_SINE));

}

void Note::addFilter(){

}
