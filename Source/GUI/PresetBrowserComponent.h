#pragma once
#include <JuceHeader.h>
class PresetBrowserComponent : public juce::Component {
public:
    PresetBrowserComponent() = default;
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::black); }
    void resized() override {}
};
