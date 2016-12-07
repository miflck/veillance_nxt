//
//  CarousselManager.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#ifndef CarousselLineManager_hpp
#define CarousselLineManager_hpp

#include <stdio.h>

#include "ofMain.h"
#include "CarousselContainer.hpp"
#include "CarousselEvent.hpp"


#include "Letter.hpp"



class CarousselLineManager {
    
public:
    CarousselLineManager();
    void setup(int numlines, int _stackId,int _lineId, ofVec2f _position,float _mywidth, float _myheight, float _width,float _height);
    void update();
    void draw();
    
    
    
    
    
    
    
    vector<CarousselContainer>containers;
    
    ofVec2f position;
    void setPosition(ofVec2f _p);
    
    float width;
    
    float speed;
  //  void move(ofVec2f target, CarousselContainer *c);
    void move();

    
    void startMoving();
    void stopMoving();
    bool bIsMoving=false;
    ofVec2f target;
    
    
    void checkBuffer();
    
    void cicle();
    
    
    double maxspeed;
    
    void setId(int _id);
    void setStackId(int _id);
    
    vector<Letter *>buffer;


    
   // vector<Letter *>letterbuffer;
    
   // void addMovement(char _c);

    void addMovement(Letter *l);

    
    
    char getLastElementChar();
    Letter* getLastElementPointer();
    
    void setDebugDraw(bool _b);
    
    void explode();
    
    void unregisterLetter(Letter * _l);

    
private:
    int counter=0;
    int deleter=0;
    int numlines;
    int id;
    int lineId;
    int stackId;
    bool bDebugDraw=false;
    
    float mywidth;
    float myheight;
    
    float letterWidth, letterHeight;
    
    bool bIsExploding=false;
    
    
   // Letter HackBaseLetter;

    
};


#endif /* CarousselManager_hpp */
