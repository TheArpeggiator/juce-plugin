/*
  ==============================================================================


  ==============================================================================
*/

#ifndef SYNTHVOICE_H_INCLUDED
#define SYNTHVOICE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sine.h"
#include <stdlib.h>
#include "panner.h"
#include <math.h>
#include <stdio.h>

using namespace std;

struct MySound:public SynthesiserSound
{
    MySound() {}

    bool appliesToNote (int /*midiNoteNumber*/) override
    {
        return true;
    }
    bool appliesToChannel (int /*midiChannel*/) override
    {
        return true;
    }
};


struct MyVoice : public SynthesiserVoice
{
    MyVoice()
    {
        tailOff = true;
        panner.buildUserInterface(&panControl);
        panner.init(getSampleRate());
        audioBuffer = new float*[2];
        onOff = false;
        for(int i=0; i<panControl.getParamsCount(); i++)
            std::cout<<panControl.getParamAdress(i)<<endl;
    };

    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<MySound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        // converting MIDI note number into freq
        panControl.setParamValue("/syn/frequency",MidiMessage::getMidiNoteInHertz(midiNoteNumber));
        panControl.setParamValue("/syn/gain",0.4);
        panControl.setParamValue("/syn/gate",1);

        onOff = true;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        onOff = false; // end the note
        panControl.setParamValue("/syn/gate",0);
        tailOff = allowTailOff;
    }

    void pitchWheelMoved (int /*newValue*/) override
    {
        // Pitch wheel is an important standard MIDI feature that should be implemented
    }

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
        // Thats where you would change the value of the modulator index and frequency
        // if you wanted to control them with MIDI controllers
    }

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        // only compute block if note is on!
        if(envelope!=0||onOff)
        {
            audioBuffer[0] = new float[numSamples];
            audioBuffer[1] = new float[numSamples];
            panner.compute(numSamples,NULL,audioBuffer);
            envelope = 0;

            for(int j=0; j<numSamples; j++)
            {
                //panner.compute(1,NULL,audioBuffer);
                envelope+=abs(audioBuffer[0][j]);
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                {
                    outputBuffer.addSample (i, startSample, audioBuffer[i][j]);
                }
                ++startSample;

                envelope/=numSamples;

                // if tail off is disabled, we end the note right away, otherwise, we wait for envelope
                // to reach a safe value

                if(!onOff && (envelope < 0.001 || !tailOff))
                {
                    envelope = 0.0f;
                    clearCurrentNote();
                }
            }
        }
    }

private:
    bool onOff, tailOff;
    Pan panner;
    float **audioBuffer;
    float level, envelope;
    MapUI panControl;
};


#endif  // SYNTHVOICE_H_INCLUDED
