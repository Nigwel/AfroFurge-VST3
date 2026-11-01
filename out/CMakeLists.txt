cmake_minimum_required(VERSION 3.22)
project(AFROLOGY_PLUGIN VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(juce GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.12 GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(juce)

juce_add_plugin(Afrolabs
    COMPANY_NAME "ManifxtAudio"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    PLUGIN_MANUFACTURER_CODE Mnfx
    PLUGIN_CODE Aflb
    FORMATS VST3 Standalone
    PRODUCT_NAME "AfroLogy VST3"
)

target_sources(Afrolabs PRIVATE
    Source/Main.cpp
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/GUI/LookAndFeel.cpp
    Source/Engine/SampleVoice.cpp
    Source/Engine/SampleSound.cpp
    Source/Engine/PresetManager.cpp
    Source/Engine/ReverseProcessor.cpp
    Source/DSP/StutterEngine.cpp
    Source/DSP/FilterModule.cpp
    Source/DSP/FXChain.cpp
    Source/DSP/GlideController.cpp
    Source/GUI/WaveformViewer.cpp
    Source/GUI/EnvelopeVisualizer.cpp
    Source/GUI/StutterShapePicker.cpp
    Source/GUI/PresetBrowserComponent.cpp
)

target_include_directories(Afrolabs PRIVATE Source)

target_compile_definitions(Afrolabs PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(Afrolabs PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_extra
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags
)
