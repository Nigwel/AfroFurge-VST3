#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/LookAndFeel.h"

class AfrologyAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AfrologyAudioProcessorEditor (AfrologyAudioProcessor&);
    ~AfrologyAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AfrologyAudioProcessor& audioProcessor;
    AfrolabsLookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AfrologyAudioProcessorEditor)
};
