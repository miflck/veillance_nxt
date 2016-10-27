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
    float angleY=ofRandom(-80,-70);
   // angle=-45;
    t.rotate(angleY, ofVec3f(0,1,0));
     float angleZ=ofRandom(-90);
    t.rotate(angleZ, ofVec3f(0,0,1));
    target.set(t);
    
    startposition.set(ofRandom(ofGetWidth()/2-200,ofGetWidth()/2+200),ofGetHeight()/2,0);
    
    //startposition.set(ofGetWidth()/2,ofGetHeight()/2,0);

    position.set(startposition);
   // node.rotate(angle, ofVec3f(0,1,0));
    //node.roll(ofDegToRad(angle));
    //node.pan(ofDegToRad(angle));
    node.lookAt(target);
    
   // node.rotate(angleY, 0, 1, 0); // the rotation happens on the y axis
   // node.rotate(angleZ, 0, 0, 1); // the rotation happens on the y axis

    geometry.rotate(angleY, 0, 1, 0); // the rotation happens on the y axis
    geometry.rotate(angleZ, 0, 0, 1); // the rotation happens on the y axis

    maxspeed=ofRandom(0.5,1);

   // plane.set(100, 100);   ///dimensions for width and height in pixels
   // plane.setPosition(startposition); /// position in x y z

    maxdistance=2000;
    setIsAlive(true);
    
    rollangle=0;
    panangle=0;
    tiltangle=0;
    
    
    
    rollspeed=ofRandom(0.01,0.1);
    panspeed=ofRandom(0.01,0.1);
    tiltspeed=ofRandom(0.01,0.1);

    
}

void MovingWords::update(){
    move();
  //node.pan(ofDegToRad(-2));
  //  geometry.rotate(dir, 0, 1, 0); // the rotation happens on the y axis
    //geometry.roll(ofDegToRad(angle));
    //geometry.pan(ofDegToRad(angle));

    //angle+=ofRandom(0.5);
    
    rollangle+=rollspeed;
    panangle+=panspeed;
    tiltangle+=tiltspeed;
    
    geometry.setPosition(position);
    node.setPosition(position);
    node.lookAt(target);
    node.pan(180+panangle);
    node.roll(rollangle);
    node.tilt(tiltangle);
    
    
    if(position.length()>maxdistance){
        setIsAlive(false);
    }
    
    

}

void MovingWords::draw(){
    
    ofPushMatrix();
   // ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofSetColor(0,0,255,100);
    //ofDrawLine(startposition, target);
    ofNoFill();
  // geometry.draw();

    
    ofSetColor(255,0,0);


    
     //  node.draw();
    ofSetColor(0,255,0);

    
    //node.pan(PI);
    
    ofPushMatrix();
    ofTranslate(position);
   // font->drawString(data,0,0);

    
    float angle;
    ofVec3f axis;//(0,0,1.0f);
    
    ofQuaternion q;
    q=node.getGlobalOrientation();
    q.getRotate(angle, axis);

    ofPushMatrix();
    ofSetColor(0,191,255);

    ofRotate(angle, axis.x, axis.y, axis.z); // rotate with quaternion
    //name = ofUTF8::toUpper(name);
     font->drawString(data,0,0);
    ofPopMatrix();

   // float angle;
   // ofVec3f axis;//(0,0,1.0f);
    //q=geometry.getOrientationQuat();

    //q.getRotate(angle, axis);
    //ofRotate(angle, axis.x, axis.y, axis.z); // rotate with quaternion
    ofSetColor(0,0,255);

    ofNoFill();
    //ofDrawBox(0, 0, 0, 50); // OF 0.74: ofBox(0, 0, 0, 220);
    //ofDrawAxis(100);
    
    //node.rotate(q);
   // plane.drawWireframe();

   // font->drawString(data,0,0);
    ofPopMatrix();
    ofPopMatrix();
 


   // ofDrawBox(position.x,position.y,position.z,20,20,20);
}



void MovingWords::setData(string _data){
    data=ofToUpper(_data);
}


string MovingWords::getData(){
    return data;
}

void MovingWords::setFont(ofTrueTypeFont *f){
    font=f;
}

void MovingWords::setStartPosition(ofVec3f _p){
    startposition.set(_p);
    position.set(_p);
    node.setGlobalPosition(position);
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

  //  cout<<startposition<<endl;
}

void MovingWords::stopMoving(){
    bIsMoving=false;
}

void MovingWords::setIsAlive(bool _b){
    bIsAlive=_b;

}

bool MovingWords::checkIsAlive(){
    return bIsAlive;
}



