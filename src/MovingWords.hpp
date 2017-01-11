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
#include "ForegroundSound.hpp"


class User;


class MovingWords {
    
public:
    MovingWords();
    void setup();
    void update();
    void draw();
    
    void setData(string data);
    string data;
    string getData();
    
    void setUserPointer(User * _u);
    User * getUserPointer();
    
    
    
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
    
    void applyForce(ofVec3f _f);
    ofVec3f getDockPoint();
    int myDockingNode=0;
    
    // timer
    void setLifeTime(int _t);
    void setLifeSpan(int _t);
    int getLifeTime();
    int getRestLifeTime();
    void startLifeTimer();
    void stopLifeTimer();

    
    int getVowelcount();
    bool isVowel(char c);
    
    bool isVowelForSyllables(char c);

    int countSyllables(string word);
    int getSyllablescount();
    
    
    //hack
    bool bHasSound=false;
    
    void addSound();
    
    
private:
    
    int viewportwidth;
    
    User * userPointer;
    ForegroundSound * foregroundSound;
    
    ofRectangle boundingBox;

    
    int lifetime;
    int lifespan;
    bool bIsLifetimeRunning=false;
    
    bool bIsOnScreen;
    ofVec3f startposition;

    ofVec3f position;
    ofVec3f velocity;
    ofVec3f initvelocity;
    ofVec3f acceleration;

    ofNode node;
    ofVec3f target;
    ofPlanePrimitive plane;    

    bool bIsAlive=false;
    
    
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
    
    
    bool bIsRotating=true;
    
    int numvowels=0;
    int numsyllables=0;
    
    
    string vouwels="";
};


#endif /* MovingWords_hpp */
