//
//  CarousselContainer.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#include "CarousselContainer.hpp"
#include "StreamManager.hpp"

CarousselContainer::CarousselContainer(){
}

void CarousselContainer::setup(){
    
}

void CarousselContainer::update(){
    ofVec2f p=ofVec2f(position.x+bbox.getWidth()/2,position.y+10);
     if(myLetter!=nullptr){
         myLetter->setPosition(p);
         myLetter->setVelocity(velocity);
     }
}

void CarousselContainer::draw(){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(position);
    //ofColor c=ofColor(255,100);
    ofColor c=ofColor(0);

    if(myLetter!=nullptr){
      
        c=myLetter->getBackgroundColor();
    }
    ofSetColor(c,30);

    
    ofFill();
   // ofDrawRectangle(bbox.x+2,bbox.y+2,bbox.getWidth()-2,bbox.getHeight()-2);
    
    
    ofDrawRectangle(bbox.x+1,bbox.y,bbox.getWidth()-5,bbox.getHeight());
    
  

    ofPopMatrix();
    ofPopStyle();
}


void CarousselContainer::setBoundingBox(ofVec3f _position, ofVec2f _dimension){
   // bbox.setPosition(position.x, position.y);
    position.set(_position.x,_position.y);
    dimension.set(_dimension);
    bbox.setWidth(_dimension.x);
    bbox.setHeight(_dimension.y);
    //cout<<dimension<<endl;


}


ofVec2f CarousselContainer::getPosition(){
    return position;
}

void CarousselContainer::setPosition(ofVec2f _pos){
    position.set(_pos);
}


void CarousselContainer::setDimension(ofVec2f _dimension){
    dimension.set(_dimension);
    bbox.setWidth(_dimension.x);
    bbox.setHeight(_dimension.y);
    cout<<dimension<<endl;
}

ofVec2f CarousselContainer::getDimension(){
    return dimension;
}

void CarousselContainer::setTarget(ofVec2f _target){
    target.set(_target);
}

ofVec2f CarousselContainer::getTarget(){
    return target;
}

void CarousselContainer::setChar(char _c){
    c=_c;
}

char CarousselContainer::getChar(){
    return c;

}

void CarousselContainer::setLetterPointer(Letter *_l){
    myLetter= _l;
    bHasPointer=true;
 //   cout<<"data "<<ofToString(myLetter->getData())<<endl;
    
}
Letter* CarousselContainer::getLetterPointer(){
        return myLetter;
}


void CarousselContainer::setVelocity(ofVec2f _v){
    velocity.set(_v);
}


void CarousselContainer::setDebug(bool _debug){
    debug=_debug;
}



