//
//  MySynth.cpp
//  example_Basic
//
//  Created by Ant Dickinson on 16/11/2016.
//
//


#include "Background.h"





void Background::setSampleRate(int rate){
    sampleRate = rate;
}




void Background::setup(int _id){
    myId=_id;
     speed = int(ofRandom(5,9));
    stretchBg=int(ofRandom(0,4));

    volume	= 0.79f;

    int speedscale=2;
    
   /* switch (myId) {
        case 0:
            speed = 6;
            stretchBg=2;
            break;
        case 1:
            speed = 7;
            stretchBg=1;
            break;
            
        case 2:
            speed = 5;
            stretchBg=4;
            break;
        case 3:
            speed = 5;
            stretchBg=2;
            break;
            
        default:
            speed = int(ofRandom(4,7));
            stretchBg=int(ofRandom(1,4));
            break;
    }
    */
    
    switch (myId) {
        case 0:
            speed = 6*speedscale;
            stretchBg=2;
            break;
        case 1:
            speed = 7*speedscale;
            stretchBg=1;
            break;
            
        case 2:
            speed = 5*speedscale;
            stretchBg=4;
            break;
        case 3:
            speed = 5*speedscale;
            stretchBg=2;
            break;
            
        default:
            speed = int(ofRandom(4,7));
            stretchBg=int(ofRandom(1,4));
            break;
    }

    
    
    cout<<"ID "<<myId<<" Speed "<<speed<< " stretch "<<stretchBg<<endl;;

    
    for(int p = 0; p < 64; p ++){                   // Populates the background note arrays
        userbgbeat[p] = int(ofRandom(8));
    }
    
    userbgnotes[0] = 220;
    userbgnotes[1] = 220;
    userbgnotes[2] = 261;
    userbgnotes[3] = 329;
    userbgnotes[4] = 329;
    userbgnotes[5] = 392;
    userbgnotes[6] = 392;
    userbgnotes[7] = 440;
    userbgnotes[8] = 220;

    
    
    
    // user 1 background instrument
    
    SineWave            tone = SineWave();
    Generator           panner = MonoToStereoPanner();
    ControlGenerator    usernoteFreq1 =  synth.addParameter("userbg") ;
    ControlGenerator    panning =  synth.addParameter("panning") ;
    ControlGenerator    volume =  synth.addParameter("volume") ;
    ControlGenerator    userbgcut =  synth.addParameter("userbgcut") ;
    
    tone.freq(usernoteFreq1);
    
    panner = MonoToStereoPanner().pan(panning).input(( (tone * ADSR(0.001,0.05,0,00).trigger(triggeroo)) * volume) * userbgcut);
    
    synth.setOutputGen(panner);

    
    
}


void Background::update(){
    
    //------------------------------ User 1 background instrument sequencer
    
    //seqlength = wordcount;
    
    if(seqlength > 0)                               // fades the instrument volume if there is less than 1 note in sequence
    {
        synth.setParameter("userbgcut",bgvol);
        if ( bgvol < 0.1 ){
            bgvol += 0.001;
            if(bgvol>0.3)bgvol=0.3;
        }
    }
    else
    {
        bgvol = 0;
        synth.setParameter("userbgcut",bgvol);
    }
    
    
    if(wordcount == 0){                        // generates a new random set of notes when the pattern has emptied
        for(int p = 0; p < 64; p ++){
            userbgbeat[p] = int(ofRandom(8));
        }
    }
    
    synth.setParameter("panning", 0);               // panning and volume - currently static
    synth.setParameter("volume", 0.2);
    
    
    if(ofGetFrameNum() % speed == 0)                //  sequencer section timed from frame count
    {
        synth.setParameter("userbg", userbgnotes[userbgbeat[x]]*stretchBg);
        triggeroo.trigger();
        x ++;                                      //scrolls through the beat number/position within the note array thenresets
        if(x >= seqlength){ //-> i dont know whats up here, but x cant get bigger than 64 because of userbgbeat[x]
       // if(x >= 64){ //-> i dont know whats up here, but x cant get bigger than 64 because of userbgbeat[x]
            x = 0;
        }
    }
    
    
}


void Background::setNumWords(int _num){
    wordcount=_num;
    
   // if(wordcount>100)wordcount=90;
    
    seqlength=wordcount;

    
  //if(myId==0)  cout<<wordcount<<" "<<seqlength<<endl;


}

int Background::getNumWords(){
    return wordcount;
}


void Background::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}


bool Background::getBRemove(){
    return bRemove;
}

void Background::setBRemove(){
    bRemove=true;
}



