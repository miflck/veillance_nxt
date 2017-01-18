//
//  Letter.cpp
//  TypeStudy_02
//
//  Created by Fl√ºckiger Michael on 10.10.16.
//
//

#include "Letter.hpp"
#include "Word.h"
#include "Fragment.hpp"
#include "User.hpp"

#include "SceneManager.hpp"


Letter::Letter(){
    data=NULL;
    bIsOnScreen=false;
    node.clearParent();
    //cout<<"node"<<node.getParent()<<endl;
    bRemove=false;
    bRemoveMe=false;
    bWasRemove=false;
    
}

void Letter::setup(){
    position.set(ofRandom(100,500),ofRandom(100,500));
    static LetterEvent newEvent;
    newEvent.message = "New Letter";
    newEvent.letter     = this;
    ofNotifyEvent(LetterEvent::events, newEvent);
    ofRectangle textBounds = font->getStringBoundingBox("H", 0, 0);
    bIsOnScreen=false;
    node.clearParent();
    //cout<<"node"<<node.getParent()<<endl;
    bRemove=false;
    bRemoveMe=false;
    bWasRemove=false;
    
}

void Letter::update(){
    
    //check what to do
    //if(bRemove && !bWasRemove){
    
    if(bRemove)bWasRemove=bRemove;
    
        if(bRemoveMe){
            bRemove=true;
           // cout<<"unregisterLetter "<<this<<endl;
        //STM->unregisterLetter(this);

   /*     bIsOnScreen=false;
        STM->unregisterLetter(this);

        myFragmentPointer->unregisterLetter(this);
        myUserPointer->unregisterLetter(this);

        myWordPointer->unregisterLetter(this);
    */
    }

    
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


void Letter::setData(string _data){
    //data=_data;
    
   // myString=ofToUpper(ofToString(data));
     myString=ofToString(_data);
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


void Letter::setUserPointer(User *_u){
    myUserPointer=_u;
}



void Letter::setPosition(ofVec2f _p){
    if(bRemove)return;
    if(bWasRemove){
    return;
    }else{

    if(getIsOnScreen()){
       // if(STM->totalWordsInBuffer>100)_p+=ofRandom(-1,1);
        
      //if(STM->totalWordsInBuffer>2000) _p.y+=ofRandom(ofMap(STM->totalWordsInBuffer, 2000, 5000, 0, 10));
        
        
        position.set(_p);
        node.setGlobalPosition(position);
    }
    }
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
    //cout<<"setremove "<<this<< data<< " "<<myString<<endl;
    bRemoveMe=_b;//bRemove=_b;
    
    if(bRemoveMe){
        //cout<<"unregisterLetter "<<this<<endl;
        STM->unregisterLetter(this);
        
        /*     bIsOnScreen=false;
         STM->unregisterLetter(this);
         
         myFragmentPointer->unregisterLetter(this);
         myUserPointer->unregisterLetter(this);
         
         myWordPointer->unregisterLetter(this);
         */
        //bWasRemove=bRemove;
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
    if(bIsOnScreen &! bRemove){//check if is on screen
        letterMesh = font->getStringMesh(myString, 0, 0);
       // letterMesh = font->getStringMesh("Ö", 0, 0);

        vector<ofVec3f>& verts = letterMesh.getVertices();
        for(int j=0; j <  verts.size() ; j++){
            letterMesh.setVertex(j,verts[j]*node.getGlobalTransformMatrix());
            if(bIsDrawn){
                letterMesh.addColor(myWordPointer->getColor());
            }else{
                letterMesh.addColor(ofColor(255,0));
                }
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
    if(getIsOnScreen()&&myWordPointer!=nullptr){
        return myWordPointer->getBackgroundColor();
    }
    else{
        return(ofColor(255,0,0));
    }
}

void Letter::explode(){
//setTarget
    bIsExploding=true;
    myWordPointer->explode();

};


