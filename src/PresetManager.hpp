#pragma once

#include "NoteBuilder.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <vector>


class PresetManagerBase
{
public:
    PresetManagerBase() = default;
    virtual ~PresetManagerBase() = default;

    virtual const std::vector<std::shared_ptr<NoteBuilder>>& GetNotePresets() = 0;
};


class PresetFile : public PresetManagerBase
{
public:
    PresetFile() = default;
    virtual ~PresetFile() = default;

    virtual void ReadFromFile(std::filesystem::path filePath);

    const std::vector<std::shared_ptr<NoteBuilder>>& GetNotePresets() override { return mNotePresets; }

private:
    std::filesystem::path mFilename;

    std::vector<std::shared_ptr<NoteBuilder>> mNotePresets;
};


class YamlPresetFile : public PresetFile
{
public:
    YamlPresetFile() = default;
    virtual ~YamlPresetFile() = default;

    virtual void ReadFromFile(std::filesystem::path filePath) override;
};
