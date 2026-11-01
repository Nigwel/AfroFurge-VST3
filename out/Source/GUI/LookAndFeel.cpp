#include "LookAndFeel.h"

void AfrolabsLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                            float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                                            juce::Slider& slider)
{
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(4.0f);
    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto centreX = bounds.getCentreX();
    auto centreY = bounds.getCentreY();
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Track Outer Circle
    g.setColour(juce::Colour::fromRGB(35, 40, 43));
    g.drawEllipse(centreX - radius, centreY - radius, radius * 2.0f, radius * 2.0f, 2.5f);

    // Active Neon Green Arc Path
    juce::Path arcPath;
    arcPath.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
    g.setColour(AfroColors::NeonGreen);
    g.strokePath(arcPath, juce::PathStrokeOptions(3.0f, juce::PathStrokeOptions::curved, juce::PathStrokeOptions::rounded));

    // Pointer Indicator Line
    juce::Path pointer;
    auto pointerLength = radius * 0.65f;
    pointer.addRectangle(-1.5f, -radius, 3.0f, pointerLength);
    pointer.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(AfroColors::NeonGreen);
    g.fillPath(pointer);
}
