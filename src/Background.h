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
    
    
    int seqlength = 0;
    float bgvol;
    
    // with x and userbgbeat something is not right. you reset x if its bigger than sequence, but sequence is equal wordcount. so if wordcount is bigger than 64 you get an error accessing userbgbeat[x]
    int x = 0;
    int userbgbeat[64] = {};
    int userbgnotes[9] = {};
    
    
private:
    
    bool bRemove;

    //params
    int wordcount;
    int myId;
    
    int stretchBg;
    
    bool shouldPlay=false;
};

#endif /* defined(__example_Basic__MySynth__) */
