#pragma once
#include <JuceHeader.h>
class FXChain {
public:
    FXChain() = default;
    void prepareToPlay(double, int) {}
    void process(juce::AudioBuffer<float>&) {}
};
