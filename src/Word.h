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
class Fragment;

class Word {
    
public:
    Word();
    
    
    void setup(int _index);
    void update();
    void draw();
    
    
    //DATA
    void setData(string _data);
    string getMyData();
    
    void addLetterPointer(Letter * _l);
    void removeLetterPointer(Letter * _l);
    
    void registerLetter(Letter * _l);
    void unregisterLetter(Letter * _l);
    
    Fragment * myFragmentPointer;
    void setFragmentPointer(Fragment * _f);


    vector<Letter *> myLetters;

    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);
    void setPosition(ofVec3f pos);
    ofVec3f getPosition();
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f getVelocity();
    void setVelocity(ofVec3f _v);
    
    ofRectangle boundingbox;
    
    ofRectangle getBoundingBox();
    
    
    float getWidth();
    float wordwidth;
    
    
    int wordIndex=0;
    
    void setLifeTime(int _lifeTime);
    
    
    void setIsSuggestion(bool _s);
    
    ofColor myColor;
    ofColor myInitColor;

    ofColor mySuggestionColor;
    ofColor targetColor;
    ofColor randomColor;


    void setColor(ofColor _c);
    ofColor getColor();
    
    bool checkIsOnScreen();
    
    
    void makeMovingWord();
    
    
    int getIndex();
    
    
    void setIsDrawn(bool _isDrawn);
    
    void startColorLerp();
    void stopColorLerp();
    void lerpColor();
    
    
    void setBRemove(bool _r);
    bool getBRemove();
    
    bool checkShouldRemove();
    
    
    
private:
    
    bool bRemove=false;
    
    string data; //declare a vector of strings to store data
    float lerpColorAmount;
    
    int lifespan;

    
  bool  bIsMovingWord=false;
  bool  bIsSuggestion=false;
    
    int lifeTime;
    bool bIsAlive=false;
    
    bool bIsOnScreen=false;
    bool wasOnScreen=false;
    
    bool bIsColorLerp=false;
    
};



#endif /* Word_h */
