#include "PluginProcessor.h"
#include "PluginEditor.h"

AfrologyAudioProcessor::AfrologyAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                       ),
       apvts (*this, nullptr, "Parameters", createParameterLayout())
#endif
{
    apvts.addParameterListener("ATTACK", this);
    apvts.addParameterListener("DECAY", this);
    apvts.addParameterListener("SUSTAIN", this);
    apvts.addParameterListener("RELEASE", this);
}

AfrologyAudioProcessor::~AfrologyAudioProcessor()
{
}

const juce::String AfrologyAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AfrologyAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AfrologyAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AfrologyAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AfrologyAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AfrologyAudioProcessor::getNumPrograms()
{
    return 1;
}

int AfrologyAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AfrologyAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AfrologyAudioProcessor::getProgramName (int index)
{
    return {};
}

void AfrologyAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void AfrologyAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synthEngine.setCurrentPlaybackSampleRate (sampleRate);
}

void AfrologyAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AfrologyAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void AfrologyAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    midiMessages.clear();
}

void AfrologyAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    juce::ignoreUnused(parameterID, newValue);
}

bool AfrologyAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* AfrologyAudioProcessor::createEditor()
{
    return new AfrologyAudioProcessorEditor (*this);
}

void AfrologyAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void AfrologyAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout AfrologyAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // ADSR Envelope Parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>(1.0f, 2000.0f, 1.0f, 0.3f), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>(10.0f, 5000.0f, 1.0f, 0.3f), 2000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>(10.0f, 5000.0f, 1.0f, 0.3f), 400.0f));

    // Stutter / Chopper Parameters
    params.push_back(std::make_unique<juce::AudioParameterChoice>("STUTTER_RATE", "Stutter Rate", juce::StringArray{"1/4", "1/8", "1/16", "1/32"}, 2));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("STUTTER_SHAPE", "Stutter Shape", juce::StringArray{"Square", "Triangle", "Saw", "StepPulse"}, 0));

    // Filter Module Parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOW_CUT", "Low Cut", juce::NormalisableRange<float>(20.0f, 2000.0f, 1.0f, 0.3f), 50.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HIGH_CUT", "High Cut", juce::NormalisableRange<float>(1000.0f, 20000.0f, 1.0f, 0.3f), 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTER_SLOPE", "Filter Slope", juce::StringArray{"12dB", "24dB", "36dB", "48dB"}, 1));

    // FX Controls
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERB_MIX", "Reverb Mix", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.60f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DELAY_AMT", "Delay Amount", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.30f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUS_MIX", "Chorus Mix", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.50f));

    return { params.begin(), params.end() };
}

// This creates new instances of the plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AfrologyAudioProcessor();
}
