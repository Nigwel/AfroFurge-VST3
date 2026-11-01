#pragma once
#include <JuceHeader.h>
class GlideController {
public:
    GlideController() = default;
    void prepareToPlay(double, int) {}
    void process(juce::AudioBuffer<float>&) {}
};
