//
//  Letter.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#ifndef Letter_hpp
#define Letter_hpp

#include <stdio.h>

#include <stdio.h>
#include "ofMain.h"
#include "LetterEvent.hpp"


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
    
    char getData();
    
   bool bRemove=false;
    
    ofVboMesh originalVboMesh;
    ofVboMesh getOriginalVboMesh();
    void makeOriginalVboMesh();
    
    
    
private:
    
    ofVec2f position;
    
};


#endif /* Letter_hpp */
