//
//  WordManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#include "WordManager.hpp"
WordManager::WordManager(){
}


void WordManager::setup(){

}

void WordManager::update(){
  
    
    
}

void WordManager::draw(){
   
}


void WordManager::addWord(string _s){
    Word w;
    w.setup(words.size());
    w.setData(_s);
    words.push_back(w);
}




/*

void WordManager::setData(string _data){
    data=_data;
}


string WordManager::getData(){
    return data;
}

void WordManager::setFont(ofTrueTypeFont *f){
    font=f;
}

void WordManager::setPosition(ofVec3f _p){
    position.set(_p);
    node.setGlobalPosition(position);
}
ofVec3f WordManager::getPosition(){
    return position;
}

void WordManager::setVelocity(ofVec3f _v){
    velocity.set(_v);
}
ofVec3f WordManager::getVelocity(){
    return velocity;
}


void WordManager::setTarget(ofVec3f _t){
    target.set(_t);
}


ofVec3f WordManager::getTarget(){
    return target;
}


void WordManager::move(){
    if(bIsMoving){
        ofVec3f p=position;
        ofVec3f t=target;
        ofVec3f dist=t-p;
        ofVec3f speed=dist;
        speed.limit(maxspeed);
        p+=speed;
        
        if(dist.length()<(maxspeed)+1){
            p.set(target);
            stopMoving();
            
        }
        position.set(p);
    }
}


void WordManager::startMoving(){
    bIsMoving=true;
    
}

void WordManager::stopMoving(){
    bIsMoving=false;
}*/