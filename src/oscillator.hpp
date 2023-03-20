/*
  Holds components for an arbitrary waveform oscillator.

  oscillate() fills the buffer with samples and returns a reference

*/

#ifndef _OSCILLATOR_HPP
#define _OSCILLATOR_HPP

#include <cstdlib>
#include <memory>
#include "waveform.hpp"
#include "FrameBuffer.hpp"



class Oscillator {

public:

  Oscillator(const float norm_freq, float amplitude, float phase, WaveType _type);
  ~Oscillator() = default;

  FrameBuffer& oscillate();       // Do oscillate callback thingy

  WaveType getType(){return type;}

private:
  float norm_freq;        // Normalized frequency (cycles / sample)
  float amplitude;
  float phase;
  WaveType type;        // WaveType

  std::shared_ptr<Waveform> waveform;    // Waveform gen

  void normalize();     // Calculate normalized freq

};

#endif
