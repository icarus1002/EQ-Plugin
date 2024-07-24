/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ZacharyWP02EQAudioProcessor::ZacharyWP02EQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Instantiating AudioParameters
    
    // Filter Cutoff parameter
    addParameter(mFilterFcParam = new juce::AudioParameterFloat("Filter Cutoff (Hz)", // parameter ID,
                                                                "FiltFc", // parameter name,
                                                                40.0f, // minValue,
                                                                10000.0f, // maxValue,
                                                                500.0f // defaultValue
                                                                ));
    // Filter Q Parameter
    addParameter(mFilterQParam = new juce::AudioParameterFloat("Filter Q", // parameter ID,
                                                               "FiltQ", // parameter name,
                                                               1.0f, // minValue,
                                                               10.0f, // maxValue,
                                                               3.0f // defaultValue
                                                               ));
    // Peaking Q Parameter
    addParameter(peakQParam = new juce::AudioParameterFloat("Peaking Q", // parameter ID,
                                                               "PeakQ", // parameter name,
                                                               0.5f, // minValue,
                                                               20.0f, // maxValue,
                                                               4.0f // defaultValue
                                                               ));
    
    // Peaking Fc Parameter
    addParameter(peakFcParam = new juce::AudioParameterFloat("Peaking Fc", // parameter ID,
                                                               "PeakFc", // parameter name,
                                                               125.0f, // minValue,
                                                               16000.0f, // maxValue,
                                                               1000.0f // defaultValue
                                                               ));
    
    // Peaking Gain Parameter
    addParameter(peakGainParam = new juce::AudioParameterFloat("Peaking Gain", // parameter ID,
                                                               "PeakGain", // parameter name,
                                                               -20.0f, // minValue,
                                                               20.0f, // maxValue,
                                                               0.0f // defaultValue
                                                               ));
    
    // Low Shelf Gain Parameter
    addParameter(LSGainParam = new juce::AudioParameterFloat("Low Shelf Gain", // parameter ID,
                                                               "LSGain", // parameter name,
                                                               -20.0f, // minValue,
                                                               20.0f, // maxValue,
                                                               0.0f // defaultValue
                                                               ));
    
    // Low Shelf Fc Parameter
    addParameter(LSFcParam = new juce::AudioParameterFloat("Low Shelf Fc (transition)", // parameter ID,
                                                               "LSFc", // parameter name,
                                                               50.0f, // minValue,
                                                               400.0f, // maxValue,
                                                               200.0f // defaultValue
                                                               ));
    
    // High Shelf Gain Parameter
    addParameter(HSGainParam = new juce::AudioParameterFloat("High Shelf Gain", // parameter ID,
                                                               "HSGain", // parameter name,
                                                               -20.0f, // minValue,
                                                               20.0f, // maxValue,
                                                               0.0f // defaultValue
                                                               ));
    
    // High Shelf Fc Parameter
    addParameter(HSFcParam = new juce::AudioParameterFloat("High Shelf Fc (transition)", // parameter ID,
                                                               "HSFc", // parameter name,
                                                               1000.0f, // minValue,
                                                               15000.0f, // maxValue,
                                                               10000.0f // defaultValue
                                                               ));
}

ZacharyWP02EQAudioProcessor::~ZacharyWP02EQAudioProcessor()
{
}

//==============================================================================
const juce::String ZacharyWP02EQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ZacharyWP02EQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ZacharyWP02EQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ZacharyWP02EQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ZacharyWP02EQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ZacharyWP02EQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ZacharyWP02EQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ZacharyWP02EQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ZacharyWP02EQAudioProcessor::getProgramName (int index)
{
    return {};
}

void ZacharyWP02EQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ZacharyWP02EQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mFs = sampleRate;
}

void ZacharyWP02EQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ZacharyWP02EQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ZacharyWP02EQAudioProcessor::calcAlgorithmParams()
{
    // Get User Parameter Values
    float fc = mFilterFcParam->get();
    float Q  = mFilterQParam->get();
    
    
    
    // Calculate Filter Coefficients
    float coeffs[5]; // an array of 5 floats for filter coeffs: [b0, b1, b2, a1, a2]
    Mu45FilterCalc::calcCoeffsLPF(coeffs, fc, Q, mFs);

    
    // setting coefficients for each filter
    mFilterL.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    mFilterR.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
    DBG("Fc = "<<fc);       // debugging
    
    // User Parameters for Peak Filter
    fc = peakFcParam->get();
    Q = peakQParam->get();
    float gainDb = peakGainParam->get();
    
    // Calculate Filter Coefficients
    Mu45FilterCalc::calcCoeffsPeak(coeffs, fc, gainDb, Q, mFs);
    
    // setting coefficients for each filter
    peakFilterL.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    peakFilterR.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
    DBG("Fc = "<<fc); // more debugging
    
    
    // User Parameters for Low Shelf Filter
    fc = LSFcParam->get();
    gainDb = LSGainParam->get();
    
    // Calculate Filter Coefficients
    Mu45FilterCalc::calcCoeffsLowShelf(coeffs, fc, gainDb, mFs);
    
    // setting coefficients for each filter
    LSFilterL.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    LSFilterR.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
    // User Parameters for High Shelf Filter
    fc = HSFcParam->get();
    gainDb = HSGainParam->get();
    
    // Calculate Filter Coefficients
    Mu45FilterCalc::calcCoeffsHighShelf(coeffs, fc, gainDb, mFs);
    
    // setting coefficients for each filter
    HSFilterL.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    HSFilterR.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
    
    
    
}

// Calculates filter coefficients for the peaking filter
/*
void ZacharyWP02EQAudioProcessor::calcPeakFilterCoeffs()
{
    float Q, fc, gainDb, wcT, K, V, D;
    float b0, b1, b2, a1, a2;
    
    Q      = peakQParam->get();
    fc     = peakFcParam->get();
    gainDb = peakGainParam->get();
    
    wcT = 2*stk::PI*fc/mFs;
    K   = tan(wcT/2);
    
    if (gainDb >= 0) {
        // boost or peak
        V  = powf(10, gainDb/20);
        b0 = 1 + V*K/Q + K*K;
        b1 = 2*(K*K - 1);
        b2 = 1 - V*K/Q + K*K;
        D  = 1 + K/Q + K*K;
        a1 = 2*(K*K - 1);
        a2 = 1 - K/Q + K*K;
    }
    else {
        // cut or notch
        V  = pow(10, -gainDb/20);
        b0 = 1 + K/Q + K*K;
        b1 = 2*(K*K - 1);
        b2 = 1 - K/Q + K*K;
        D  = 1 + V*K/Q + K*K;
        a1 = 2*(K*K - 1);
        a2 = 1 - V*K/Q + K*K;
    }
    // normalize by D
    b0 = b0 / D;
    b1 = b1 / D;
    b2 = b2 / D;
    a1 = a1 / D;
    a2 = a2 / D;
    
    peakFilterL.setCoefficients(b0, b1, b2, a1, a2);
    peakFilterR.setCoefficients(b0, b1, b2, a1, a2);
    
}
*/

void ZacharyWP02EQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // update alg parameters
    calcAlgorithmParams();
    
    // get left and right audio buffers
    auto* channelDataLeft = buffer.getWritePointer(0);
    auto* channelDataRight = buffer.getWritePointer(1);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int samp = 0; samp < buffer.getNumSamples(); samp++)
    {
        channelDataLeft[samp] = mFilterL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = mFilterR.tick(channelDataRight[samp]);
        
        channelDataLeft[samp] = peakFilterL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = peakFilterR.tick(channelDataRight[samp]);
        
        channelDataLeft[samp] = LSFilterL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = LSFilterR.tick(channelDataRight[samp]);
        
        channelDataLeft[samp] = HSFilterL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = HSFilterR.tick(channelDataRight[samp]);
        
        
        
        

        // ..do something to the data...
    }
}

//==============================================================================
bool ZacharyWP02EQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ZacharyWP02EQAudioProcessor::createEditor()
{
    return new ZacharyWP02EQAudioProcessorEditor (*this);
}

//==============================================================================
void ZacharyWP02EQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ZacharyWP02EQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ZacharyWP02EQAudioProcessor();
}
