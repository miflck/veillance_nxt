//
//  Word.cpp
//  TypeStudy_02
//
//  Created by Fl√ºckiger Michael on 10.10.16.
//
//

#include "Word.h"
#include "Letter.hpp"
#include "SceneManager.hpp"
#include "User.hpp"

Word::Word(){
}

void Word::setup(int _index){
    //cout<<"index"<<_index<<endl;
    wordIndex=_index;
    lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(50000,200000));
    
    backgroundColor=ofColor(ofRandom(50,255),ofRandom(50,255),ofRandom(50,255));
    myColor=ofColor(0,0,255);
    myInitColor=ofColor(0,0,255);
    
    mySuggestionColor=ofColor(0,191,255);
    targetColor=ofColor(0,0,255);
    // bIsAlive=true;
    lerpColorAmount=0.0f;
    bIsDrawn=true;
    
    
}

void Word::update(){
    if(checkShouldRemove()){
    setBRemove(true);
    myFragmentPointer->unregisterWord(this);
    myUserPointer->unregisterWord(this);
    }
    
    lerpColor();
    int now=ofGetElapsedTimeMillis();
    bool isOnScreen=checkIsOnScreen();
   // cout<<myFragmentPointer->getFragmentId()<<endl;
    
    
    if(isOnScreen &! wasOnScreen){
        //lifespan=int(ofRandom(20000,150000));
        //lifeTime=ofGetElapsedTimeMillis()+lifespan;
        bIsAlive=true;
        //startColorLerp();
        //if(bIsSuggestion)startColorLerp();
        
        //lerpColorAmount=0.0f;
    }
    
    
    if(bIsAlive && bIsSuggestion && now>lifeTime){
        /* bIsAlive=false;
         myColor=ofColor(0,0,0);
         STM->addMovingWord(this);
         
         for(auto letter:myLetters){
         letter->setIsDrawn(false);
         }*/
        
        makeMovingWord();
        
    }
    
    wasOnScreen=isOnScreen;
    
}






void Word::draw(){
    ofSetColor(backgroundColor,100);
    if(getPosition().length()>3){
        STM->backgroundFbo.begin();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        
        for(int i=0;i<5;i++){
            
            ofDrawRectangle(getPosition().x-getBoundingBox().width/2,getPosition().y-10*i, getBoundingBox().width*2,20*i);
        }
        
        ofSetColor(255,0,0);
        
        
        ofDisableBlendMode();
        
        
        // ofDrawRectangle(getPosition().x,getPosition().y-30, getBoundingBox().width-10,60);
        
        /*ofSetColor(255,0,0,100);
         ofDrawRectangle(getPosition().x,getPosition().y-10, getBoundingBox().width-10,20);
         ofDrawRectangle(getPosition().x,getPosition().y-5, getBoundingBox().width-10,20);*/
        
        
        
        STM->backgroundFbo.end();
    }
}

void Word::setData(string _data){
    data=_data;
}

string Word::getMyData(){
    return data;
}

void Word::setFont(ofTrueTypeFont *f){
    font=f;
}


float Word::getWidth(){
    return wordwidth;
};


ofRectangle Word::getBoundingBox(){
    ofVec2f p=myLetters[0]->getPosition();
    ofVec2f p2=myLetters[myLetters.size()-1]->getPosition();
    return ofRectangle(p,p2);
    
}


ofVec3f Word::getPosition(){
    ofVec2f p=myLetters[0]->getPosition();
    position.set(p);
    return position;
}




void Word::setPosition(ofVec3f pos){
    position.set(pos);
}

void Word::setVelocity(ofVec3f _v){
    velocity.set(_v);
}

ofVec3f Word::getVelocity(){
    // return velocity;
    
    ofVec2f v=myLetters[0]->getVelocity();
    velocity.set(v.x,v.y,0);
    return velocity;
}


void Word::setLifeTime(int _lifeTime){
    lifeTime=_lifeTime;
}





void Word::addLetterPointer(Letter *_l){
    myLetters.push_back(_l);
}


void Word::registerLetter(Letter *_l){
    myLetters.push_back(_l);
}

void Word::unregisterLetter(Letter *_l){
    
   // cout<<" unregister letter "<<_l<<" "<<_l->getData()<<"from word"<<myFragmentPointer->getFragmentId()<<endl;
    auto it = std::find(myLetters.begin(), myLetters.end(), _l);
    if (it != myLetters.end()) {
        myLetters.erase(it);
    }
}

void Word::setFragmentPointer(Fragment *_f){
    myFragmentPointer=_f;
}


void Word::setUserPointer(User *_u){
    myUserPointer=_u;
}

User * Word::getUserPointer(){
    return myUserPointer;
}


void Word::setColor(ofColor _c){
    myColor=_c;
}


ofColor Word::getColor(){
    
    // schwerfällig?
    if(bIsDrawn && ! bIsExploding){
        switch (STM->drawMode) {
            case 0:
                return myColor;
                break;
            case 1:
                return ofColor(255);
                break;
            case 2:
                
                myFragmentPointer->getFragmentId();
                return myFragmentPointer->getBackgroundColor();
                break;
                
                
            default:
                return myColor;
                break;
        }
    }
    
    else if(bIsDrawn && bIsExploding){
         return myColor;
    }
    
    
    
    else{
        return ofColor(0);
        
    }
    
    
    
    
    
    
}

ofColor Word::getBackgroundColor(){
    ofColor c=myFragmentPointer->getBackgroundColor();
    return c;//backgroundColor;
}



void Word::makeMovingWord(){
    
    bIsAlive=false;
    myColor=ofColor(0,0,0);
    STM->addMovingWord(this);
    
    
    /* for(auto letter:myLetters){
     letter->setIsDrawn(false);
     }*/
    
    
}


void Word::startColorLerp(){
    bIsColorLerp=true;
}

void Word::stopColorLerp(){
    bIsColorLerp=false;
    
}

void Word::lerpColor(){
    if(bIsColorLerp){
        int now=ofGetElapsedTimeMillis();
        float amount=ofMap(lifeTime-now,lifespan,0,0,1);
        lerpColorAmount=amount;
        
        
        
        
        
        
        ofColor c=myInitColor;
        c.lerp(targetColor,lerpColorAmount) ;
        myColor=c;
        
        
        
        
        if(lerpColorAmount>0.99){
            lerpColorAmount=1;
            stopColorLerp();
        }
    }
}



void Word::setBRemove(bool _r){
    bRemove=_r;
}

bool Word::getBRemove(){
    return bRemove;
}


bool Word::checkShouldRemove(){
    bool b=false;
    if(myLetters.size()==0)b = true;
    return b;
}



bool Word::checkIsOnScreen(){
    bool b=false;
    if(myLetters.size()>0){
        b= myLetters[myLetters.size()-1]->getIsOnScreen();
    }
    return b;
    
}



void Word::setIsSuggestion(bool _s){
    bIsSuggestion=_s;
    if(bIsSuggestion){
        lock(true);
        targetColor=mySuggestionColor;
        lifespan=int(ofRandom(20000,150000));
        lifeTime=ofGetElapsedTimeMillis()+lifespan;
        startColorLerp();
        lerpColorAmount=0.0f;
    }
}

bool Word::getIsSuggestion(){
    return bIsSuggestion;
}


int Word::getIndex(){
    return wordIndex;
}

void Word::setIsDrawn(bool _isDrawn){
    bIsDrawn=_isDrawn;
    for(auto letter:myLetters){
        letter->setIsDrawn(_isDrawn);
    }
}

bool Word::getIsDrawn(){
    return bIsDrawn;
}


void Word::lock(bool _l){
    bIsLocked=_l;
}

bool Word::getIsLocked(){
    return bIsLocked;
}

void Word::explode(){
    bIsExploding=true;
    targetColor=ofColor(0,0);
    myColor=ofColor(255);
    lifespan=3000;
    lifeTime=ofGetElapsedTimeMillis()+lifespan;
    startColorLerp();
    lerpColorAmount=0.0f;
}

