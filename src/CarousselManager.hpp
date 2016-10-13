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
#include "CarousselEvent.hpp"


class CarousselManager {
    
public:
    CarousselManager();
    void setup(ofVec2f _position,float _width,float _height);
    void update();
    void draw();
    
    vector<CarousselContainer>containers;
    
    ofVec2f position;
    float width;
    
    float speed;
    void move(ofVec2f target, CarousselContainer *c);
    void move();

    
    void startMoving();
    void stopMoving();
    bool bIsMoving=false;
    ofVec2f target;
    
    void cicle();
    
    
    float maxspeed;
    
    void setId(int _id);
    
    
    vector<char>buffer;
    void addMovement(char _c);

    char getLastElementChar();
    
    
private:
    
    int id;
    
};


#endif /* CarousselManager_hpp */
