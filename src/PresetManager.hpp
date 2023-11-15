#pragma once

#include "NoteBuilder.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <vector>
#include <yaml-cpp/node/node.h>


class PresetManagerBase
{
public:
    PresetManagerBase() = default;
    virtual ~PresetManagerBase() = default;

    virtual std::vector<NoteBuilder> GetNotePresets() = 0;
};


class PresetFile : public PresetManagerBase
{
public:
    PresetFile() = default;
    virtual ~PresetFile() = default;

    virtual void ReadFromFile(std::filesystem::path filePath) = 0;

    std::vector<NoteBuilder> GetNotePresets() override { return mNotePresets; }

protected:
    std::filesystem::path mFilename;

    std::vector<NoteBuilder> mNotePresets;
};


class YamlPresetFile : public PresetFile
{
public:
    YamlPresetFile() = default;
    virtual ~YamlPresetFile() = default;

    virtual void ReadFromFile(std::filesystem::path filePath) override;

private:
    void ParsePreset(YAML::Node preset_node);
};
