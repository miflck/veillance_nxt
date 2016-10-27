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

class Letter {
    
public:
    Letter();
    void setup();
    void update();
    void draw();
    
    ofRectangle textBounds;


    
    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);
    
    void setData(char data);
    char data;
    
    string myString;
    
    char getData();
    
   bool bRemove=false;
    
    ofVboMesh originalVboMesh;
    ofVboMesh getOriginalVboMesh();
    void makeOriginalVboMesh();
    
    void setWordId(int _id);
    int getWordId();
    
    void setDebug(bool debug);
    bool debug=false;
    
    
    Word * myWordPointer;
    void setWordPointer(Word * w);
    
    
    void setPosition(ofVec2f p);
    ofVec2f getPosition();
    
    void setIsDrawn(bool _b);
    
    
    void setIsOnScreen(bool _s);
    bool getIsOnScreen();
    
private:
    
    ofVec2f position;
    int wordId;
    bool bIsDrawn=true;
    bool bIsOnScreen=false;
    
    
};


#endif /* Letter_hpp */
