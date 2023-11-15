#include "PresetManager.hpp"
#include "NoteBuilder.hpp"
#include "waveform.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


/*

 [Preset]
 Envelope = 1, 10, 0.9, 1500	
 Harmonic = 1, 0, 0, Sine

*/

static std::vector<std::string> getParams(const std::string& line)
{
    auto m = line.find("=") + 1;

    std::istringstream params(line.substr(m));
    std::vector<std::string> output;

    std::string token;
    while(std::getline(params, token, ','))
    {
        std::string param;
        std::istringstream(token) >> param;
        output.push_back(param);
    }

    return output;
}


static WaveType stringToWaveType(const std::string& line)
{
   if (line == "Sine") return WaveType::WAVE_SINE;
   if (line == "Square") return WaveType::WAVE_SQUARE;
   if (line == "Saw") return WaveType::WAVE_SAW;
   if (line == "Triangle") return WaveType::WAVE_TRIANGLE;

   return WaveType::WAVE_SINE;
}

void PresetFile::ReadFromFile(std::filesystem::path filePath)
{
    std::ifstream file(filePath);
    
    std::string line;

    std::shared_ptr<NoteBuilder> curr_preset = nullptr;

    while(std::getline(file, line))
    {
        if (line.find("[Preset]") != std::string::npos)
        {
            if(curr_preset != nullptr)
            {
                mNotePresets.push_back(curr_preset);
            }

            curr_preset = std::make_shared<NoteBuilder>(48000); // TODO obtain the sample freq from somewhere (or let NoteBuilder worry about that)
        }


        if (line.find("Envelope") != std::string::npos)
        {
            auto params = getParams(line);

            assert(params.size() == 4);

            std::cout << "Envelope params: " << std::endl;
            for (auto param : params)
            {
                std::cout << "Param: " << std::stof(param) << std::endl;
            }

            float attack = std::stof(params[0]);
            float decay = std::stof(params[1]);
            float sustain = std::stof(params[2]);
            float release = std::stof(params[3]);

            curr_preset->setBaseEnvelope({attack, decay, sustain, release});
        }

        if (line.find("Harmonic") != std::string::npos)
        {
            auto params = getParams(line);

            assert(params.size() == 4);

            std::cout << "Harmonic params: " << std::endl;
            for (auto param : params)
            {
                std::cout << "Param: " << param << std::endl;
            }

            float multiplier = std::stof(params[0]);
            float volume = std::stof(params[1]);
            float phase = std::stof(params[2]);
            WaveType type = stringToWaveType(params[3]);

            curr_preset->addHarmonic(multiplier, volume, phase, type);
        }
    }


    if(curr_preset != nullptr)
    {
        mNotePresets.push_back(curr_preset);
    }
}
