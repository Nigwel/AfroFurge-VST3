#pragma once
#include <JuceHeader.h>
#include "GrooveCore.h"
class AfrogridProcessor final : public juce::AudioProcessor {
public:
 AfrogridProcessor();
 void prepareToPlay(double sampleRate,int maximumExpectedSamplesPerBlock) override;
 void releaseResources() override {}
 bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
 juce::AudioProcessorEditor* createEditor() override;
 bool hasEditor() const override {return true;}
 const juce::String getName() const override {return "AFROGRID";}
 bool acceptsMidi() const override {return true;}
 bool producesMidi() const override {return false;}
 bool isMidiEffect() const override {return false;}
 double getTailLengthSeconds() const override {return 0.3;}
 int getNumPrograms() override {return 1;}
 int getCurrentProgram() override {return 0;}
 void setCurrentProgram(int) override {}
 const juce::String getProgramName(int) override {return "Lagos Pocket 01";}
 void changeProgramName(int,const juce::String&) override {}
 void getStateInformation(juce::MemoryBlock&) override;
 void setStateInformation(const void*,int) override;
private:
 juce::AudioProcessorValueTreeState state;
 afrogrid::GrooveCore core;
 static juce::AudioProcessorValueTreeState::ParameterLayout makeLayout();
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AfrogridProcessor)
};
