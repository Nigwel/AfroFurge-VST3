#pragma once
#include <JuceHeader.h>
class WaveformViewer : public juce::Component {
public:
    WaveformViewer() = default;
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::black); }
    void resized() override {}
};
