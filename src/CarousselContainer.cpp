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
    //cout<<"data"<<myLetter->getData()<<endl;
  //  myLetter->getData();
    
 //   if(id==0 && myLetter!=nullptr)   cout<<id<<" letter "<<myLetter->getData()<<endl;
    
    ofVec2f p=ofVec2f(position.x,position.y);
    //cout<<"pos"<<p<<endl;
     if(myLetter!=nullptr){
         myLetter->setPosition(p);
     }

}

void CarousselContainer::draw(){
  //  if(id==0 && myLetter!=nullptr)   cout<<id<<" letter "<<myLetter->getData()<<endl;

    
    
    ofPushMatrix();
    ofTranslate(position);
    ofSetColor(255);
  if(debug) ofDrawRectangle(bbox.x+2,bbox.y+2,bbox.getWidth()-2,bbox.getHeight()-2);
    ofSetColor(200,200,255);
    //ofDrawBitmapString(ofToString(id), bbox.getCenter().x, bbox.getCenter().y);
   // if(myLetter !=NULL){
 //       ofDrawBitmapString(myLetter.getData(), bbox.getCenter().x, bbox.getCenter().y);
   // }
    //cout<<myLetter<<endl;
     //   ofDrawBitmapString(myLetter->getData(), bbox.getCenter().x, bbox.getCenter().y);
    
    
    
    if(myLetter!=nullptr){
        ofPushMatrix();
        ofTranslate(dimension.x/2,dimension.y/2);
      //  cout<<id<<" letter "<<myLetter->getData()<<endl;
      // myLetter->draw();
        ofPopMatrix();
    }
    ofSetColor(255, 0, 0,100);
 //   if(bDrawDebugRect && id%20==0)ofDrawRectangle(bbox.getCenter().x, bbox.getCenter().y,10,10);
  //  if(bDrawDebugRect)ofDrawRectangle(bbox.getCenter().x, bbox.getCenter().y,10,10);

    ofPopMatrix();
    
    if(myLetter!=nullptr){
        //  cout<<id<<" letter "<<myLetter->getData()<<endl;
      //  myLetter->draw();
    }
    
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




void CarousselContainer::setDebug(bool _debug){
    debug=_debug;
}



