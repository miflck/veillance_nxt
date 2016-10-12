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
    
    maxspeed=2;
    //maxspeed=int(l/10);
    
    ofVec3f pos = ofVec3f(-l,position.y);
    float dl=ceil(ofGetWidth()/l)+1;
    for(int i=0;i<dl;i++){
        CarousselContainer c;
        c.setBoundingBox(pos, ofVec2f(l,h));
        c.id=i;
        containers.push_back(c);
        pos.x+=l;
    }
    
    
}

void CarousselManager::update(){
    
    
    //  for(int i=0;i<containers.size();i++){
    
    //CarousselContainer *c =&containers[0];
    // c->setPosition(ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight())));
    
    //    move(ofVec2f(-containers[0].getDimension().x,0), &containers[0]);
    
    if(bIsMoving){
        move();
    }
    for(int i=containers.size();i>0;i--){
        ofVec2f p=containers[i-1].getPosition();
        //      move(p, &containers[i]);
    }
    
    
    //  ofVec2f p=containers[i].getPosition();
    //  p.x-=3;
    //  containers[i].setPosition(p);
    //  }
    
    
    
    
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


void CarousselManager::move(ofVec2f target, CarousselContainer *c){
    ofVec2f p=c->getPosition();
    ofVec3f dist=target-p;
    dist.limit(maxspeed);
    p+=dist;
    c->setPosition(p);
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
    if(id==14)cout<<"startMoving"<<endl;
    buffer.erase( buffer.begin() );
    
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
void CarousselManager::move(){
    
    for(int i=0;i<containers.size();i++){
        ofVec2f p=containers[i].getPosition();
        ofVec2f target=containers[i].getTarget();
        ofVec3f dist=target-p;
        dist.limit(maxspeed);
        p+=dist;
        containers[i].setPosition(p);
        if(p==target){
            containers[i].bIsMoving=false;
        }
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


void CarousselManager::setId(int _id){
    id=_id;
}

void CarousselManager::addMovement(char _c){
    buffer.push_back(_c);
    cicle();
}
