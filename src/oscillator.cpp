#include "oscillator.hpp"
#include <iostream>

Oscillator::Oscillator(const float _norm_freq, float _amplitude, float _phase, WaveType _type):
                              norm_freq(_norm_freq),
                              amplitude(_amplitude),
                              phase(_phase),
                              type(_type)
{



  switch (type){
    case WaveType::WAVE_SINE:
      waveform = std::make_shared<SineWave>(norm_freq, amplitude, phase);
      break;
    case WaveType::WAVE_SQUARE:
      waveform = std::make_shared<SquareWave>(norm_freq, amplitude, phase);
      break;
  default:
      waveform = std::make_shared<SineWave>(norm_freq, amplitude, phase);
      break;

  }
}

FrameBuffer& Oscillator::oscillate()
{
  return waveform->generate();
}
