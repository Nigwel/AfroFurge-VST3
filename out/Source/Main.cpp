#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

// This creates new instances of the plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AfrologyAudioProcessor();
}
