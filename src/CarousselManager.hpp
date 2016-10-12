//
//  CarousselManager.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#ifndef CarousselManager_hpp
#define CarousselManager_hpp

#include <stdio.h>

#include "ofMain.h"
#include "CarousselContainer.hpp"


class CarousselManager {
    
public:
    CarousselManager();
    void setup();
    void update();
    void draw();
    
    vector<CarousselContainer>containers;
    
    float speed;
    void move(ofVec2f target, CarousselContainer *c);
    void move();

    
    void startMoving();
    void stopMoving();
    bool bIsMoving=false;
    ofVec2f target;
    
    void cicle();
    
    
    int maxspeed;
private:
};


#endif /* CarousselManager_hpp */
