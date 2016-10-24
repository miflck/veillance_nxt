//
//  Word.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//


#pragma once



#ifndef Word_h
#define Word_h

#include <stdio.h>

#include "ofMain.h"
//#include "Letter.hpp"
#include "LetterEvent.hpp"

class Letter;

class Word {
    
public:
    Word();
    
    
    void setup(int _index);
    void update();
    void draw();
    
    
    //DATA
    string data; //declare a vector of strings to store data
    void setData(string _data);
    
    void addLetterPointer(Letter * _l);
    vector<Letter *> myLetters;

    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);
    void setPosition(ofVec3f pos);
    ofVec3f getPosition();
    ofVec3f position;
    float getWidth();
    float wordwidth;
    
    
    int wordIndex=0;
    
    void setLifeTime(int _lifeTime);
    
    
    void setIsSuggestion(bool _s);
    
    ofColor myColor;
    ofColor mySuggestionColor;

    void setColor(ofColor _c);
    ofColor getColor();
    
    
private:
    
  bool  bIsMovingWord=false;
  bool  bIsSuggestion=false;
    
    int lifeTime;
    bool bIsAlive=false;
    
    
};



#endif /* Word_h */
