//
//  CarousselContainer.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#ifndef CarousselContainer_hpp
#define CarousselContainer_hpp

#include <stdio.h>
#include "ofMain.h"


class CarousselContainer{
    
public:
    CarousselContainer();
    void setup();
    void update();
    void draw();
    
    
    ofRectangle bbox;
    
    ofVec3f position;
    ofVec2f dimension;
    
    
    bool bIsMoving;

    
    void setBoundingBox(ofVec3f position, ofVec2f dimension);
    
    void setPosition(ofVec2f _pos);
    ofVec2f getPosition();
    
    void setTarget(ofVec2f _target);
    ofVec2f getTarget();
    ofVec2f target;

    
    void setDimension(ofVec2f _dimension);
    ofVec2f getDimension();
    
    int id;
    
    char c=' ';
    
    char getChar();
    void setChar(char _c);
    
private:
};

#endif /* CarousselContainer_hpp */
