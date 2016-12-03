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


class CarousselStackManager {
    
public:
    CarousselStackManager();
    void setup(int _id, ofVec2f _position,float _mywidth, float _myheight);
    void update();
    void draw();
    
    void carousselEvent(CarousselEvent &e);

    ofVec2f position;
    
    
    vector<CarousselLineManager> cms;
    
    //void carousselEvent(CarousselEvent &e);
    
    
    float maxspeed;
    float minspeed=3;
    
    
    void setId(int _id);
    void setStackId(int _id);
    
    void addMovement(Letter * l);
    void unregisterLetter(Letter *l);

    
private:
    int id;
    int stackId;
    bool bDebugDraw=false;
    
    float mywidth;
    float myheight;
    
    float containerWidth;
    float containerHeight;
    
    
    

};



#endif /* CarousselStackManager_hpp */
