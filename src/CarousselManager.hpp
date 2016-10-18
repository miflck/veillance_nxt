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


#include "Letter.hpp"


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
  //  void move(ofVec2f target, CarousselContainer *c);
    void move();

    
    void startMoving();
    void stopMoving();
    bool bIsMoving=false;
    ofVec2f target;
    
    void cicle();
    
    
    double maxspeed;
    
    void setId(int _id);
    
    
    vector<Letter *>buffer;
    
   // vector<Letter *>letterbuffer;
    
   // void addMovement(char _c);

    void addMovement(Letter *l);

    
    
    char getLastElementChar();
    Letter* getLastElementPointer();
    
    
private:
    
    int id;
    
   // Letter HackBaseLetter;

    
};


#endif /* CarousselManager_hpp */
