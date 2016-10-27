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
    cout<<"index"<<_index<<endl;
    wordIndex=_index;
    lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(50000,200000));
    
   // myColor=ofColor(ofRandom(200,255),ofRandom(200,255),ofRandom(200,255));
    myColor=ofColor(0,0,255);

    mySuggestionColor=ofColor(0,191,255);
   // bIsAlive=true;

}

void Word::update(){
    
    int now=ofGetElapsedTimeMillis();

    if(!wasOnScreen){
        bool isOnScreen=checkIsOnScreen();
        lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(20000,150000));
        bIsAlive=true;
        wasOnScreen=isOnScreen;
    }
    
    
    if(bIsAlive && bIsSuggestion && now>lifeTime){
        bIsAlive=false;
        myColor=ofColor(0,0,0);
        STM->addMovingWord(this);
        
        for(auto letter:myLetters){
            letter->setIsDrawn(false);
        }
    }
}

void Word::draw(){
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

ofVec3f Word::getPosition(){
    ofVec2f p=myLetters[0]->getPosition();
    position.set(p);
    return position;

}

void Word::setPosition(ofVec3f pos){
    position.set(pos);
  }

void Word::setLifeTime(int _lifeTime){
    lifeTime=_lifeTime;
}


void Word::setIsSuggestion(bool _s){
    bIsSuggestion=_s;
    if(bIsSuggestion)myColor=mySuggestionColor;
}


void Word::addLetterPointer(Letter *_l){
    myLetters.push_back(_l);
}


void Word::setColor(ofColor _c){
    myColor=_c;
}

ofColor Word::getColor(){
    return myColor;
}


bool Word::checkIsOnScreen(){
    bool b=false;
    if(myLetters.size()>1){
     b= myLetters[myLetters.size()-1]->getIsOnScreen();
    }
    return b;

}



