#include "waveform.hpp"
#include <iostream>


Waveform::Waveform(float _freq)
  : norm_freq(_freq)
{
}


FrameBuffer& SineWave::generate(){

    unsigned int n;
    for (n = 0; n < FrameBuffer::frame_size; n++)
    {
        // TODO: this should probably be an approximation..
        float sample = std::sin(3.14151598 * 2 * norm_freq * n + phase);

        buffer[n] = sample; // TODO: fix interleaving
                            //buffer[2 * n + 1] = sample;
    }

    phase = 3.141598 * 2 *norm_freq * n + phase;

    return buffer;
}


FrameBuffer& SquareWave::generate(){

    for (std::size_t i = 0; i < FrameBuffer::frame_size; i++)
    {
        buffer[i] = 0;
    }

    return buffer;
}
