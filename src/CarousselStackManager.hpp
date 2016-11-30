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
    void setup(ofVec2f _position,float _mywidth, float _myheight);
    void update();
    void draw();
    
    void carousselEvent(CarousselEvent &e);

    ofVec2f position;
    
    
    vector<CarousselLineManager> cms;
    
    //void carousselEvent(CarousselEvent &e);
    
    
    int maxspeed;
    int minspeed=2;
    
    
    void setId(int _id);
    
private:
    int id;
    bool bDebugDraw=false;
    
    float mywidth;
    float myheight;
    
    float containerWidth;
    float containerHeight;
    
    
    

};



#endif /* CarousselStackManager_hpp */
