//
//  MySynth.cpp
//  example_Basic
//
//  Created by Ant Dickinson on 16/11/2016.
//
//


#include "MySynth.h"


MySynth::MySynth(){
    cout<<"init MySynth "<<this<<endl;
}

MySynth::~MySynth(){
    cout<<"deconstruct MySynth "<<this<<endl;
    
}


void MySynth::setSampleRate(int rate){
    sampleRate = rate;
}




void MySynth::setup(float _p){
    volume	= 0.5f;
    float basePitch = _p;
    
     SawtoothWave saw = SawtoothWave();
    
    saw.freq(basePitch);
    SineWave vibratoOsc = SineWave();
    vibratoOsc.freq(0.1);

        ControlGenerator    volume =  synth.addParameter("volume") ;
    

    SineWave tone = SineWave();
    LPF24 filter = LPF24().cutoff(200 * (vibratoOsc + 1)).input(saw).Q(0);
    
   
    tone.freq(basePitch);
  
    
    
    // let's also create a tremelo effect
    SineWave tremeloSine = SineWave().freq(0.1);
    
    // set the synth's final output generator
    synth.setOutputGen( (filter  * (tremeloSine * 0.1) * volume ));
    
    
}

void MySynth::update(){
        synth.setParameter("volume", 0.7);
}


void MySynth::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}




