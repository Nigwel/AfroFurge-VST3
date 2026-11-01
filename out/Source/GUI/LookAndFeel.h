#pragma once
#include <JuceHeader.h>

namespace AfroColors
{
    const juce::Colour BackgroundDark    = juce::Colour::fromRGB(15, 17, 18);
    const juce::Colour PanelBackground  = juce::Colour::fromRGB(24, 27, 29);
    const juce::Colour NeonGreen        = juce::Colour::fromRGB(0, 255, 102);
    const juce::Colour TextMuted        = juce::Colour::fromRGB(140, 145, 150);
    const juce::Colour TextBright       = juce::Colour::fromRGB(240, 240, 240);
}

class AfrolabsLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AfrolabsLookAndFeel() = default;
    ~AfrolabsLookAndFeel() override = default;

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                           juce::Slider& slider) override;
};
