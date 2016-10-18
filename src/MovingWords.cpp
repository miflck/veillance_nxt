//
//  MovingWords.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//
float angle=0;

#include "MovingWords.hpp"
MovingWords::MovingWords(){
}


void MovingWords::setup(){
    ofVec3f t=ofVec3f(1,0,0);
    t*=ofRandom(3000,5000);
    float angle=ofRandom(-80,-70);
   // angle=-45;
    t.rotate(angle, ofVec3f(0,1,0));
     angle=ofRandom(-90);
    t.rotate(angle, ofVec3f(0,0,1));
    target.set(t);
    startposition.set(ofRandom(ofGetWidth()/2-200,ofGetWidth()/2+200),ofGetHeight()/2,0);
    //startposition.set(ofGetWidth()/2,ofGetHeight()/2,0);

    position.set(startposition);
   // node.rotate(angle, ofVec3f(0,1,0));
    //node.roll(ofDegToRad(angle));
    //node.pan(ofDegToRad(angle));
    //node.lookAt(target);
    
    node.rotate(angle, 0, 1, 0); // the rotation happens on the y axis
    geometry.rotate(angle, 0, 1, 0); // the rotation happens on the y axis
    geometry.rotate(angle, 0, 0, 1); // the rotation happens on the y axis

    

    plane.set(100, 100);   ///dimensions for width and height in pixels
    plane.setPosition(startposition); /// position in x y z


}

void MovingWords::update(){
    move();
  //node.pan(ofDegToRad(-2));
  //  geometry.rotate(dir, 0, 1, 0); // the rotation happens on the y axis
    geometry.roll(ofDegToRad(angle));
    geometry.pan(ofDegToRad(angle));

    angle+=0.1;
    geometry.setPosition(position);
    node.setPosition(position);


}

void MovingWords::draw(){
    ofSetColor(0,0,255,100);
    ofDrawLine(startposition, target);
    ofNoFill();
  // geometry.draw();

    
    ofSetColor(0,0,255);


    
     //  node.draw();

    ofPushMatrix();
    ofTranslate(position);
   // font->drawString(data,0,0);

    ofQuaternion q;
    q=node.getGlobalOrientation();
    

    float angle;
    ofVec3f axis;//(0,0,1.0f);
    q=geometry.getOrientationQuat();

    q.getRotate(angle, axis);
    ofRotate(angle, axis.x, axis.y, axis.z); // rotate with quaternion
    
    ofNoFill();
    ofDrawBox(0, 0, 0, 50); // OF 0.74: ofBox(0, 0, 0, 220);
    ofDrawAxis(100);
    
    //node.rotate(q);
    plane.drawWireframe();

    font->drawString(data,0,0);
    ofPopMatrix();
 


   // ofDrawBox(position.x,position.y,position.z,20,20,20);
}



void MovingWords::setData(string _data){
    data=_data;
}


string MovingWords::getData(){
    return data;
}

void MovingWords::setFont(ofTrueTypeFont *f){
    font=f;
}

void MovingWords::setPosition(ofVec3f _p){
    position.set(_p);
    node.setGlobalPosition(position);
}
ofVec3f MovingWords::getPosition(){
    return position;
}

void MovingWords::setVelocity(ofVec3f _v){
    velocity.set(_v);
}
ofVec3f MovingWords::getVelocity(){
    return velocity;
}


void MovingWords::setTarget(ofVec3f _t){
    target.set(_t);
}


ofVec3f MovingWords::getTarget(){
    return target;
}


void MovingWords::move(){
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


void MovingWords::startMoving(){
    bIsMoving=true;

}

void MovingWords::stopMoving(){
    bIsMoving=false;
}
