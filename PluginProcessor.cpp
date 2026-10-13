#include "PluginProcessor.h"
AfrogridProcessor::AfrogridProcessor():
 AudioProcessor(BusesProperties().withOutput("Output",juce::AudioChannelSet::stereo(),true)),
 state(*this,nullptr,"Parameters",makeLayout()) {}
juce::AudioProcessorValueTreeState::ParameterLayout AfrogridProcessor::makeLayout() {
 std::vector<std::unique_ptr<juce::RangedAudioParameter>> p;
 p.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"tempo",1},"Groove BPM",juce::NormalisableRange<float>(98.f,115.f,1.f),110.f));
 p.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"level",1},"Output Level",juce::NormalisableRange<float>(0.f,1.f,.01f),.75f));
 p.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{"run",1},"Groove Enabled",true));
 return {p.begin(),p.end()};
}
void AfrogridProcessor::prepareToPlay(double sampleRate,int) {core.prepare(sampleRate);}
bool AfrogridProcessor::isBusesLayoutSupported(const BusesLayout& l) const {
 return l.getMainOutputChannelSet()==juce::AudioChannelSet::stereo() && l.getMainInputChannelSet().isDisabled();
}
void AfrogridProcessor::processBlock(juce::AudioBuffer<float>& buffer,juce::MidiBuffer& midi) {
 juce::ScopedNoDenormals noDenormals; midi.clear(); buffer.clear();
 core.setBpm(double(state.getRawParameterValue("tempo")->load()));
 core.setGain(double(state.getRawParameterValue("level")->load()));
 core.setEnabled(state.getRawParameterValue("run")->load()>.5f);
 auto* left=buffer.getWritePointer(0); auto* right=buffer.getWritePointer(1);
 for(int i=0;i<buffer.getNumSamples();++i) left[i]=right[i]=core.tick();
}
juce::AudioProcessorEditor* AfrogridProcessor::createEditor() {
 return new juce::GenericAudioProcessorEditor(*this);
}
void AfrogridProcessor::getStateInformation(juce::MemoryBlock& dest) {
 auto xml=state.copyState().createXml(); copyXmlToBinary(*xml,dest);
}
void AfrogridProcessor::setStateInformation(const void* data,int bytes) {
 auto xml=getXmlFromBinary(data,bytes);
 if(xml && xml->hasTagName(state.state.getType())) state.replaceState(juce::ValueTree::fromXml(*xml));
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {return new AfrogridProcessor();}
