//
//  MovingWords.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#ifndef MovingWords_hpp
#define MovingWords_hpp

#include <stdio.h>
#include "ofMain.h"


class MovingWords {
    
public:
    MovingWords();
    void setup();
    void update();
    void draw();
    
    void setData(string data);
    string data;
    string getData();
    
    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);
    ofRectangle textBounds;

    bool bRemove=false;
    
    
    void setStartPosition(ofVec3f _p);
    void setPosition(ofVec3f _p);
    ofVec3f getPosition();
    void setVelocity(ofVec3f _v);
    
    
    void setInitVelocity(ofVec3f _v);

    ofVec3f getVelocity();
    void setTarget(ofVec3f _t);
    ofVec3f getTarget();
    
    
    void move();
    void startMoving();
    void stopMoving();
    bool bIsMoving=false;
    float maxspeed=10;
    
    
    void setIsAlive(bool _b);
    bool checkIsAlive();
    
    
    
    ofVboMesh getUpdatedVboMesh();

    
    ofColor myColor;

    
    
    
private:
    
    bool bIsOnScreen;
    
    ofVec3f startposition;

    ofVec3f position;
    ofVec3f velocity;
    
    ofVec3f initvelocity;

    
    ofVec3f acceleration;

    ofNode node;
    ofVec3f target;
    ofPlanePrimitive plane;    
    ofBoxPrimitive geometry;

    bool bIsAlive=false;
    
    int maxdistance;
    
    float rollspeed;
    float panspeed;
    float tiltspeed;
    
    float rollangle;
    float panangle;
    float tiltangle;
    
    
    ofVboMesh vbom;
    ofVboMesh letterMesh;
    
    
    float scalefact;
    float spacingFact;
    
    ofVec3f lookat;
    
    
};


#endif /* MovingWords_hpp */
