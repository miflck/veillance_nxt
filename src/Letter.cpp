//
//  Letter.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#include "Letter.hpp"
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
    ofSetColor(255,0,0);
    font->drawString(ofToString(data), 0,font->getStringBoundingBox("H", 0, 0).getHeight());

    /*fboText.begin();
    ofClear(255, 255, 255, 0);
    font->drawString(ofToString(data), 0, font->getStringBoundingBox("H", 0, 0).getHeight());
    fboText.end();
    fboText.draw(0, 0);*/
}


void Letter::setData(char _data){
    data=_data;
  //  ofRectangle textBounds = font->getStringBoundingBox("H", 0, 0);
  //  fboText.allocate(textBounds.getWidth()+2, textBounds.getHeight()+2);
}


char Letter::getData(){
    return data;
}

void Letter::setFont(ofTrueTypeFont *f){
    font=f;
     ofRectangle textBounds = font->getStringBoundingBox("H", 0, 0);
    
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