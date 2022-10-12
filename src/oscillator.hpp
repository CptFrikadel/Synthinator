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

  Oscillator(const float norm_freq);
  Oscillator(const float norm_freq, WaveType _type);
  ~Oscillator();

  std::shared_ptr<Waveform> waveform;    // Waveform gen
  float norm_freq;        // Normalized frequency (cycles / sample)

  FrameBuffer& oscillate();       // Do oscillate callback thingy

public:
  void setType(WaveType _type){ type = _type;}
  WaveType getType(){return type;}

private:
  WaveType type;        // WaveType

private:
  void normalize();     // Calculate normalized freq


};


#endif
