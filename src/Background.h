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
    
    void setup(int _id);
    void update();
    void setNumWords(int _num);
    int getNumWords();

    

    void setSampleRate( int rate );
    void audioRequested (float * output, int bufferSize, int nChannels);
    
    


    int speed;

    ControlTrigger triggeroo;
    
    bool getBRemove();
    void setBRemove();
    
    
private:
    
    bool bRemove;

    //params
    int wordcount;
    int myId;
    
    int stretchBg;
    
    bool shouldPlay=false;
};

#endif /* defined(__example_Basic__MySynth__) */
