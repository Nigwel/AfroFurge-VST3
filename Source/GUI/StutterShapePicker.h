#pragma once
#include <JuceHeader.h>
class StutterShapePicker : public juce::Component {
public:
    StutterShapePicker() = default;
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::black); }
    void resized() override {}
};
