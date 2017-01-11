//
//  CarousselContainer.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
// This is a caroussel item. its holding a pointer to the assignet letter
//
//

#ifndef CarousselContainer_hpp
#define CarousselContainer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Letter.hpp"


class CarousselContainer{
    
public:
    CarousselContainer();
    virtual ~CarousselContainer();

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
    
    
    void setVelocity(ofVec2f _v);
    
    
    void setTarget(ofVec2f _target);
    ofVec2f getTarget();
    ofVec2f target;

    
    void setDimension(ofVec2f _dimension);
    ofVec2f getDimension();
    
    void setId(int _id);
    void setStackId(int _id);
    int id;
    int stackId;
    
    char c=' ';
    
    char getChar();
    void setChar(char _c);
    
    
    
    Letter*  myLetter=nullptr;
    void setLetterPointer(Letter * _l);
    
    void registerLetter(Letter * _l);
    void unregisterLetter();
    
    
    Letter* getLetterPointer();
    
    
    bool bDrawDebugRect=true;
    
    bool bHasPointer=false;

    
    void setDebug(bool _debug);
    
    ofColor getBackgroundColor();
    void explode();
    
private:
    
    bool debug=false;
    ofVec2f velocity;
    
   bool bIsExploding=false;
    
    
};

#endif /* CarousselContainer_hpp */
