#pragma once
#include <JuceHeader.h>
class FilterModule {
public:
    FilterModule() = default;
    void prepareToPlay(double, int) {}
    void process(juce::AudioBuffer<float>&) {}
};
