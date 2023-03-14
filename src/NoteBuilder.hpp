#pragma once


#include "Filter.hpp"
#include "Note.hpp"
#include "waveform.hpp"
#include <vector>


class NoteBuilder 
{
public:

    struct Harmonic
    {
        float frequency;
        WaveType type;
    };

    struct ADSRms
    {
        float attack;
        float decay;
        float sustain;
        float release;
    };

    NoteBuilder(float _sampleFreq)
        : sampleFreq(_sampleFreq)
        , baseADSR({1, 0, 1, 1})
    {}


    NoteBuilder& addHarmonic(float freq, WaveType type);
    NoteBuilder& setBaseEnvelope(ADSRms adsr);

    Note Build(float baseFreq);

private:

    float sampleFreq;
    ADSRms baseADSR;

    std::vector<Harmonic> harmonics;
};
