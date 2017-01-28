//
//  VerticalCarousselContainer.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
// This is a caroussel item. its holding a pointer to the assignet letter
//
//

#ifndef VerticalCarousselContainer_hpp
#define VerticalCarousselContainer_hpp

#include <stdio.h>
#include "ofMain.h"


class VerticalCarousselContainer{
    
public:
    VerticalCarousselContainer();
    
    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);
    
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
    int id;
    
    
    void setString(string _s);
    string mystring="";
    
    
    bool bDrawDebugRect=true;
    
    void setDebug(bool _debug);
    void explode();
    
    
    ofColor color;
    void setColor(ofColor _color);
    
private:
    
    bool debug=false;
    ofVec2f velocity;
    
   bool bIsExploding=false;
    
    
};

#endif /* VerticalCarousselContainer_hpp */
