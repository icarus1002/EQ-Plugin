/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ZacharyWP02EQAudioProcessorEditor::ZacharyWP02EQAudioProcessorEditor (ZacharyWP02EQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // sliders and other gui components
    auto& params = audioProcessor.getParameters();
    
    /*
    // Cutoff Frequency Slider
    juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
    mFilterFcSlider.setBounds(0, 0, 100, 160); // x, y, width, height
    mFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFilterFcSlider.setRange(audioParam->range.start, audioParam->range.end);
    mFilterFcSlider.setValue(*audioParam);
    mFilterFcSlider.addListener(this);
    addAndMakeVisible(mFilterFcSlider);
    
    // Q Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
    mFilterQSlider.setBounds(0, 190, 100, 80); // x, y, width, height
    mFilterQSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mFilterQSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFilterQSlider.setRange(audioParam->range.start, audioParam->range.end);
    mFilterQSlider.setValue(*audioParam);
    mFilterQSlider.addListener(this);
    addAndMakeVisible(mFilterQSlider);
     */
    
    // LS Gain Slider
    juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(5);
    LSFilterGainSlider.setBounds(0, 170, 150, 120); // x, y, width, height
    LSFilterGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    LSFilterGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    LSFilterGainSlider.setTextValueSuffix("dB");
    LSFilterGainSlider.setRange(audioParam->range.start, audioParam->range.end);
    LSFilterGainSlider.setValue(*audioParam);
    LSFilterGainSlider.addListener(this);
    addAndMakeVisible(LSFilterGainSlider);
    
    LSFilterGainLabel.setText("Low Shelf", juce::dontSendNotification);
    LSFilterGainLabel.attachToComponent(&LSFilterGainSlider, false);
    LSFilterGainLabel.setJustificationType(juce::Justification::centredTop);
    LSFilterGainLabel.setColour(LSFilterGainLabel.textColourId, juce::Colours::black);
    addAndMakeVisible(LSFilterGainLabel);
    
    // LS Fc Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(6);
    LSFilterFcSlider.setBounds(0, 0, 150, 120); // x, y, width, height
    LSFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    LSFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    LSFilterFcSlider.setTextValueSuffix("Hz");
    LSFilterFcSlider.setRange(audioParam->range.start, audioParam->range.end);
    LSFilterFcSlider.setValue(*audioParam);
    LSFilterFcSlider.addListener(this);
    addAndMakeVisible(LSFilterFcSlider);
    
    /*
    LSFilterFcLabel.setText("LS Gain", juce::dontSendNotification);
    LSFilterFcLabel.attachToComponent(&LSFilterFcSlider, false);
    LSFilterFcLabel.setJustificationType(juce::Justification::centredTop);
    LSFilterFcLabel.setColour(LSFilterFcLabel.textColourId, juce::Colours::black);
    addAndMakeVisible(LSFilterFcLabel);
     */
    
    // HS Gain Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(7);
    HSFilterGainSlider.setBounds(260, 170, 150, 120); // x, y, width, height
    HSFilterGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    HSFilterGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    HSFilterGainSlider.setTextValueSuffix("dB");
    HSFilterGainSlider.setRange(audioParam->range.start, audioParam->range.end);
    HSFilterGainSlider.setValue(*audioParam);
    HSFilterGainSlider.addListener(this);
    addAndMakeVisible(HSFilterGainSlider);
    
    HSFilterGainLabel.setText("High Shelf", juce::dontSendNotification);
    HSFilterGainLabel.attachToComponent(&HSFilterGainSlider, false);
    HSFilterGainLabel.setJustificationType(juce::Justification::centredTop);
    HSFilterGainLabel.setColour(HSFilterGainLabel.textColourId, juce::Colours::black);
    addAndMakeVisible(HSFilterGainLabel);
    
    // HS Fc Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(8);
    HSFilterFcSlider.setBounds(260, 0, 150, 120); // x, y, width, height
    HSFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    HSFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    HSFilterFcSlider.setTextValueSuffix("Hz");
    HSFilterFcSlider.setRange(audioParam->range.start, audioParam->range.end);
    HSFilterFcSlider.setValue(*audioParam);
    HSFilterFcSlider.addListener(this);
    addAndMakeVisible(HSFilterFcSlider);
    
    /*
    HSFilterFcLabel.setText("LS Gain", juce::dontSendNotification);
    HSFilterFcLabel.attachToComponent(&HSFilterFcSlider, false);
    HSFilterFcLabel.setJustificationType(juce::Justification::centredTop);
    HSFilterFcLabel.setColour(HSFilterFcLabel.textColourId, juce::Colours::black);
    addAndMakeVisible(HSFilterFcLabel);
     */
    
    // Peak Q Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
    peakFilterQSlider.setBounds(150, 200, 100, 80); // x, y, width, height
    peakFilterQSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    peakFilterQSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    peakFilterQSlider.setRange(audioParam->range.start, audioParam->range.end);
    peakFilterQSlider.setValue(*audioParam);
    peakFilterQSlider.addListener(this);
    addAndMakeVisible(peakFilterQSlider);
    
    /*
    peakFilterQLabel.setText("LS Gain", juce::dontSendNotification);
    peakFilterQLabel.attachToComponent(&peakFilterQSlider, false);
    peakFilterQLabel.setJustificationType(juce::Justification::centredTop);
    peakFilterQLabel.setColour(peakFilterQLabel.textColourId, juce::Colours::black);
    addAndMakeVisible(peakFilterQLabel);
     */
    
    // Peak Fc Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
    peakFilterFcSlider.setBounds(150, 10, 100, 80); // x, y, width, height
    peakFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    peakFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    peakFilterFcSlider.setTextValueSuffix("Hz");
    peakFilterFcSlider.setRange(audioParam->range.start, audioParam->range.end);
    peakFilterFcSlider.setValue(*audioParam);
    peakFilterFcSlider.addListener(this);
    addAndMakeVisible(peakFilterFcSlider);
    
    /*
    peakFilterFcLabel.setText("LS Gain", juce::dontSendNotification);
    peakFilterFcLabel.attachToComponent(&peakFilterFcSlider, false);
    peakFilterFcLabel.setJustificationType(juce::Justification::centredTop);
    peakFilterFcLabel.setColour(peakFilterFcLabel.textColourId, juce::Colours::black);
    addAndMakeVisible(peakFilterFcLabel);
     */
    
    // Peak Gain Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(4);
    peakFilterGainSlider.setBounds(150, 110, 100, 80); // x, y, width, height
    peakFilterGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //mFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    peakFilterGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    peakFilterGainSlider.setTextValueSuffix("dB");
    peakFilterGainSlider.setRange(audioParam->range.start, audioParam->range.end);
    peakFilterGainSlider.setValue(*audioParam);
    peakFilterGainSlider.addListener(this);
    addAndMakeVisible(peakFilterGainSlider);
    
    peakFilterGainLabel.setText("Peak", juce::dontSendNotification);
    peakFilterGainLabel.attachToComponent(&peakFilterGainSlider, false);
    peakFilterGainLabel.setJustificationType(juce::Justification::centredRight);
    peakFilterGainLabel.setColour(peakFilterGainLabel.textColourId, juce::Colours::black);
    addAndMakeVisible(peakFilterGainLabel);
}

ZacharyWP02EQAudioProcessorEditor::~ZacharyWP02EQAudioProcessorEditor()
{
}

void ZacharyWP02EQAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    auto& params = audioProcessor.getParameters();
    
    /*
    if (slider == &mFilterFcSlider)
    {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
        *audioParam = mFilterFcSlider.getValue(); // set the AudioParameter
        DBG("Fc Slider Changed");
    }
    else if (slider == &mFilterQSlider)
    {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
        *audioParam = mFilterQSlider.getValue(); // set the AudioParameter
        DBG("Q Slider Changed");
    }
     */
    
    // compare pointer to slider that was changed w/ address of our slider
    if (slider == &peakFilterQSlider)
    {
        // get a pointer to the first param in the processor
        juce::AudioParameterFloat* peakFilterQParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
        
        // use value from slider to set param in processor
        float sliderValue = peakFilterQSlider.getValue();
        *peakFilterQParam = sliderValue;     // set the param
        
        
        // we can use DBG() for simple print debugging
        DBG("Volume Slider Changed to " << sliderValue);
    }
    if (slider == &peakFilterFcSlider)
    {
        // get a pointer to the second param in the processor
        juce::AudioParameterFloat* peakFilterFcParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
        
        // use value from slider to set param in processor
        float sliderValue = peakFilterFcSlider.getValue();
        *peakFilterFcParam = sliderValue;     // set the param
        
        
        // we can use DBG() for simple print debugging
        DBG("Balance Slider Changed to " << sliderValue);
    }
    if (slider == &peakFilterGainSlider)
    {
        juce::AudioParameterFloat* peakFilterGainParam = (juce::AudioParameterFloat*)params.getUnchecked(4);
        
        float sliderValue = peakFilterGainSlider.getValue();
        *peakFilterGainParam = sliderValue;
        
        
        DBG("Volume Slider Changed to " << sliderValue);
    }
    if (slider == &LSFilterGainSlider)
    {
        juce::AudioParameterFloat* LSFilterGainParam = (juce::AudioParameterFloat*)params.getUnchecked(5);
        
        float sliderValue = LSFilterGainSlider.getValue();
        *LSFilterGainParam = sliderValue;
        
        
        DBG("Balance Slider Changed to " << sliderValue);
    }
    if (slider == &LSFilterFcSlider)
    {
        juce::AudioParameterFloat* LSFilterFcParam = (juce::AudioParameterFloat*)params.getUnchecked(6);
        
        float sliderValue = LSFilterFcSlider.getValue();
        *LSFilterFcParam = sliderValue;
        
        
        DBG("Volume Slider Changed to " << sliderValue);
    }
    if (slider == &HSFilterGainSlider)
    {
        juce::AudioParameterFloat* HSFilterGainParam = (juce::AudioParameterFloat*)params.getUnchecked(7);
        
        float sliderValue = HSFilterGainSlider.getValue();
        *HSFilterGainParam = sliderValue;
        
        
        DBG("Balance Slider Changed to " << sliderValue);
    }
    if (slider == &HSFilterFcSlider)
    {
        juce::AudioParameterFloat* HSFilterFcParam = (juce::AudioParameterFloat*)params.getUnchecked(8);
        
        float sliderValue = HSFilterFcSlider.getValue();
        *HSFilterFcParam = sliderValue;
        
        
        DBG("Volume Slider Changed to " << sliderValue);
    }
    
}

//==============================================================================
void ZacharyWP02EQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ZacharyWP02EQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
