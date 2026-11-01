#include "PluginProcessor.h"
#include "PluginEditor.h"

AfrologyAudioProcessorEditor::AfrologyAudioProcessorEditor (AfrologyAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel (&lookAndFeel);
    setSize (900, 600);
}

AfrologyAudioProcessorEditor::~AfrologyAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

void AfrologyAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (AfroColors::BackgroundDark);
    g.setColour (AfroColors::NeonGreen);
    g.setFont (juce::Font (24.0f));
    g.drawText ("AfroLogy", getLocalBounds().removeFromTop (40), juce::Justification::centred, true);
}

void AfrologyAudioProcessorEditor::resized()
{
}
