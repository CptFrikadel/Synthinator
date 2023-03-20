#include "NoteBuilder.hpp"
#include "EnvelopeFilter.hpp"
#include <cmath>

static constexpr float fromDb(float valueDb)
{
    return std::pow(10.0f, valueDb/20.0f);
}

NoteBuilder& NoteBuilder::setBaseEnvelope(ADSRms adsr)
{
    baseADSR = adsr;

    return *this;
}


NoteBuilder& NoteBuilder::addHarmonic(float freqMultiplier, float volumeDb, float phaseOffsetRadians, WaveType type)
{
    harmonics.emplace_back(freqMultiplier, volumeDb, phaseOffsetRadians, type);

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
      note.addHarmonic(
              baseFreq * harmonic.frequencyMultiplier,
              fromDb(harmonic.volumeDb),
              harmonic.type,
              harmonic.phaseOffsetRadians);
    }

    return note;
}
