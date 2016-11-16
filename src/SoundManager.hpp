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
#include "ofxGui.h"


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

    void audioRequested (float * output, int bufferSize, int nChannels);
    
    bool bHide=true;
    
    void toggleGui();
    
  //  ofxIntSlider user1wordcount;
    
    ofParameter<float> user1wordcount;
    ofParameter<float> user1vowelcount;
    ofParameter<float> user1sylcont1;
    
    
    ofParameter<float> user2wordcount;
    ofParameter<float> user2vowelcount;
    ofParameter<float> user2sylcont1;
    
    
    ofParameter<float> user3wordcount;
    ofParameter<float> user3vowelcount;
    ofParameter<float> user3sylcont1;
    
    
    ofParameter<float> user4wordcount;
    ofParameter<float> user4vowelcount;
    ofParameter<float> user4sylcont1;
    

private:
    
    SoundManager();
    static SoundManager* instance;
    bool initialized;

    
    ofxTonicSynth synth;
    
    
    ofxPanel gui;
    

    ofxIntSlider user1sylcont2;
    ofxIntSlider user1sylcont3;
    ofxIntSlider user1sylcont4;
    ofxIntSlider user1sylcont5;
    ofxIntSlider user1sylcont6;
    ofxFloatSlider user1pan;
    ofxFloatSlider user1Zpos;
    
 /*   ofxIntSlider user2wordcount;
    ofxIntSlider user2vowelcount;
    ofxIntSlider user2sylcont1;*/
    ofxIntSlider user2sylcont2;
    ofxIntSlider user2sylcont3;
    ofxIntSlider user2sylcont4;
    ofxIntSlider user2sylcont5;
    ofxIntSlider user2sylcont6;
    ofxFloatSlider user2pan;
    ofxFloatSlider user2Zpos;
    
/*    ofxIntSlider user3wordcount;
    ofxIntSlider user3vowelcount;
    ofxIntSlider user3sylcont1;*/
    ofxIntSlider user3sylcont2;
    ofxIntSlider user3sylcont3;
    ofxIntSlider user3sylcont4;
    ofxIntSlider user3sylcont5;
    ofxIntSlider user3sylcont6;
    ofxFloatSlider user3pan;
    ofxFloatSlider user3Zpos;
    
  /*  ofxIntSlider user4wordcount;
    ofxIntSlider user4vowelcount;
    ofxIntSlider user4sylcont1;*/
    ofxIntSlider user4sylcont2;
    ofxIntSlider user4sylcont3;
    ofxIntSlider user4sylcont4;
    ofxIntSlider user4sylcont5;
    ofxIntSlider user4sylcont6;
    ofxFloatSlider user4pan;
    ofxFloatSlider user4Zpos;
    
    
};


#endif /* SoundManager_hpp */
