#pragma once
#include <JuceHeader.h>
class PresetManager {
public:
    PresetManager() = default;
    juce::StringArray getPresetNames() const { return {}; }
};
