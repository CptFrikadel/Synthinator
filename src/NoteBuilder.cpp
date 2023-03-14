#include "NoteBuilder.hpp"
#include "EnvelopeFilter.hpp"

NoteBuilder& NoteBuilder::setBaseEnvelope(ADSRms adsr)
{
    baseADSR = adsr;

    return *this;
}


NoteBuilder& NoteBuilder::addHarmonic(float freqMultiplier, WaveType type)
{
    harmonics.emplace_back(freqMultiplier, type);

    return *this;
}


Note NoteBuilder::Build(float baseFreq)
{
    ADSR adsrSamples;
    adsrSamples.attack  = baseADSR.attack * sampleFreq / 1000;
    adsrSamples.decay   = baseADSR.decay * sampleFreq / 1000;
    adsrSamples.release = baseADSR.release * sampleFreq / 1000;
    adsrSamples.sustain = baseADSR.sustain;
    

    Note note(baseFreq, sampleFreq, adsrSamples);

    for (auto& harmonic : harmonics)
    {
        note.addHarmonic(baseFreq * harmonic.frequencyMultiplier, harmonic.type);
    }

    return note;
}
