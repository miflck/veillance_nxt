//
//  ForegroundSound.hpp
//  customSynthClass
//
//  Created by Flückiger Michael on 28.11.16.
//
//

#ifndef ForegroundSound_hpp
#define ForegroundSound_hpp
#include <stdio.h>
#include "ofMain.h"
#include "ofxTonic.h"
#include "ofSoundUnit.h"


using namespace Tonic;



class ForegroundSound: public ofSoundSource{
    
public:
    ForegroundSound();
    virtual ~ForegroundSound();

    
    ofxTonicSynth synth;
    string getName() { return "ForeGroundSound"; }
    void setSampleRate( int rate );
    void audioRequested (float * output, int bufferSize, int nChannels);
    float volume;

    
    void setup();
    void update();
    
    //not really need that, better go for parseVovels
    void setVowels(string _vowels);
    
    void parseVowels(string _vowels);
    void setNumSyllables(int _num);
    
    void setPosition (ofVec3f _pos);
    void setTimingSubDiv(int _timeSubDiv);
    
    bool getBRemove();

    void setMaxZ(int _maxZ);
    
    
private:
    //flag to remove sound if reached foreground;
    bool bRemove;
    
    string vowelsString;
    int vowelsCount;
    
    int numSyllables;
    
    int timeSubDiv;
    
    ofVec3f position;
    int maxZ;
    float scaledZpos;
    
    
    int maxX;
    int minX;
    float scaledXpos;
    
    int viewportwidth;
    
    
    ControlTrigger fgtrig;
    
    
  /* vector< int > fgnotes= {0,0,0,0,0,0,0};
    vector< int > fgbeats = {0,1,1,1,1,1,1,1,1,1,1};
    vector< int > scale = {220, 880 ,261,329,329,392,392,440,220};
    */
    
    vector< int > fgnotes= {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    vector< int > fgbeats = {0,1,1,1,1,1,1,1,1,1,1};
    // SCALE HERE IN MIDI NOTE NUMBERS FROM KEYBOARD http://newt.phys.unsw.edu.au/jw/graphics/notesinvert.GIF
    vector< int > scale = {64,66,67,69,71,72,74,76,64,66,67,69,71,72,74,76};
    
    int beat;

/*
    
    int fgnotes[7];
    int fgbeats[11];
      int scale[7];
 
    */
    
    float userPan;
    int sylcont1,sylcont2,sylcont3,sylcont4,sylcont5,sylcont6;
    
    int	sampleRate;
    float volumeForMixer;
    
    int z;
    int transpose,transposeRandom;

    
};




#endif /* ForeGroundSound_hpp */