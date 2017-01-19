//
//  SoundManager.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 15.11.16.
//
//

#ifndef SoundManager_hpp
#define SoundManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxTonic.h"
#include "Background.h"
#include "ForegroundSound.hpp"
#include "ofxReverb.h"


using namespace Tonic;



//for convenience
#define SoundM SoundManager::getInstance()

class SoundManager : public ofBaseApp{
    
public:
    
    static SoundManager* getInstance();
    void initialize();
    bool isInitialized();
    

    
    void update();
    void draw();

   // void audioRequested (float * output, int bufferSize, int nChannels);
    

    
    ForegroundSound * addForegroundSound(int _numSyllables,string _vowels,ofVec3f _p);
    
  
    
    
    // NewStuff -------------------------------------------------------------------
    
    void audioOut(float * output, int bufferSize, int nChannels);
    ofSoundStream soundStream;
    
    ofSoundMixer mixer;

    
    vector< ForegroundSound * > foregrounds;
    vector< ForegroundSound * > removedforegrounds;

    
    
    Background * addBackgroundSound();

    vector< Background * > backgrounds;

    
    
    //Reverb
    float 	volume;
    ofxReverb	reverb;
    float		wetness,verbRoomSize,verbDamp,verbWidth;
    float		reverbOUT;
    bool bReverb = false;
    
    
    
    void deleteAllDeletedSounds();

private:
    
    SoundManager();
    static SoundManager* instance;
    bool initialized;

    
    
    
};


#endif /* SoundManager_hpp */
