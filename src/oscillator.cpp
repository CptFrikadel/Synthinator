#include "oscillator.hpp"
#include <iostream>

Oscillator::Oscillator(const float _norm_freq):
    norm_freq(_norm_freq)
{
}


Oscillator::Oscillator(const float _norm_freq, WaveType _type):
                              norm_freq(_norm_freq),
                              type(_type)
{



  switch (type){
    case WaveType::WAVE_SINE:
      waveform = new SineWave(norm_freq);
      break;
    case WaveType::WAVE_SQUARE:
      waveform = new SquareWave(norm_freq);
      break;
  default:
      waveform = new SineWave(norm_freq);
      break;

  }


}

Oscillator::~Oscillator(){

    delete waveform;
}

FrameBuffer& Oscillator::oscillate(){

  return waveform->generate();

}
