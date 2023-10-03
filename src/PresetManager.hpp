#pragma once

#include "NoteBuilder.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <vector>



class PresetManager
{
public:
    PresetManager() = default;
    virtual ~PresetManager() = default;

    void ReadFromFile(std::filesystem::path filePath);

    const std::vector<std::shared_ptr<NoteBuilder>>& GetNotePresets() { return mNotePresets; }


private:
    std::filesystem::path mFilename;

    std::vector<std::shared_ptr<NoteBuilder>> mNotePresets;

};
