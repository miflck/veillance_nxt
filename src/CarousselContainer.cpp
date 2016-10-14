//
//  CarousselContainer.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#include "CarousselContainer.hpp"
CarousselContainer::CarousselContainer(){
}

void CarousselContainer::setup(){
    
}

void CarousselContainer::update(){
   // cout<<dimension<<endl;
}

void CarousselContainer::draw(){
    ofPushMatrix();
    ofTranslate(position);
    ofSetColor(255,100);
   ofDrawRectangle(bbox.x+2,bbox.y+2,bbox.getWidth()-2,bbox.getHeight()-2);
    ofSetColor(2000,200,255);
    //ofDrawBitmapString(ofToString(id), bbox.getCenter().x, bbox.getCenter().y);
 //   if(c!=' ')ofDrawBitmapString(c, bbox.getCenter().x, bbox.getCenter().y);
    if(c!=' ' && bDrawDebugRect)ofDrawRectangle(bbox.getCenter().x, bbox.getCenter().y,10,10);

    ofPopMatrix();
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

