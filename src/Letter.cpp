//
//  Letter.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#include "Letter.hpp"
#include "Word.h"
#include "Fragment.hpp"

#include "StreamManager.hpp"


Letter::Letter(){
    data=NULL;
    
}

void Letter::setup(){
    position.set(ofRandom(100,500),ofRandom(100,500));
    static LetterEvent newEvent;
    newEvent.message = "New Letter";
    newEvent.letter     = this;
    ofNotifyEvent(LetterEvent::events, newEvent);
    ofRectangle textBounds = font->getStringBoundingBox("H", 0, 0);
    bIsOnScreen=false;
    
}

void Letter::update(){
    if(bIsOnScreen){//check if is on screen
        angle+=0.5;
        if(angle>360)angle=360;
    }
}

void Letter::draw(){

    
    if(bIsOnScreen){
        
              
        
        
        
        //check if is on screen
       /* if(bIsDrawn){ // only draw if is not moving word;
            ofPushMatrix();
            ofTranslate(position);
            ofColor c=myWordPointer->getColor();
            ofSetColor(c);
            font->drawString(myString, 0,font->getStringBoundingBox("H", 0, 0).getHeight());
            ofPopMatrix();
        }*/
        
      
        
    }
}


void Letter::setData(char _data){
    data=_data;
    myString=ofToUpper(ofToString(_data));
    letterMesh = font->getStringMesh(myString, 0, 0);
}

void Letter::setWordId(int _id){
    wordId=_id;
}

int Letter::getWordId(){
    return wordId;
}


char Letter::getData(){
    return data;
}


string Letter::getString(){
    return myString;
}


void Letter::setFont(ofTrueTypeFont *f){
    font=f;
    ofRectangle textBounds = font->getStringBoundingBox("H", 0, 0);
    
}



void Letter::setIsDrawn(bool _b){
    bIsDrawn=_b;
}



void Letter::setDebug(bool _debug){
    debug=_debug;
}


void Letter::setWordPointer(Word *_w){
    myWordPointer=_w;
}


void Letter::setFragmentPointer(Fragment *_f){
    myFragmentPointer=_f;
}



void Letter::setPosition(ofVec2f _p){
    position.set(_p);
    node.setGlobalPosition(position);
    
}

ofVec2f Letter::getPosition(){
    return position;
}


void Letter::setIsOnScreen(bool _s){
    bIsOnScreen=_s;
    angle=0;
    
}

bool Letter::getIsOnScreen(){
    return bIsOnScreen;
}




void Letter::setBRemove(bool _b){
    bRemove=_b;
    if(bRemove){
      myWordPointer->unregisterLetter(this);
        myFragmentPointer->unregisterLetter(this);
    }
}

bool Letter::getBRemove(){
    return bRemove;
}

void Letter::setVelocity(ofVec2f _v){
    velocity.set(_v);
}

ofVec2f Letter::getVelocity(){
    return velocity;
}



ofVboMesh Letter::getUpdatedVboMesh(){
    // node.roll(ofDegToRad(angle));
    vbom.clear();
    if(bIsOnScreen){//check if is on screen
        letterMesh = font->getStringMesh(myString, 0, 0);
        vector<ofVec3f>& verts = letterMesh.getVertices();
        for(int j=0; j <  verts.size() ; j++){
            letterMesh.setVertex(j,verts[j]*node.getGlobalTransformMatrix());
            letterMesh.addColor(myWordPointer->getColor());
          //  letterMesh.addColor(255);

        }
        vbom.append(letterMesh);
    }
    return vbom;
    
}

ofColor Letter::getColor(){
    return myWordPointer->getColor();
}
ofColor Letter::getBackgroundColor(){
    return myWordPointer->getBackgroundColor();
}

