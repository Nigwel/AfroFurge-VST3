#pragma once
#include <JuceHeader.h>
#include "DSP/FilterModule.h"
#include "DSP/StutterEngine.h"
#include "DSP/FXChain.h"
#include "Engine/PresetManager.h"

class AfrologyAudioProcessor  : public juce::AudioProcessor,
                                public juce::AudioProcessorValueTreeState::Listener
{
public:
    AfrologyAudioProcessor();
    ~AfrologyAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    // Audio Processor Value Tree State for Parameter Automation
    juce::AudioProcessorValueTreeState apvts;
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void parameterChanged (const juce::String& parameterID, float newValue) override;

    // Core Sample Engine
    juce::Synthesiser synthEngine;

private:
    // Custom DSP Chain
    StutterEngine stutterEngine;
    FilterModule  filterEngine;
    FXChain       fxChain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AfrologyAudioProcessor)
};
