/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Mu45FilterCalc/Mu45FilterCalc.h"
#include "StkLite-4.6.2/BiQuad.h"


//==============================================================================
/**
*/
class ZacharyWP02EQAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ZacharyWP02EQAudioProcessor();
    ~ZacharyWP02EQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    void calcAlgorithmParams();
    //void calcPeakFilterCoeffs();
    //void calcLSFilterCoeffs();
    
    // user parameters
    juce::AudioParameterFloat* mFilterFcParam;      // low pass filter parameters
    juce::AudioParameterFloat* mFilterQParam;
    juce::AudioParameterFloat* peakQParam;          // peak filter parameters
    juce::AudioParameterFloat* peakFcParam;
    juce::AudioParameterFloat* peakGainParam;
    juce::AudioParameterFloat* LSGainParam;         // low shelf filter parameters
    juce::AudioParameterFloat* LSFcParam;
    juce::AudioParameterFloat* HSGainParam;         // high shelf filter parameters
    juce::AudioParameterFloat* HSFcParam;
    
    // objects needed
    stk::BiQuad mFilterL, mFilterR;                 // low pass filters
    float mFs;                                      // Sampling Rate
    
    stk::BiQuad peakFilterL, peakFilterR;           // peak filters
    stk::BiQuad LSFilterL, LSFilterR;               // low shelf filters
    stk::BiQuad HSFilterL, HSFilterR;               // high shelf filters
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZacharyWP02EQAudioProcessor)
};
