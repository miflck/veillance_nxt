//
//  Letter.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#include "Letter.hpp"
#include "Word.h"
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
    
}

void Letter::update(){
    //  move();
    //node.pan(ofRandom(5));
    //  makeOriginalVboMesh();
}

void Letter::draw(){
    
    if(bIsOnScreen){//check if is on screen
        if(bIsDrawn){ // only draw if is not moving word;
            ofPushMatrix();
            ofTranslate(position);
            ofColor c=myWordPointer->getColor();
            ofSetColor(c);
            font->drawString(myString, 0,font->getStringBoundingBox("H", 0, 0).getHeight());
            ofPopMatrix();
        }
    }
    /*fboText.begin();
     ofClear(255, 255, 255, 0);
     font->drawString(ofToString(data), 0, font->getStringBoundingBox("H", 0, 0).getHeight());
     fboText.end();
     fboText.draw(0, 0);*/
}


void Letter::setData(char _data){
    data=_data;
    myString=ofToUpper(ofToString(_data));
    //  ofRectangle textBounds = font->getStringBoundingBox("H", 0, 0);
    //  fboText.allocate(textBounds.getWidth()+2, textBounds.getHeight()+2);
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


void Letter::setPosition(ofVec2f _p){
    position.set(_p);
}

ofVec2f Letter::getPosition(){
    return position;
}


void Letter::setIsOnScreen(bool _s){
    bIsOnScreen=_s;
    
}

bool Letter::getIsOnScreen(){
    return bIsOnScreen;
}



void Letter::makeOriginalVboMesh(){
    
    ofMesh tmesh;
    tmesh = font->getStringMesh(ofToString(data), 0, 0);
    
    vector<ofVec3f>& verts = tmesh.getVertices();
    
    for(int j=0; j <  verts.size() ; j++){
        tmesh.setVertex(j,verts[j]);//*node.getGlobalTransformMatrix());
    }
    originalVboMesh.append(tmesh);
}

ofVboMesh Letter::getOriginalVboMesh(){
    return originalVboMesh;
}