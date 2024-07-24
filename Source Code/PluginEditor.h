/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ZacharyWP02EQAudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::Slider::Listener
{
public:
    ZacharyWP02EQAudioProcessorEditor (ZacharyWP02EQAudioProcessor&);
    ~ZacharyWP02EQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // get called when a slider changes
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // Sliders
    juce::Slider mFilterFcSlider;
    juce::Slider mFilterQSlider;
    
    juce::Slider peakFilterQSlider;
    juce::Slider peakFilterFcSlider;
    juce::Slider peakFilterGainSlider;
    
    juce::Slider LSFilterFcSlider;
    juce::Slider LSFilterGainSlider;
    
    juce::Slider HSFilterFcSlider;
    juce::Slider HSFilterGainSlider;
    
    // Labels
    juce::Label peakFilterQLabel;
    juce::Label peakFilterFcLabel;
    juce::Label peakFilterGainLabel;
    
    juce::Label LSFilterFcLabel;
    juce::Label LSFilterGainLabel;
    
    juce::Label HSFilterFcLabel;
    juce::Label HSFilterGainLabel;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ZacharyWP02EQAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZacharyWP02EQAudioProcessorEditor)
};
