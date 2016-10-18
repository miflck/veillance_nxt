//
//  Word.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#ifndef Word_h
#define Word_h

#include <stdio.h>

#include "ofMain.h"
#include "Letter.hpp"
#include "LetterEvent.hpp"


class Word {
    
public:
    Word();
    
    
    void setup(int _index);
    void update();
    void draw();
    
    
    //DATA
    string data; //declare a vector of strings to store data
    void setData(string _data);
    
    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);
    void setPosition(ofVec3f pos);
    ofVec3f getPosition();
    ofVec3f position;
    float getWidth();
    float wordwidth;
    vector<Letter> letters;
    
    int wordIndex;
    
private:
};



#endif /* Word_h */
