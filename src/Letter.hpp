//
//  Letter.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#ifndef Letter_hpp
#define Letter_hpp

#pragma once


#include <stdio.h>

#include <stdio.h>
#include "ofMain.h"
#include "LetterEvent.hpp"



class Word;
class Fragment;
class User;

class Letter {
    
public:
    Letter();
    virtual ~Letter();

    void setup();
    void update();
    void draw();
    
    ofRectangle textBounds;


    
    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);
    
    //void setData(char data);
    void setData(string data);

    char data;
    
    
    string myString;
    string getString();
    
    char getData();
    
    
    ofVboMesh getUpdatedVboMesh();
    
    void setWordId(int _id);
    int getWordId();
    
    void setDebug(bool debug);
    bool debug=false;
    
    
    Word * myWordPointer;
    void setWordPointer(Word * w);
    
    
    Fragment * myFragmentPointer;
    void setFragmentPointer(Fragment * f);
    
    User * myUserPointer;
    void setUserPointer(User * u);
    
    
    void setPosition(ofVec2f p);
    ofVec2f getPosition();
    
    void setVelocity(ofVec2f _v);
    ofVec2f getVelocity();
    
    void setIsDrawn(bool _b);
    
    
    void setIsOnScreen(bool _s);
    bool getIsOnScreen();
    
    void setBRemove(bool _b);
    bool getBRemove();
    
    
    ofColor getColor();
    ofColor getBackgroundColor();
    bool bRemoveMe;
    
    
    void explode();
private:
    bool bRemove=false;
    bool bWasRemove=false;

    bool bIsExploding=false;

    
    ofVec2f position;
    ofVec2f velocity;
    int wordId;
    bool bIsDrawn=true;
    bool bIsOnScreen=false;
    
    
    //ofNode node;
    ofMesh letterMesh;
    ofMesh originalletterMesh;

    float angle=0;
    
    ofVboMesh vbom;
    

    ofColor myColor;
    
};


#endif /* Letter_hpp */
