#include "waveform.hpp"
#include <iostream>


Waveform::Waveform(float _freq, float _amplitude, float _phase)
    :norm_freq(_freq)
    ,amplitude(_amplitude)
    ,phase(_phase)
{
}


FrameBuffer& SineWave::generate(){

    unsigned int n;
    for (n = 0; n < FrameBuffer::frame_size; n++)
    {
        // TODO: this should probably be an approximation..
        float sample = amplitude * std::sin(3.14151598 * 2 * norm_freq * n + phase);

        buffer[n] = sample; // TODO: fix interleaving
                            //buffer[2 * n + 1] = sample;
    }

    phase = 3.141598 * 2 *norm_freq * n + phase;

    return buffer;
}


FrameBuffer& SquareWave::generate(){

    std::size_t n;
    for (n = 0; n < FrameBuffer::frame_size; n++)
    {
        float sample = std::sin(3.14151598 * 2 * norm_freq * n + phase);
        if (sample >= 0 )
            buffer[n] = 0.707 * amplitude; // same RMS value as a sine wave
        else
            buffer[n] = -0.707 * amplitude;
    }

    phase = 3.141598 * 2 *norm_freq * n + phase;

    return buffer;
}
