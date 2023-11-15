#include "PresetManager.hpp"
#include "NoteBuilder.hpp"
#include "waveform.hpp"



static WaveType stringToWaveType(const std::string& line)
{
   if (line == "Sine") return WaveType::WAVE_SINE;
   if (line == "Square") return WaveType::WAVE_SQUARE;
   if (line == "Saw") return WaveType::WAVE_SAW;
   if (line == "Triangle") return WaveType::WAVE_TRIANGLE;

   return WaveType::WAVE_SINE;
}


