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

    
    
    
    
    for (int i=foregrounds.size()-1;i>=0;i--){
        if(foregrounds[i]->getBRemove()){
            cout<<"remove! "<<foregrounds[i]<<endl;
            mixer.removeInputFrom(foregrounds[i]);
            //delete (foregrounds[i]);
            
            removedforegrounds.push_back(foregrounds[i]);
            foregrounds.erase(foregrounds.begin()+i);

            
        }
    }

    
    
    if(removedforegrounds.size()>0){
        for (int i = 0; i < removedforegrounds.size(); ++i) {
          //  delete removedforegrounds[i]; // Calls ~object and deallocates *tmp[i]
        }
        //removedforegrounds.clear();
    }


        
}

//--------------------------------------------------------------
void SoundManager::toggleGui(){
    bHide = !bHide;

   
}


//--------------------------------------------------------------
void SoundManager::draw(){
    
    if( !bHide ){
       // gui.draw();
    }
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
    ForegroundSound *fg = new ForegroundSound();
    fg->setup();
    //hello
    fg->setNumSyllables(_numSyllables);
    fg->setVowels(_vowels);
    fg->setPosition(_p);
    fg->setTimingSubDiv(10 + int(ofRandom(20)));
    mixer.addInputFrom(fg);
    foregrounds.push_back(fg);
    cout<<"Number of foreground sounds: "<<foregrounds.size()<<endl;
    return fg;
}

void SoundManager::deleteAllDeletedSounds(){
    if(removedforegrounds.size()>0){
        for (int i = 0; i < removedforegrounds.size(); ++i) {
            delete removedforegrounds[i]; // Calls ~object and deallocates *tmp[i]
        }
    removedforegrounds.clear();
    }

}

