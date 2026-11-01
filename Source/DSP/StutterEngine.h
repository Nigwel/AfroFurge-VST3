#pragma once
#include <JuceHeader.h>
class StutterEngine {
public:
    StutterEngine() = default;
    void prepareToPlay(double, int) {}
    void process(juce::AudioBuffer<float>&) {}
};
