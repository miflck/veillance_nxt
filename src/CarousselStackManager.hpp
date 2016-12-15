//
//  CarousselStackManager.hpp
//  Veillance
//
//  Created by Flückiger Michael on 30.11.16.
//
//

#ifndef CarousselStackManager_hpp
#define CarousselStackManager_hpp

#include <stdio.h>
#include "ofMain.h"

#include "CarousselLineManager.hpp"
#include "CarousselEvent.hpp"
#include "helpers.hpp"






class CarousselStackManager {
    
    
    
    
public:
    CarousselStackManager();
    virtual ~ CarousselStackManager();

    
    
    void setup(int _id, ofVec2f _position,float _mywidth, float _myheight);
    void update();
    void draw();
    
    void carousselEvent(CarousselEvent &e);

    ofVec2f position;
    ofVec2f getPosition();
    
    
    vector<CarousselLineManager*> cms;
    float minspeed;
    
    
    void setId(int _id);
    void setStackId(int _id);
    
    void addMovement(Letter * l);
    void unregisterLetter(Letter *l);
    
    void explode();

    
    map<Letter *, Letter *> letterbuffer;
    
    void addMessage(message _m);
    message mymessage;
    
    void addDataFromBuffer();
    
    vector<string > messagestring;
    

    int getStringsize();
    
    ofColor getBackgroundColor();
    
    void startCountdown();
    void stopCountDown();
    
    bool bIsCountingDown=false;
    float lifespan;
    float lifetime;
    
private:
    
    
    
    int id;
    int stackId=99;
    bool bDebugDraw=false;
    
    float mywidth;
    float myheight;
    
    float containerWidth;
    float containerHeight;

    bool bIsExploding;
    
    
    

};



#endif /* CarousselStackManager_hpp */
