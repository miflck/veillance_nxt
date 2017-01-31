//
//  CarousselManager.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#ifndef VerticalCaroussell_hpp
#define VerticalCaroussell_hpp

#include <stdio.h>

#include "ofMain.h"
#include "VerticalCarousselContainer.hpp"
#include "CarousselEvent.hpp"

#include "helpers.hpp"
#include "Letter.hpp"



class VerticalCaroussel {
    
public:
    VerticalCaroussel
    ();
    void setup(ofVec2f _position,float _mywidth, float _myheight, float _width,float _height);
    void update();
    void draw();
    
    vector<VerticalCarousselContainer>containers;
    
    ofVec2f position;
    void setPosition(ofVec2f _p);
    
    void startMoving();
    void move();

    void stopMoving();
    bool bIsMoving=false;
    ofVec2f target;
    float speed;

    
    void checkBuffer();
    void cicle();
    
    
    double maxspeed;
    
    
    vector<string>buffer;
    vector<dns>dnsbuffer;



    void addMovement(string _s);
    
    void addMovement(dns _dns);


    
    void setDebugDraw(bool _b);
    void explode();
    
   
    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);

    
    void setColor(ofColor _c);
    
    
private:
    int counter=0;
    int deleter=0;
    int id;
    bool bDebugDraw=true;
    
    float mywidth;
    float myheight;
    
    float containerWidth, containerHeight;
    
    bool bIsExploding=false;
    bool bStoppedExploding=false;
    
    
   // Letter HackBaseLetter;

    
};


#endif /* CarousselManager_hpp */
