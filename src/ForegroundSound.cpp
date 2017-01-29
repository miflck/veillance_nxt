//
//  ForegroundSound.cpp
//  customSynthClass
//
//  Created by Flückiger Michael on 28.11.16.
//
//

#include "ForegroundSound.hpp"
#include "SceneManager.hpp"
#include "SoundManager.hpp"



ForegroundSound::ForegroundSound(){
    cout<<"init FG sound "<<this<<endl;
}

ForegroundSound::~ForegroundSound(){
    cout<<"deconstruct FG sound "<<this<<endl;

}


void ForegroundSound::setSampleRate(int rate){
    sampleRate = rate;
}



void ForegroundSound::setup(){
    
    //viewportwidth=STM->viewportwidth;

    
    transposeRandom = int(ofRandom(4));
    switch (transposeRandom) {
        case 0:
            transpose = -12;
            break;
        case 1:
            transpose = 0;
            break;
        case 2:
            transpose = 12;
            break;
        case 3:
            transpose = 24;
            break;
        case 4:
            transpose = 36;
            break;
            
        default:
            break;
    }
    
    
    sylcont0=int(ofRandom(7)+1);
    sylcont1=int(ofRandom(7)+1);
    sylcont2=int(ofRandom(7)+1);
    sylcont3=int(ofRandom(7)+1);
    sylcont4=int(ofRandom(7)+1);
    sylcont5=int(ofRandom(7)+1);
    sylcont6=int(ofRandom(7)+1);
    
    fgnotes[0] =  scale[sylcont1];  // should this be 0
    fgnotes[1] =  scale[sylcont1];
    fgnotes[2] =  scale[sylcont2];
    fgnotes[3] =  scale[sylcont3];
    fgnotes[4] =  scale[sylcont4];
    fgnotes[5] =  scale[sylcont5];
    fgnotes[6] =  scale[sylcont6];

    
    
    
    
    //////////////////////////////////////////////////
    /////////Sound and control setup here/////////////
    //////////////////////////////////////////////////
    
     int NUM_STEPS;// = vowelsCount;//int(ofRandom(9));// This needs to be implemented this so that it is controlled by vowel count
    
    if(vowelsCount>0)     NUM_STEPS = vowelsCount;//int(ofRandom(9));// This needs to be implemented this so that it is controlled by vowel count
    else NUM_STEPS=1;
    
    
    SineWave            tone = SineWave();
    SineWave            modulator = SineWave();
    Generator           panner = MonoToStereoPanner();
    ControlGenerator    initialTrigger = synth.addParameter("trigger");;
    
    ControlGenerator    fmAmount =  synth.addParameter("fmAmt") ;       // Frequency modulation controls for timbre variation
    ControlGenerator    fmRatio =  synth.addParameter("fmRatio") ;      // Pass these in as random for each user
    
    ControlGenerator    panning =  synth.addParameter("panning") ;      // Dynamic controls for pan and volume
    ControlGenerator    volume =  synth.addParameter("volume") ;        // Controlled by LR position and Z position of word
    ControlGenerator    fgcut =  synth.addParameter("fgcut") ;          // fgcut is to tweak overall volume of instrument as may be too loud
    ControlGenerator    filterCutoff =  synth.addParameter("cutoff") ;
    
    ControlGenerator    trigger = ControlMetro().bpm(ControlRandom().min(70).max(200).trigger(initialTrigger));   // Main timing metronome. Sends a trigger message
    ControlGenerator    step = ControlStepper().end(NUM_STEPS).trigger(trigger);                                    // Stepper for seq.  Steps through note and beat vect
    ControlSwitcher     pitches = ControlSwitcher().inputIndex(step);                                               // Stored pitches populated by for loop bellow
    ControlSwitcher     volumes = ControlSwitcher().inputIndex(step);       // Stored volumes to control note on or off within rhythms
    ControlGenerator    noteFreq =  ControlMidiToFreq().input(pitches);     // Converts MIDI note numbers to frequency
    ControlGenerator    volume2 =  volumes;
    
    Generator           toneFilter = LPF12().input(tone * ADSR(0.001,0.1,0,0).trigger(trigger)).Q(0).cutoff(filterCutoff);
    
    modulator.freq(noteFreq* fmRatio);                                 // Combining of Carrier and Modulator oscilators for FM timbre variation
    tone.freq(noteFreq  * ( 1 +(modulator * fmAmount)));
    
    //////////////////////////////////////////////////
    /////////Sequencer content setup here/////////////e
    //////////////////////////////////////////////////
    
    for(int i = 0; i < NUM_STEPS; i++){                                 // Loop for populating step on/off and step pitches
        
        // This needs to come from word data
        
        ControlGenerator pitchForThisStep = synth.addParameter("step" + to_string(i) + "Pitch", (fgnotes[i] + transpose));
        pitches.addInput(pitchForThisStep);
        
        
        ControlGenerator volume3 = synth.addParameter("step" + to_string(i) + "Volume", fgbeats[i]);
        volumes.addInput(volume3);
    }

    
    panner = MonoToStereoPanner().pan(panning).input(((toneFilter * volume) * fgcut) * volume2.smoothed().length(1));
    synth.setOutputGen(panner);
    bRemove=false;
    maxZ=300;
   // position.set(0,0,0);
    
    
    
    maxX=viewportwidth+viewportwidth*2/3;
    minX=-viewportwidth*2/3;
    
    
    synth.setParameter("fmAmt", ofRandom(0.05));                         // Timbre variation for each instance ... Currently set randomly each time
    synth.setParameter("fmRatio", 0.5);
    float scaledCut=ofMap(SoundM->foregrounds.size(),0,20,0,1,true);
    synth.setParameter("fgcut", 0.2);

    
}

void ForegroundSound::update(){
    
    //scale zpos between background and screen2-zpos
    // that remap of position seems a bit overcomplicated, but that gives me the possibility to
    // set or move the both screen planes in virtual room later. these are not yet definitively set....
   // scaledZpos=ofMap(position.z,0,maxZ,0,1,true);
    
    
    scaledScalefact=ofMap(scalefact,0,fgmaxScalefact,0,1,true);
    
    

    
   // if (position.z >= maxZ)bRemove=true;
    
    scaledXpos=ofMap(position.x,minX,maxX,-1,1,true);
    
    float scaledCut=ofMap(SoundM->foregrounds.size(),0,50,500,200,true);
    
    float scaledVol=ofMap(distanceToMidScreen,0,viewportwidth,1,0,true);;
    
    //cout<<scaledXpos<<endl;
   // if (position.x >= maxX || position.x <=minX)bRemove=true;
    
    //synth.setParameter("volume", scaledZpos);
    synth.setParameter("volume", scaledVol);                                    //  Sound setup parameters
    synth.setParameter("panning", scaledXpos);
    synth.setParameter("cutoff", scaledCut);

    
  //  synth.setParameter("fmAmt", ofRandom(0.05));                         // Timbre variation for each instance ... Currently set randomly each time
//    synth.setParameter("fmRatio", 0.5);
  //  synth.setParameter("cutoff", 300);
    
  
    
    
   }

void ForegroundSound::setVowels(string _vowels){
    cout<<"v "<<_vowels<<endl;
  //  vowelsString=_vowels;
// vowelsCount=_vowels.length();
    parseVowels(_vowels);
}

void ForegroundSound::setNumSyllables(int _num){
    numSyllables=_num;

}

void ForegroundSound::setPosition(ofVec3f _position){
    position.set(_position);
   // cout<<"My Position "<<position;
}


void ForegroundSound::setScalefact(float _s){
    scalefact=_s;
}


void ForegroundSound::setTimingSubDiv(int _timeSubDiv) {
    timeSubDiv = _timeSubDiv;
}


void ForegroundSound::parseVowels(string _vowels){
    vowelsString=_vowels;
    vowelsCount=_vowels.length();
    cout<<"vC"<<vowelsCount<<endl;
    
    int  index;
    for (auto s:vowelsString){
        char c = s;
        switch (c) {
                
            case 'a':
                // do the a stuff
                fgnotes[index] =  scale[0]; // scale[0] is just a suggestion to keep up the order.if i understand your intention right.
                break;
            case 'e':
                fgnotes[index] =  scale[1];
                break;
            case 'i':
                fgnotes[index] =  scale[2];
                break;
            case 'o':
                fgnotes[index] =  scale[3];
                break;
            case 'u':
                fgnotes[index] =  scale[4];
                break;
                
            default:
                break;
        index++;
    }
    }
    
    
    
    
    
}

void ForegroundSound::setDistanceToMidScreen(float _d){
    distanceToMidScreen=_d;
}


void ForegroundSound::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}


bool ForegroundSound::getBRemove(){
    return bRemove;
}

void ForegroundSound::setBRemove(){
     bRemove=true;
}

void ForegroundSound::setMaxZ(int _maxZ){
    maxZ=_maxZ;
}