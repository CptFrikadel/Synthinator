#include "NoteBuilder.hpp"
#include "PresetManager.hpp"
#include "waveform.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

void YamlPresetFile::ReadFromFile(std::filesystem::path filePath)
{
    YAML::Node presets = YAML::LoadFile(filePath.string());

    if (!presets["preset"]){
        std::cerr << "Invalid preset file! Could not find root preset node" << std::endl;
        return;
    }

    mNotePresets.clear();
    NoteBuilder builder(48000);

    YAML::Node preset_node = presets["preset"];

    if (!preset_node["harmonics"]){
        std::cerr << "Invalid preset, no harmonics defined!" << std::endl;
        return;
    }

    for (auto harmonic : preset_node["harmonics"]){
        auto type = harmonic["type"].as<std::string>();
        WaveType wavetype;
        auto freq = harmonic["freq"].as<float>();
        auto volume = harmonic["volume"].as<float>();
        auto phase = harmonic["phase"].as<float>();

        if (type == "Sine"){
            wavetype = WaveType::WAVE_SINE;
        } else if (type == "Square") {
            wavetype = WaveType::WAVE_SQUARE;
        } else if (type == "Saw") {
            wavetype = WaveType::WAVE_SAW;
        } else if (type == "Triangle"){
            wavetype = WaveType::WAVE_TRIANGLE;
        } else {
            std::cerr << "Ivalid wave type: " << type << std::endl;
            return;
        }

        std::cout << "Harmonic: " << std::endl 
            << "    type: " << type 
            << "    freq: " << freq 
            << "    volume: " << volume 
            << "    phase: " << phase 
            << std::endl;
        
        builder.addHarmonic(freq, volume, phase, wavetype);
    }


    // Envelope
    YAML::Node envelope = preset_node["envelope"];
    if (!envelope){
        std::cerr << "Invalid preset, no envelope defined!" << std::endl;
        return;
    }

    auto attack = envelope["attack"].as<float>();
    auto decay = envelope["decay"].as<float>();
    auto sustain = envelope["sustain"].as<float>();
    auto release = envelope["release"].as<float>();

    std::cout << "Envelope: " << std::endl 
        << "    attack: " << attack 
        << "    decay: " << decay 
        << "    sustain: " << sustain 
        << "    release: " << release 
        << std::endl;

    builder.setBaseEnvelope({attack, decay, sustain, release});
    mNotePresets.push_back(builder);
}
