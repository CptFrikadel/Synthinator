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
    std::shared_ptr<Oscillator> osc1(new Oscillator(norm_freq, WaveType::WAVE_SINE));
    oscillators.emplace_back(osc1);

    // Add some harmonics for shits n giggles
	std::shared_ptr<Oscillator> osc2(new Oscillator(norm_freq / 2, WaveType::WAVE_SINE));
	oscillators.emplace_back(osc2);
    //oscillators.emplace_back(new Oscillator(norm_freq / 4, WaveType::WAVE_SINE));
	std::shared_ptr<Oscillator> osc3(new Oscillator(norm_freq / 4, WaveType::WAVE_SINE));
	oscillators.emplace_back(osc3);
    //oscillators.emplace_back(new Oscillator(norm_freq / 8, WaveType::WAVE_SINE));
	std::shared_ptr<Oscillator> osc4(new Oscillator(norm_freq / 8, WaveType::WAVE_SINE));
	oscillators.emplace_back(osc4);
    //oscillators.emplace_back(new Oscillator(norm_freq * 2, WaveType::WAVE_SINE));
    //oscillators.emplace_back(norm_freq * 4, WaveType::WAVE_SINE);
    /*
        Initialize the base envelope and place at first position in chain
    */

    base_envelope = new EnvelopeFilter(5000, 500, 0.95, 6000);

}


FrameBuffer& Note::synthesize(){



    if (base_envelope->envelope_phase != FINISHED){

        // Oscillate and sum all harmonics
        for (auto osc = oscillators.begin(); osc != oscillators.end(); ++osc){

            buffer += (*osc)->oscillate() *  (1 /(float) oscillators.size());

        }

        // Run filters on final buffer
        for (auto filter: filter_chain){
            filter->doFilterings(buffer);
        }

        // Finally run base envelope
        base_envelope->doFilterings(buffer);
    } else {
        note_active = false;
    }

    return buffer;
}

void Note::signalOff(){

    // Signal the base envelope to release
    base_envelope->envelope_phase = RELEASE;
    envelope_phase = RELEASE;


}

void Note::addHarmonic(const float freq){

    //oscillators.emplace_back(normalize(freq), WaveType::WAVE_SINE);

}

void Note::addFilter(){

}
