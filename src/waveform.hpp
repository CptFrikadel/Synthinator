#ifndef _WAVEFORM_HPP
#define _WAVEFORM_HPP

#include <cmath>
#include "FrameBuffer.hpp"

enum class WaveType {
  WAVE_SINE,
  WAVE_SQUARE,
  WAVE_TRIANGLE,
  WAVE_SAW
};


class Waveform {

public:
  Waveform(float _freq, float _amplitude, float _phase = 0);
  virtual ~Waveform() = default;
  virtual FrameBuffer& generate() = 0;
  FrameBuffer buffer;

protected:
  float norm_freq;
  float amplitude;
  float phase;

};

class SquareWave : public Waveform{

public:
  SquareWave(float _freq, float _amplitude, float phase = 0): Waveform(_freq, _amplitude, phase){}
  FrameBuffer& generate() override;

};


class SineWave : public Waveform{

public:
  SineWave(float _freq, float _amplitude, float phase = 0): Waveform(_freq, _amplitude, phase){}
  FrameBuffer& generate() override;
};

#endif
