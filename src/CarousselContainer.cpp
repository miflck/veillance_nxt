//
//  CarousselContainer.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#include "CarousselContainer.hpp"
#include "SceneManager.hpp"

CarousselContainer::CarousselContainer(){
}

void CarousselContainer::setup(){
    
}

void CarousselContainer::update(){
    ofVec2f p=ofVec2f(position.x+3,position.y+bbox.getHeight()-3);
    if(myLetter!=nullptr && myLetter->getBRemove()){}
    else{
    if(myLetter!=nullptr && !myLetter->getBRemove()){
         myLetter->setPosition(p);
         myLetter->setVelocity(velocity);
    }}
    
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
    ofSetColor(c,120);

    //debug stack manager
    ofSetColor(255,0,0);

    
    ofFill();
   // ofDrawRectangle(bbox.x+2,bbox.y+2,bbox.getWidth()-2,bbox.getHeight()-2);
    
    ofDrawRectangle(bbox.x-1,bbox.y-1,bbox.getWidth()-2,bbox.getHeight()-2);
  
  

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
    if(myLetter!=nullptr){
        return myLetter->getData();
    }else
    return '*';

}

void CarousselContainer::setLetterPointer(Letter *_l){
    myLetter= _l;
    bHasPointer=true;
 //   cout<<"data "<<ofToString(myLetter->getData())<<endl;
    
}


void CarousselContainer::registerLetter(Letter *_l){
    myLetter= _l;
    bHasPointer=true;
    //   cout<<"data "<<ofToString(myLetter->getData())<<endl;
    
}

void CarousselContainer::unregisterLetter(){
   cout<<id<<" unregister from container "<<myLetter<<endl;
        myLetter=nullptr;
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

ofColor CarousselContainer::getBackgroundColor(){
    ofColor c;
    if(myLetter!=nullptr){
        
        c=myLetter->getBackgroundColor();
    }else{
        c=ofColor(0);
    }
    return c;
}

void CarousselContainer::explode(){
    bIsExploding=true;
}

void CarousselContainer::setId(int _id){
    id=_id;
}
void CarousselContainer::setStackId(int _id){
    stackId=_id;
}
