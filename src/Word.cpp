//
//  Word.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#include "Word.h"
#include "Letter.hpp"
#include "StreamManager.hpp"

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

}

void Word::update(){
    
    lerpColor();
    int now=ofGetElapsedTimeMillis();
    bool isOnScreen=checkIsOnScreen();

    if(isOnScreen&!wasOnScreen){
        lifespan=int(ofRandom(20000,150000));
        lifeTime=ofGetElapsedTimeMillis()+lifespan;
        bIsAlive=true;
        //startColorLerp();
        if(bIsSuggestion)startColorLerp();

        lerpColorAmount=0.0f;
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
            //STM->bkg.draw(getPosition().x-250,getPosition().y-10*i,getBoundingBox().width,20*i);

         ofDrawRectangle(getPosition().x-getBoundingBox().width/2,getPosition().y-10*i, getBoundingBox().width*2,20*i);
        }
        
        ofSetColor(255,0,0);
        
        //STM->bkg.draw(getPosition().x-500,getPosition().y-500,1000,1000);

       ofDisableBlendMode();
 

       // ofDrawRectangle(getPosition().x,getPosition().y-30, getBoundingBox().width-10,60);

        /*ofSetColor(255,0,0,100);
        ofDrawRectangle(getPosition().x,getPosition().y-10, getBoundingBox().width-10,20);
        ofDrawRectangle(getPosition().x,getPosition().y-5, getBoundingBox().width-10,20);*/
        
        //STM->bkg.draw(getPosition().x,getPosition().y-50,100,200);


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


void Word::setIsSuggestion(bool _s){
    bIsSuggestion=_s;
    if(bIsSuggestion)targetColor=mySuggestionColor;
}


void Word::addLetterPointer(Letter *_l){
    myLetters.push_back(_l);
}


void Word::registerLetter(Letter *_l){
    myLetters.push_back(_l);
}

void Word::unregisterLetter(Letter *_l){
    auto it = std::find(myLetters.begin(), myLetters.end(), _l);
    if (it != myLetters.end()) { myLetters.erase(it); }
    
    
    if(myLetters.size()==0){
        setBRemove(true);
        myFragmentPointer->unregisterWord(this);
       // cout<<"remove word"<<data<<endl;
    }
    
   /// myLetters.push_back(_l);
}

void Word::setFragmentPointer(Fragment *_f){
    myFragmentPointer=_f;
}



void Word::setColor(ofColor _c){
    myColor=_c;
}


ofColor Word::getColor(){
    return myColor;
}

ofColor Word::getBackgroundColor(){
    return backgroundColor;
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
    if(myLetters.size()>1){
     b= myLetters[myLetters.size()-1]->getIsOnScreen();
    }
    return b;

}

int Word::getIndex(){
    return wordIndex;
}

void Word::setIsDrawn(bool _isDrawn){
    for(auto letter:myLetters){
        letter->setIsDrawn(_isDrawn);
    }
}
