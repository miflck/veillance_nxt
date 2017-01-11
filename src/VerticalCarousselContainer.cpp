//
//  VerticalVerticalCarousselContainer.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#include "VerticalCarousselContainer.hpp"
#include "SceneManager.hpp"

VerticalCarousselContainer::VerticalCarousselContainer(){
}

void VerticalCarousselContainer::setup(){
    
}

void VerticalCarousselContainer::update(){
   /* ofVec2f p=ofVec2f(position.x+3,position.y+bbox.getHeight()-3);
    if(myLetter!=nullptr && myLetter->getBRemove()){
        myLetter=nullptr;
    }
    else{
    if(myLetter!=nullptr && !myLetter->getBRemove()){
         myLetter->setPosition(p);
         myLetter->setVelocity(velocity);
    }}
    */
}

void VerticalCarousselContainer::draw(){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(position);
    ofColor c=ofColor(255);
    ofNoFill();
    ofSetColor(c);
    //ofScale(0.6, 0.6);
    font->setLetterSpacing(1);

    font->drawString(mystring, -font->getStringBoundingBox(mystring, 0, 0).getWidth()/2,bbox.getHeight()-font->getStringBoundingBox("H", 0, 0).getHeight());
    ofPopMatrix();
    ofPopStyle();
    
    
    

    
}


void VerticalCarousselContainer::setBoundingBox(ofVec3f _position, ofVec2f _dimension){
    position.set(_position.x,_position.y);
    dimension.set(_dimension);
    bbox.setWidth(_dimension.x);
    bbox.setHeight(_dimension.y);
}


ofVec2f VerticalCarousselContainer::getPosition(){
    return position;
}

void VerticalCarousselContainer::setPosition(ofVec2f _pos){
    position.set(_pos);
}


void VerticalCarousselContainer::setDimension(ofVec2f _dimension){
    dimension.set(_dimension);
    bbox.setWidth(_dimension.x);
    bbox.setHeight(_dimension.y);
    cout<<dimension<<endl;
}

ofVec2f VerticalCarousselContainer::getDimension(){
    return dimension;
}

void VerticalCarousselContainer::setTarget(ofVec2f _target){
    target.set(_target);
}

ofVec2f VerticalCarousselContainer::getTarget(){
    return target;
}

void VerticalCarousselContainer::setString(string _s){
    mystring=ofToUpper(_s);
}



void VerticalCarousselContainer::setVelocity(ofVec2f _v){
    velocity.set(_v);
}


void VerticalCarousselContainer::setDebug(bool _debug){
    debug=_debug;
}


void VerticalCarousselContainer::explode(){
   // cout<<id<<" container exploding "<<endl;
    bIsExploding=true;
}

void VerticalCarousselContainer::setId(int _id){
    id=_id;
}

void VerticalCarousselContainer::setFont(ofTrueTypeFont *f){
    font=f;
    ofRectangle textBounds = font->getStringBoundingBox("H", 0, 0);
    
}