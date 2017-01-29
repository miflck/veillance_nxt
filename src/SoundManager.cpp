//
//  SoundManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 15.11.16.
//
//

#include "SoundManager.hpp"

SoundManager* SoundManager::instance = 0;
SoundManager* SoundManager::getInstance() {
    if (!instance) {
        instance = new SoundManager();
    }
    return instance;
}


SoundManager::SoundManager(){
}

//--------------------------------------------------------------
void SoundManager::initialize(){
    
    initialized=true;
    cout<<"init SoundManager"<<endl;
    
    //ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    
    
    int bufferSize		= 2048;
    int sampleRate 		= 44100;
    
    soundStream.setup(2, 0, 44100, bufferSize, 4);
    soundStream.setOutput(this);

    volume				= 0.81f;
    wetness				= 0.2f;
    verbRoomSize		= 0.99f;
    verbDamp			= 0.2f;
    verbWidth			= 0.99f;
   
    
    
}

//--------------------------------------------------------------
void SoundManager::update(){
    //Check if we have to remove a foreground, else update it
   /* for (int i=0;i<foregrounds.size();i++){
        if(foregrounds[i]->getBRemove()){
            cout<<"remove! "<<foregrounds[i]<<endl;
            mixer.removeInputFrom(foregrounds[i]);

           delete (foregrounds[i]);
            foregrounds.erase(foregrounds.begin()+i);
        }else{
            foregrounds[i]->update();
        }
    }*/
for (int i=0;i<foregrounds.size();i++){
    foregrounds[i]->update();
        
        
    }
    
    for (int i=0;i<backgrounds.size();i++){
        backgrounds[i]->update();
        
        
    }

    
    
    
    
    for (int i=foregrounds.size()-1;i>=0;i--){
        if(foregrounds[i]->getBRemove()){
            cout<<"remove! "<<foregrounds[i]<<endl;
            mixer.removeInputFrom(foregrounds[i]);
          //  delete (foregrounds[i]);
            //removedforegrounds.push_back(foregrounds[i]);
            foregrounds.erase(foregrounds.begin()+i);
            
            if(foregrounds.size()<1){
                if(synths.size()>0)synths.erase(synths.begin());

            }
        }
    }

    
    
    if(removedforegrounds.size()>0){
        for (int i = 0; i < removedforegrounds.size(); ++i) {
          //  delete removedforegrounds[i]; // Calls ~object and deallocates *tmp[i]
        }
        //removedforegrounds.clear();
    }
    
    
    
    for (int i=backgrounds.size()-1;i>=0;i--){
        if(backgrounds[i]->getBRemove()){
            cout<<"remove Background! "<<backgrounds[i]<<endl;
            mixer.removeInputFrom(backgrounds[i]);
            //delete (backgrounds[i]);
            //removedforegrounds.push_back(foregrounds[i]);
            backgrounds.erase(backgrounds.begin()+i);
        }
    }


        
}




//--------------------------------------------------------------
void SoundManager::draw(){
    
}

//--------------------------------------------------------------

//void SoundManager::audioRequested (float * output, int bufferSize, int nChannels){
   // synth.fillBufferOfFloats(output, bufferSize, nChannels);
//}


//--------------------------------------------------------------
void SoundManager::audioOut(float * output, int bufferSize, int nChannels){
    
    
    float pan = 0.5f;
    float leftScale = 1 - pan;
    float rightScale = pan;
    
    
    reverb.setroomsize(verbRoomSize);
    reverb.setdamp(verbDamp);
    reverb.setwidth(verbWidth);
    reverb.setwet(wetness);
    reverb.setdry(1.0f - wetness);
    
    
    mixer.audioRequested(output, bufferSize, nChannels);
    
    
    
    for (int i = 0; i < bufferSize; i++){
        float left =output[i*nChannels]* volume * leftScale;
        float right =output[i*nChannels+1]* volume * leftScale;
        
       // if(bReverb) {
            reverb.processreplace(&left, &right, &output[i*nChannels], &output[i*nChannels + 1], 1, 1);
       // }else{
         //   output[i*nChannels + 0] = left;
          //  output[i*nChannels + 1] = right ;
            
        //}
    }
    
}




ForegroundSound* SoundManager::addForegroundSound(int _numSyllables,string _vowels,ofVec3f _p){
     if(foregrounds.size()<maxForegroundSound){

    ForegroundSound *fg = new ForegroundSound();
         fg->setNumSyllables(_numSyllables);
         fg->setVowels(_vowels);
         fg->setTimingSubDiv(10 + int(ofRandom(20)));
         fg->setPosition(_p);


    fg->setup();
    mixer.addInputFrom(fg);
    foregrounds.push_back(fg);
         if(synths.size()<1)addDrone();
    cout<<"Number of foreground sounds: "<<foregrounds.size()<<endl;
         return fg;
     }else{
         return nullptr;
     }
}



Background* SoundManager::addBackgroundSound(){
   // return;
    if(backgrounds.size()<8){
    Background *bg = new Background();
    bg->setup(backgrounds.size());
    mixer.addInputFrom(bg);
    backgrounds.push_back(bg);
        cout<<"Number of background sounds: "<<backgrounds.size()<<endl;
        return bg;

    }else return nullptr;
}



void SoundManager::deleteAllDeletedSounds(){
    if(removedforegrounds.size()>0){
        for (int i = 0; i < removedforegrounds.size(); ++i) {
            delete removedforegrounds[i]; // Calls ~object and deallocates *tmp[i]
        }
    removedforegrounds.clear();
    }

}


void SoundManager::explode(){
    for (int i=0;i<foregrounds.size();i++){
        foregrounds[i]->setBRemove();
    }
    
    for (int i=0;i<backgrounds.size();i++){
        backgrounds[i]->setBRemove();
    }


}


void SoundManager::addDrone(){
MySynth *s = new MySynth();
s->setup(55);        // ANT frequency here should be from scale
s->update();
mixer.addInputFrom(s);
synths.push_back(s);
cout<<synths.size()<<endl;

}


