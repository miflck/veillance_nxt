//
//  SoundManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 15.11.16.
//
//

#include "SoundManager.hpp"

ControlTrigger triggeroo;
ControlTrigger triggeroo2;
ControlTrigger triggeroo3;
ControlTrigger triggeroo4;
ControlTrigger user1fgtrig;
ControlTrigger user2fgtrig;
ControlTrigger user3fgtrig;
ControlTrigger user4fgtrig;

int user1bgnotes[] = {220, 220 ,261,329,329,392,392,440, 220};
int scale[] = {220, 880 ,261,329,329,392,392,440, 220};
int user1fgnotes[] = {0,0,0,0,0,0,0};
int user1fgbeats[] = {0,1,1,1,1,1,1,1,1,1,1};
int user2fgnotes[] = {0,0,0,0,0,0,0};
int user2fgbeats[] = {0,1,1,1,1,1,1,1,1,1,1};
int user3fgnotes[] = {0,0,0,0,0,0,0};
int user3fgbeats[] = {0,1,1,1,1,1,1,1,1,1,1};
int user4fgnotes[] = {0,0,0,0,0,0,0};
int user4fgbeats[] = {0,1,1,1,1,1,1,1,1,1,1};

// int user1bgnotes[] = {220, 247 ,261,294,329,349,392,440};
int user1bgbeat[64] = {};
int user2bgbeat[64] = {};
int user3bgbeat[64] = {};
int user4bgbeat[64] = {};
int x = 0;
int x2 = 0;
int x3 = 0;
int x4 = 0;
float bgvol;
float bgvol2;
float bgvol3;
float bgvol4;
int seqlength = 0;
int seqlength2 = 0;
int seqlength3 = 0;
int seqlength4 = 0;
int speed = 6;
int speed2 = 7;
int speed3 = 8;
int speed4 = 5;
int z = 0;
int z2 = 0;
int z3 = 0;
int z4 = 0;


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
    cout<<"init SceneManager"<<endl;
    
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    
    
    /* -----------------------------ALL OF THE GUI STUFF------------------------------------------------*/
    
    
    for(int p = 0; p < 64; p ++){                   // Populates the background note arrays
        user1bgbeat[p] = int(ofRandom(8));
    }
    
    for(int p = 0; p < 64; p ++){
        user2bgbeat[p] = int(ofRandom(8));
    }
    
    for(int p = 0; p < 64; p ++){
        user3bgbeat[p] = int(ofRandom(8));
    }
    
    for(int p = 0; p < 64; p ++){
        user4bgbeat[p] = int(ofRandom(8));
    }
    
    
    ////////// ALL OF THIS BIT HERE  VVVVVVVVVV ////////////
    //// iNSTEAD OF THE gui controlling the sound, teh data will instead so
    ////  these would need to be re-mapped
    //// for example instead of "user1wordcount" being controlled from teh GUI slider it would be mapped
    //// from the incoming data for user 1s background word count
    
    
    gui.setup();
    
    gui.add( user1wordcount.set( "user1 word count",0,0,100));
   // gui.add(user1wordcount.setup("user1 word count",0,0,100));
    gui.add(user1vowelcount.set("user1 syllable count",0,0,6));
    gui.add(user1sylcont1.set("user1 vowel 1",int(ofRandom(6)),0,6));
    gui.add(user1sylcont2.setup("user1 vowel 2",int(ofRandom(6)),0,6));
    gui.add(user1sylcont3.setup("user1 vowel 3",int(ofRandom(6)),0,6));
    gui.add(user1sylcont4.setup("user1 vowel 4",int(ofRandom(6)),0,6));
    gui.add(user1sylcont5.setup("user1 vowel 5",int(ofRandom(6)),0,6));
    gui.add(user1sylcont6.setup("user1 vowel 6",int(ofRandom(6)),0,6));
    gui.add(user1pan.setup("user1 pan",0,-1,1));
    gui.add(user1Zpos.setup("user1 z position",0.2,0,1));
    
    gui.add(user2wordcount.setup("user2 word count",0,0,100));
    gui.add(user2vowelcount.setup("user2 syllable count",0,0,16));
    gui.add(user2sylcont1.setup("user2 vowel 1",int(ofRandom(6)),0,14));
    gui.add(user2sylcont2.setup("user2 vowel 2",int(ofRandom(6)),0,14));
    gui.add(user2sylcont3.setup("user2 vowel 3",int(ofRandom(6)),0,14));
    gui.add(user2sylcont4.setup("user2 vowel 4",int(ofRandom(6)),0,14));
    gui.add(user2sylcont5.setup("user2 vowel 5",int(ofRandom(6)),0,14));
    gui.add(user2sylcont6.setup("user2 vowel 6",int(ofRandom(6)),0,14));
    gui.add(user2pan.setup("user2 pan",0,-1,1));
    gui.add(user2Zpos.setup("user2 z position",0.2,0,1));
    
    gui.add(user3wordcount.setup("user3 word count",0,0,100));
    gui.add(user3vowelcount.setup("user3 syllable count",0,0,16));
    gui.add(user3sylcont1.setup("user3 vowel 1",int(ofRandom(6)),0,14));
    gui.add(user3sylcont2.setup("user3 vowel 2",int(ofRandom(6)),0,14));
    gui.add(user3sylcont3.setup("user3 vowel 3",int(ofRandom(6)),0,14));
    gui.add(user3sylcont4.setup("user3 vowel 4",int(ofRandom(6)),0,14));
    gui.add(user3sylcont5.setup("user3 vowel 5",int(ofRandom(6)),0,14));
    gui.add(user3sylcont6.setup("user3 vowel 6",int(ofRandom(6)),0,14));
    gui.add(user3pan.setup("user3 pan",0,-1,1));
    gui.add(user3Zpos.setup("user3 z position",0.2,0,1));
    
    gui.add(user4wordcount.setup("user4 word count",0,0,100));
    gui.add(user4vowelcount.setup("user4 syllable count",0,0,16));
    gui.add(user4sylcont1.setup("user4 vowel 1",int(ofRandom(6)),0,14));
    gui.add(user4sylcont2.setup("user4 vowel 2",int(ofRandom(6)),0,14));
    gui.add(user4sylcont3.setup("user4 vowel 3",int(ofRandom(6)),0,14));
    gui.add(user4sylcont4.setup("user4 vowel 4",int(ofRandom(6)),0,14));
    gui.add(user4sylcont5.setup("user4 vowel 5",int(ofRandom(6)),0,14));
    gui.add(user4sylcont6.setup("user4 vowel 6",int(ofRandom(6)),0,14));
    gui.add(user4pan.setup("user4 pan",0,-1,1));
    gui.add(user4Zpos.setup("user4 z position",0.2,0,1));
    
    bHide = true;
    
    
    
    /* -----------------------------SET UP AND PATCHING OF INSTRUMENTS---------------------------------------*/
    
    Generator           reveroo = Reverb();
    
    // user 1 background instrument
    
    SineWave            tone = SineWave();
    Generator           panner = MonoToStereoPanner();
    ControlGenerator    user1noteFreq1 =  synth.addParameter("user1bg") ;
    ControlGenerator    panning =  synth.addParameter("panning") ;
    ControlGenerator    volume =  synth.addParameter("volume") ;
    ControlGenerator    user1bgcut =  synth.addParameter("user1bgcut") ;
    
    tone.freq(user1noteFreq1);
    
    panner = MonoToStereoPanner().pan(panning).input(( (tone * ADSR(0.001,0.05,0,00).trigger(triggeroo)) * volume) * user1bgcut);
    
    // user 2 background instrument
    
    SineWave            tone2 = SineWave();
    Generator           panner2 = MonoToStereoPanner();
    ControlGenerator    user2noteFreq1 =  synth.addParameter("user2bg") ;
    ControlGenerator    panning2 =  synth.addParameter("panning2") ;
    ControlGenerator    volume2 =  synth.addParameter("volume2") ;
    ControlGenerator    user2bgcut =  synth.addParameter("user2bgcut") ;
    
    tone2.freq(user2noteFreq1);
    
    panner2 = MonoToStereoPanner().pan(panning2).input(( (tone2 * ADSR(0.001,0.05,0,00).trigger(triggeroo2)) * volume2) * user2bgcut);
    
    // user 3 background instrument
    
    SineWave            tone3 = SineWave();
    Generator           panner3 = MonoToStereoPanner();
    ControlGenerator    user3noteFreq1 =  synth.addParameter("user3bg") ;
    ControlGenerator    panning3 =  synth.addParameter("panning3") ;
    ControlGenerator    volume3 =  synth.addParameter("volume3") ;
    ControlGenerator    user3bgcut =  synth.addParameter("user3bgcut") ;
    
    tone3.freq(user3noteFreq1);
    
    panner3 = MonoToStereoPanner().pan(panning3).input(( (tone3 * ADSR(0.001,0.05,0,00).trigger(triggeroo3)) * volume3) * user3bgcut);
    
    // user 4 background instrument
    
    SineWave            tone4 = SineWave();
    Generator           panner4 = MonoToStereoPanner();
    ControlGenerator    user4noteFreq1 =  synth.addParameter("user4bg") ;
    ControlGenerator    panning4 =  synth.addParameter("panning4") ;
    ControlGenerator    volume4 =  synth.addParameter("volume4") ;
    ControlGenerator    user4bgcut =  synth.addParameter("user4bgcut") ;
    
    tone4.freq(user4noteFreq1);
    
    panner4 = MonoToStereoPanner().pan(panning4).input(( (tone4 * ADSR(0.001,0.05,0,00).trigger(triggeroo4)) * volume4) * user4bgcut);
    
    
    // user 1 forground instrument
    
    SineWave            u1tone2 = SineWave();
    Generator           u1panner2 = MonoToStereoPanner();
    ControlGenerator    user1noteFreq2 =  synth.addParameter("user1fg") ;
    ControlGenerator    u1panning2 =  synth.addParameter("u1panning2") ;
    ControlGenerator    u1volume2 =  synth.addParameter("u1volume2") ;
    ControlGenerator    user1fgcut2 =  synth.addParameter("user1fgcut2") ;
    
    u1tone2.freq(user1noteFreq2);
    
    u1panner2 = MonoToStereoPanner().pan(u1panning2).input(( (u1tone2 * ADSR(0.001,0.05,0,00).trigger(user1fgtrig)) * u1volume2) * user1fgcut2);
    
    // user 2 forground instrument
    
    SineWave            u2tone2 = SineWave();
    Generator           u2panner2 = MonoToStereoPanner();
    ControlGenerator    user2noteFreq2 =  synth.addParameter("user2fg") ;
    ControlGenerator    u2panning2 =  synth.addParameter("u2panning2") ;
    ControlGenerator    u2volume2 =  synth.addParameter("u2volume2") ;
    ControlGenerator    user2fgcut2 =  synth.addParameter("user2fgcut2") ;
    
    u2tone2.freq(user2noteFreq2);
    
    u2panner2 = MonoToStereoPanner().pan(u2panning2).input(( (u2tone2 * ADSR(0.001,0.05,0,00).trigger(user2fgtrig)) * u2volume2) * user2fgcut2);
    
    // user 3 forground instrument
    
    SineWave            u3tone2 = SineWave();
    Generator           u3panner2 = MonoToStereoPanner();
    ControlGenerator    user3noteFreq2 =  synth.addParameter("user3fg") ;
    ControlGenerator    u3panning2 =  synth.addParameter("u3panning2") ;
    ControlGenerator    u3volume2 =  synth.addParameter("u3volume2") ;
    ControlGenerator    user3fgcut2 =  synth.addParameter("user3fgcut2") ;
    
    u3tone2.freq(user3noteFreq2);
    
    u3panner2 = MonoToStereoPanner().pan(u3panning2).input(( (u3tone2 * ADSR(0.001,0.05,0,00).trigger(user3fgtrig)) * u3volume2) * user3fgcut2);
    
    // user 4 forground instrument
    
    SineWave            u4tone2 = SineWave();
    Generator           u4panner2 = MonoToStereoPanner();
    ControlGenerator    user4noteFreq2 =  synth.addParameter("user4fg") ;
    ControlGenerator    u4panning2 =  synth.addParameter("u4panning2") ;
    ControlGenerator    u4volume2 =  synth.addParameter("u4volume2") ;
    ControlGenerator    user4fgcut2 =  synth.addParameter("user4fgcut2") ;
    
    u4tone2.freq(user4noteFreq2);
    
    u4panner2 = MonoToStereoPanner().pan(u4panning2).input(( (u4tone2 * ADSR(0.001,0.05,0,00).trigger(user4fgtrig)) * u4volume2) * user4fgcut2);
    
    
    reveroo = Reverb().input(panner + panner2 + panner3 + panner4 + u1panner2 + u2panner2 + u3panner2 + u4panner2).decayTime(10).roomSize(20).wetLevel(0.5);
    
    // Synth's final output generator
    synth.setOutputGen(reveroo + panner + panner2 + panner3 + panner4  + u1panner2 + u2panner2 + u3panner2 + u4panner2);
    
    
}

//--------------------------------------------------------------
void SoundManager::update(){
    
    
    
    //------------------------------ User 1 background instrument sequencer
    
    seqlength = user1wordcount;
    
    if(seqlength > 0)                               // fades the instrument volume if there is less than 1 note in sequence
    {
        synth.setParameter("user1bgcut",bgvol);
        if ( bgvol < 0.1){
            bgvol += 0.001;
        }
    }
    else
    {
        bgvol = 0;
        synth.setParameter("user1bgcut",bgvol);
    }
    
    
    if(user1wordcount == 0){                        // generates a new random set of notes when the pattern has emptied
        for(int p = 0; p < 64; p ++){
            user1bgbeat[p] = int(ofRandom(8));
        }
    }
    
    synth.setParameter("panning", 0);               // panning and volume - currently static
    synth.setParameter("volume", 0.2);
    
    
    if(ofGetFrameNum() % speed == 0)                //  sequencer section timed from frame count
    {
        synth.setParameter("user1bg", user1bgnotes[user1bgbeat[x]] * 2);
        triggeroo.trigger();
        x ++;                                      //scrolls through the beat number/position within the note array thenresets
        if(x >= seqlength){
            x = 0;
        }
    }
    
    
    
    
    // ------------------------------ User 2 background instrument sequencer
    
    seqlength2 = user2wordcount;
    
    if(seqlength2 > 0)                               // kills the instrument volume if there is less than 1 note in sequence
    {
        synth.setParameter("user2bgcut",bgvol2);
        
        if ( bgvol2 < 0.1){
            bgvol2 += 0.001;
        }
    }
    else
    {
        bgvol2 = 0;
        synth.setParameter("user2bgcut",bgvol2);
    }
    
    
    
    if(user2wordcount == 0){
        for(int p = 0; p < 64; p ++){
            user2bgbeat[p] = int(ofRandom(8));
        }
    }
    
    synth.setParameter("panning2", 0);         // controller input for panning and volume - need to loose this
    synth.setParameter("volume2", 0.3);
    
    
    if(ofGetFrameNum() % speed2 == 0)                //  sequencer section timed from frame count
    {
        synth.setParameter("user2bg", user1bgnotes[user2bgbeat[x2]]);
        triggeroo2.trigger();
        
        x2 ++;                                      //scrolls through the beat number/position within the note array thenresets
        if(x2 >= seqlength2){
            x2 = 0;
        }
    }
    
    // ------------------------------ User 3 background instrument
    
    seqlength3 = user3wordcount;
    
    if(seqlength3 > 0)                               // kills the instrument volume if there is less than 1 note in sequence
    {
        synth.setParameter("user3bgcut",bgvol3);
        
        if ( bgvol3 < 0.1){
            bgvol3 += 0.001;
        }
        
    }
    else
    {
        bgvol3 = 0;
        synth.setParameter("user3bgcut",bgvol3);
    }
    
    if(user3wordcount == 0){
        
        for(int p = 0; p < 64; p ++){
            user3bgbeat[p] = int(ofRandom(8));
        }
    }
    
    
    synth.setParameter("panning3", 0);         // controller input for panning and volume - need to loose this
    synth.setParameter("volume3", 0.1);
    
    
    if(ofGetFrameNum() % speed3 == 0)                //  sequencer section timed from frame count
    {
        synth.setParameter("user3bg", user1bgnotes[user3bgbeat[x3]] * 4);
        triggeroo3.trigger();
        
        x3 ++;                                      //scrolls through the beat number/position within the note array thenresets
        if(x3 >= seqlength3){
            x3 = 0;
        }
    }
    
    // ------------------------------ User 4 background instrument
    
    seqlength4 = user4wordcount;
    
    if(seqlength4 > 0)                               // kills the instrument volume if there is less than 1 note in sequence
    {
        synth.setParameter("user4bgcut",bgvol4);
        
        if ( bgvol4 < 0.1){
            bgvol4 += 0.001;
        }
        
    }
    else
    {
        bgvol4 = 0;
        synth.setParameter("user4bgcut",bgvol4);
    }
    
    if(user4wordcount == 0){
        
        for(int p = 0; p < 64; p ++){
            user4bgbeat[p] = int(ofRandom(8));
        }
    }
    synth.setParameter("panning4", 0);         // controller input for panning and volume - need to loose this
    synth.setParameter("volume4", 0.4);
    
    
    if(ofGetFrameNum() % speed4 == 0)                //  sequencer section timed from frame count
    {
        synth.setParameter("user4bg", user1bgnotes[user4bgbeat[x4]] * 2);
        triggeroo4.trigger();
        
        x4 ++;                                      //scrolls through the beat number/position within the note array thenresets
        if(x4 >= seqlength4){
            x4 = 0;
        }
    }
    
    
    
    /* ---------------------------------------foreground moving text sequencer user 1---------------------------------  */
    
    synth.setParameter("u1volume2", user1Zpos);
    synth.setParameter("user1fgcut2", 0.4);
    synth.setParameter("u1panning2", user1pan);
    
    user1fgnotes[0] = 0;
    user1fgnotes[1] =  scale[user1sylcont1];
    user1fgnotes[2] =  scale[user1sylcont2];
    user1fgnotes[3] =  scale[user1sylcont3];
    user1fgnotes[4] =  scale[user1sylcont4];
    user1fgnotes[5] =  scale[user1sylcont5];
    user1fgnotes[6] =  scale[user1sylcont6];
    
    
    
    
    if ( ofGetFrameNum() % 14 == 0)
    {
        z ++;
        
        if(z > user1vowelcount)
        {
            z = 0;
        }
        
        if (user1fgbeats[z] == 1){
            synth.setParameter("user1fg", user1fgnotes[z]);
            user1fgtrig.trigger();
        }
        
    }
    
    
    if ( user1Zpos == 1)            ///////////////////////////// if the volume reaches maximum i.e. the word is close to the                           screen . The sound will cut out and in turn this will be used to trigger the rear screen synth.
    {
        user1Zpos = 0;
        
    }
    
    /* ---------------------------------------foreground moving text sequencer user 2---------------------------------  */
    
    synth.setParameter("u2volume2", user2Zpos);
    synth.setParameter("user2fgcut2", 0.4);
    synth.setParameter("u2panning2", user2pan);
    
    user2fgnotes[0] = 0;
    user2fgnotes[1] =  scale[user2sylcont1];
    user2fgnotes[2] =  scale[user2sylcont2];
    user2fgnotes[3] =  scale[user2sylcont3];
    user2fgnotes[4] =  scale[user2sylcont4];
    user2fgnotes[5] =  scale[user2sylcont5];
    user2fgnotes[6] =  scale[user2sylcont6];
    
    
    
    
    if ( ofGetFrameNum() % 14 == 0)
    {
        z2 ++;
        
        if(z2 > user2vowelcount)
        {
            z2 = 0;
        }
        
        if (user2fgbeats[z2] == 1){
            synth.setParameter("user2fg", user2fgnotes[z2]);
            user2fgtrig.trigger();
        }
        
    }
    
    
    if ( user2Zpos == 1)            ///////////////////////////// if the volume reaches maximum i.e. the word is close to the                           screen . The sound will cut out and in turn this will be used to trigger the rear screen synth.
    {
        user2Zpos = 0;
        
    }
    
    /* ---------------------------------------foreground moving text sequencer user 3---------------------------------  */
    
    synth.setParameter("u3volume2", user3Zpos);
    synth.setParameter("user3fgcut2", 0.4);
    synth.setParameter("u3panning2", user3pan);
    
    user3fgnotes[0] = 0;
    user3fgnotes[1] =  scale[user3sylcont1];
    user3fgnotes[2] =  scale[user3sylcont2];
    user3fgnotes[3] =  scale[user3sylcont3];
    user3fgnotes[4] =  scale[user3sylcont4];
    user3fgnotes[5] =  scale[user3sylcont5];
    user3fgnotes[6] =  scale[user3sylcont6];
    
    
    
    
    if ( ofGetFrameNum() % 14 == 0)
    {
        z3 ++;
        
        if(z3 > user3vowelcount)
        {
            z3 = 0;
        }
        
        if (user3fgbeats[z3] == 1){
            synth.setParameter("user3fg", user3fgnotes[z3]);
            user3fgtrig.trigger();
        }
        
    }
    
    
    if ( user3Zpos == 1)            ///////////////////////////// if the volume reaches maximum i.e. the word is close to the                           screen . The sound will cut out and in turn this will be used to trigger the rear screen synth.
    {
        user3Zpos = 0;
        
    }
    
    /* ---------------------------------------foreground moving text sequencer user 4---------------------------------  */
    
    synth.setParameter("u4volume2", user4Zpos);
    synth.setParameter("user4fgcut2", 0.4);
    synth.setParameter("u4panning2", user4pan);
    
    user4fgnotes[0] = 0;
    user4fgnotes[1] =  scale[user4sylcont1];
    user4fgnotes[2] =  scale[user4sylcont2];
    user4fgnotes[3] =  scale[user4sylcont3];
    user4fgnotes[4] =  scale[user4sylcont4];
    user4fgnotes[5] =  scale[user4sylcont5];
    user4fgnotes[6] =  scale[user4sylcont6];
    
    
    
    
    if ( ofGetFrameNum() % 14 == 0)
    {
        z4 ++;
        
        if(z4 > user4vowelcount)
        {
            z4 = 0;
        }
        
        if (user4fgbeats[z4] == 1){
            synth.setParameter("user4fg", user4fgnotes[z4]);
            user4fgtrig.trigger();
        }
        
    }
    
    
    if ( user4Zpos == 1)            ///////////////////////////// if the volume reaches maximum i.e. the word is close to the                           screen . The sound will cut out and in turn this will be used to trigger the rear screen synth.
    {
        user4Zpos = 0;
        
    }
    
    
    
    
}

//--------------------------------------------------------------
void SoundManager::toggleGui(){
    bHide = !bHide;

   
}


//--------------------------------------------------------------
void SoundManager::draw(){
    
    if( !bHide ){
        gui.draw();
    }
}

//--------------------------------------------------------------

void SoundManager::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}
