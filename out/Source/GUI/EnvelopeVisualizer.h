#pragma once
#include <JuceHeader.h>
class EnvelopeVisualizer : public juce::Component {
public:
    EnvelopeVisualizer() = default;
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::black); }
    void resized() override {}
};
