//
//  MySynth.h
//  example_Basic
//
//  Created by Ant Dickinson on 16/11/2016.
//
//

#ifndef Background_h
#define Background_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxTonic.h"
#include "ofSoundUnit.h"



using namespace Tonic;

class Background: public ofSoundSource{
    
public:
    
    ofxTonicSynth synth;
    string getName() { return "soundSourceTonic"; }
    int	sampleRate;
    float volume;
    
    void setup();
    void update();
    void setNumWords(int _num);
    int getNumWords();

    

    void setSampleRate( int rate );
    void audioRequested (float * output, int bufferSize, int nChannels);
    
    




private:
    //params
    int wordcount;
};

#endif /* defined(__example_Basic__MySynth__) */
