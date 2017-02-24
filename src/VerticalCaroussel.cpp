//
//  CarousselManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#include "VerticalCaroussel.hpp"
#include "SceneManager.hpp"

VerticalCaroussel::VerticalCaroussel(){
}

void VerticalCaroussel::setup( ofVec2f _position,float _mywidth, float _myheight, float _width,float _height){
    
    
    
    
    position.set(_position);
    mywidth=_mywidth;
    myheight=_myheight;
    
    containerWidth=_width;
    containerHeight=_height;
    
    maxspeed=.5;//;l/5;
    
    ofVec3f pos = ofVec3f(position.x,position.y);
    float dl=myheight/containerHeight;
    for(int i=0;i<dl;i++){
        VerticalCarousselContainer c;
        c.setFont(font);
        c.setBoundingBox(pos, ofVec2f(containerWidth,containerHeight));
        c.id=i;
        containers.push_back(c);
        pos.y+=containerHeight;
    }
    
    
}




void VerticalCaroussel::update(){
    maxspeed=ofMap(dnsbuffer.size(),0,10,2,8,true);

    if(bIsMoving){
        move();
    }
    
    for(int i=0;i<containers.size();i++){
        containers[i].update();
    }
    
}

void VerticalCaroussel::draw(){
    if(bDebugDraw){
    for(int i=0;i<containers.size();i++){
        containers[i].draw();
    }
    }
}


void VerticalCaroussel::move(){
    
    for(int i=0;i<containers.size();i++){
        ofVec2f p=containers[i].getPosition();

        ofVec2f target=containers[i].getTarget();
        
        
        ofVec2f dist=target-p;
        ofVec2f speed=dist;
       speed.limit(maxspeed);
        p+=speed;
        
       // if(dist.length()<(maxspeed)+1){
        if(dist.length()<maxspeed){
            p.set(target);
            speed.set(ofVec2f(0,0));
            containers[i].bIsMoving=false;
        }
        
       // p.y+=ofRandom(-0.5,0.5);
        containers[i].setPosition(p);
        containers[i].setVelocity(speed);
        /* if(p==target){
         containers[i].bIsMoving=false;
         }*/
    }
    
    //check if finished;
    bool move=false;
    for(int i=0;i<containers.size();i++){
        if(containers[i].bIsMoving){
            move=true;
            break;
        }
    }
    if(!move){
        stopMoving();
    }

}



void VerticalCaroussel::cicle(){
    if(!bIsMoving){
        for(int i=1;i<containers.size();i++){
            containers[i].setTarget(containers[i-1].getPosition());
        }
        ofVec2f p=containers[containers.size()-1].getPosition();
        ofVec2f d=ofVec2f(0,containers[containers.size()-1].getDimension().y);
        containers[0].setPosition(p+d);
        containers[0].setTarget(p);

        std::rotate(containers.begin(),containers.begin()+1,containers.end());
        startMoving();
    }
}

void VerticalCaroussel::startMoving(){
    
    dns d=dnsbuffer[0];
    
    
    string s=d.text;
    dnsbuffer.erase(dnsbuffer.begin());
    containers[containers.size()-1].setString(s);
    containers[containers.size()-1].setColor(d.color);

    
    
    
    
   /* static CarousselEvent newEvent;
    newEvent.message = "START";
    newEvent.id=id;
    newEvent.stackId=stackId;
    newEvent.lineId=lineId;
    ofNotifyEvent(CarousselEvent::events, newEvent);
    */
    
    bIsMoving=true;
    for(int i=1;i<containers.size();i++){
        containers[i].bIsMoving=true;
    }
}

void VerticalCaroussel::stopMoving(){
    bIsMoving=false;
    checkBuffer();
   /* if(!bIsExploding){
        bIsMoving=false;
        static CarousselEvent newEvent;
        newEvent.message = "STOP";
        newEvent.id=id;
        newEvent.stackId=stackId;
        newEvent.lineId=lineId;
        ofNotifyEvent(CarousselEvent::events, newEvent);
        checkBuffer();
    }else{
        bStoppedExploding=true;
        static CarousselEvent newEvent;
        newEvent.message = "EXPLODE STOP";
        newEvent.id=id;
        newEvent.stackId=stackId;
        newEvent.lineId=lineId;
        ofNotifyEvent(CarousselEvent::events, newEvent);
    }*/
}


void VerticalCaroussel::checkBuffer(){
    //check if we have some movement in buffer
    if(!bIsMoving){
        if(dnsbuffer.size()>0){
            cicle();
        }
    }
}




void VerticalCaroussel::setPosition(ofVec2f _p){
    position.set(_p);
}




void VerticalCaroussel::addMovement(string _s){
    buffer.push_back(_s);
    cicle();
}



void VerticalCaroussel::addMovement(dns _dns){
    dnsbuffer.push_back(_dns);
    cicle();
}


void VerticalCaroussel::setDebugDraw(bool _d){
    bDebugDraw=_d;
};

void VerticalCaroussel::explode(){
    bIsExploding=true;
    bIsMoving=true;
    for(int i=1;i<containers.size();i++){
        containers[i].explode();
        containers[i].setTarget(ofVec3f(ofRandom(-mywidth,2*mywidth),ofRandom(-myheight,2*myheight),ofRandom(-1000,1000)));
    }
    
}
void VerticalCaroussel::setFont(ofTrueTypeFont *f){
    font=f;    
}



