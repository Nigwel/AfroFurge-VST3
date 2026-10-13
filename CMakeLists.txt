cmake_minimum_required(VERSION 3.22)
project(AFROGRID VERSION 0.2.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(juce GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.12 GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(juce)
juce_add_plugin(AFROGRID
 COMPANY_NAME "JG BeatsLab" BUNDLE_ID "com.jgbeatslab.afrogrid"
 PLUGIN_MANUFACTURER_CODE JGBL PLUGIN_CODE AgR1
 FORMATS VST3 PRODUCT_NAME "AFROGRID"
 IS_SYNTH TRUE NEEDS_MIDI_INPUT TRUE NEEDS_MIDI_OUTPUT FALSE
 COPY_PLUGIN_AFTER_BUILD FALSE)
target_sources(AFROGRID PRIVATE src/PluginProcessor.cpp src/PluginProcessor.h src/GrooveCore.h)
target_compile_definitions(AFROGRID PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)
target_link_libraries(AFROGRID PRIVATE juce::juce_audio_utils juce::juce_audio_processors juce::juce_dsp PUBLIC juce::juce_recommended_config_flags juce::juce_recommended_warning_flags)
