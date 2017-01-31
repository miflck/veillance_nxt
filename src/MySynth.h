//
//  MySynth.h
//  example_Basic
//
//  Created by Ant Dickinson on 16/11/2016.
//
//

#ifndef __example_Basic__MySynth__
#define __example_Basic__MySynth__

#include <stdio.h>
#include "ofMain.h"
#include "ofxTonic.h"
#include "ofSoundUnit.h"



using namespace Tonic;

class MySynth: public ofSoundSource{
    
public:
    
    MySynth();
    virtual ~MySynth();
    
    ofxTonicSynth synth;
    string getName() { return "soundSourceTonic"; }
    int	sampleRate;
    float volume;
    
    void setup(float _p);
      void update();
    void audioRequested (float * output, int bufferSize, int nChannels);

    void setSampleRate( int rate );


private:
    
};

#endif /* defined(__example_Basic__MySynth__) */
