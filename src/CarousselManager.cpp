//
//  CarousselManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#include "CarousselManager.hpp"
CarousselManager::CarousselManager(){
}

void CarousselManager::setup(ofVec2f _position,float _width,float _height){
    position.set(_position);
    
    
    float l=_width;
    float h=_height;
    
    maxspeed=15;//;l/5;
    
    ofVec3f pos = ofVec3f(-l,position.y);
    float dl=ofGetWidth()/l+1;
    for(int i=0;i<dl;i++){
        CarousselContainer c;
        c.setBoundingBox(pos, ofVec2f(l,h));
        c.id=i;
        containers.push_back(c);
        pos.x+=l;
    }
    
    
}

void CarousselManager::update(){
    if(bIsMoving){
        move();
    }
    
    for(int i=0;i<containers.size();i++){
        containers[i].update();
    }
    
}

void CarousselManager::draw(){
    // ofDrawLine(0,position.y, ofGetWidth(), position.y);
    for(int i=0;i<containers.size();i++){
        containers[i].draw();
    }
    
}


void CarousselManager::move(){
    
    for(int i=0;i<containers.size();i++){
        ofVec2f p=containers[i].getPosition();
        ofVec2f target=containers[i].getTarget();
        ofVec3f dist=target-p;
        ofVec3f speed=dist;
        speed.limit(maxspeed);
        p+=speed;
        
        if(dist.length()<(maxspeed)+1){
            p.set(target);
            containers[i].bIsMoving=false;

        }
        
    
        
        containers[i].setPosition(p);
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



void CarousselManager::cicle(){
    if(!bIsMoving){
        for(int i=1;i<containers.size();i++){
            containers[i].setTarget(containers[i-1].getPosition());
        }
        ofVec2f p=containers[containers.size()-1].getPosition();
        ofVec2f d=ofVec2f(containers[containers.size()-1].getDimension().x,0);
        containers[0].setPosition(p+d);
        containers[0].setTarget(p);
        std::rotate(containers.begin(),containers.begin()+1,containers.end());
        startMoving();
    }
}

void CarousselManager::startMoving(){
     // if(id==14)cout<<"startMoving "<<buffer[0]<<endl;
    Letter * l=buffer[0];
    l->setIsOnScreen(true);
    buffer.erase(buffer.begin());
    containers[containers.size()-1].setLetterPointer(l);
    
    
    static CarousselEvent newEvent;
    newEvent.message = "START";
    newEvent.id=id;
    ofNotifyEvent(CarousselEvent::events, newEvent);
    
    bIsMoving=true;
    for(int i=1;i<containers.size();i++){
        containers[i].bIsMoving=true;
    }
}

void CarousselManager::stopMoving(){
    bIsMoving=false;
    // cout<<"System stopped"<<endl;
    
    
    static CarousselEvent newEvent;
    newEvent.message = "STOP";
    newEvent.id=id;
    ofNotifyEvent(CarousselEvent::events, newEvent);
    
    
    //check if we have some movement in buffer
    if(buffer.size()>0){
        //   cout<<id<<" "<<buffer.size()<<endl;
        cicle();
    }
    
}



void CarousselManager::setId(int _id){
    id=_id;
}


void CarousselManager::addMovement(Letter *_l){
    buffer.push_back(_l);
    cicle();
}



char CarousselManager::getLastElementChar(){
    return containers[0].getChar();
}


Letter* CarousselManager::getLastElementPointer(){
    return containers[0].getLetterPointer();
}
