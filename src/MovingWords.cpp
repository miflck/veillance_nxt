//
//  MovingWords.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//
float angle=0;

#include "MovingWords.hpp"
#include "SceneManager.hpp"
MovingWords::MovingWords(){
}


void MovingWords::setup(){
    
    bIsOnScreen=true;
    setIsAlive(true);

    ofVec3f t=ofVec3f(1,0,0);
    t.set(ofGetWidth()/4+ofRandom(-200,200),ofGetHeight()/2+ofRandom(-200,200),2000);
    /*
    t*=ofRandom(3000,5000);
    float angleY=ofRandom(-80,-70);
    t.rotate(angleY, ofVec3f(0,1,0));
    float angleZ=ofRandom(-90);
    t.rotate(angleZ, ofVec3f(0,0,1));
    */
    
    target.set(t);
    startposition.set(ofRandom(ofGetWidth()/2-200,ofGetWidth()/2+200),ofGetHeight()/2,0);
    position.set(startposition);
    
    scalefact=0.2;
    node.setScale(scalefact);
    
    
    maxspeed=ofRandom(0.25,3);
    
    // plane.set(100, 100);   ///dimensions for width and height in pixels
    // plane.setPosition(startposition); /// position in x y z
    
    rollangle=0;
    panangle=0;
    tiltangle=0;
    
    
    rollspeed=ofRandom(0.01,0.2);
    panspeed=ofRandom(0.01,0.2);
    tiltspeed=ofRandom(0.01,0.2);
    
    
    myColor=ofColor(0,191,255);
    lookat.set(position+ofVec3f(0,0,1));
    
}

void MovingWords::update(){
    
    
    int now=ofGetElapsedTimeMillis();
    if(bIsLifetimeRunning && now>lifetime){
        stopLifeTimer();
    }
    
    
    move();
    node.setPosition(position);
    
    //do the rotation
    if(spacingFact<1.6 && bIsRotating){
        rollangle+=rollspeed;
        panangle+=panspeed;
        tiltangle+=tiltspeed;
        
        lookat.set(position+ofVec3f(0,0,1));
        
        node.lookAt(lookat);
        node.pan(180+panangle);
        node.roll(rollangle);
        node.tilt(tiltangle);
    }
}

void MovingWords::draw(){
    /*
    ofPushMatrix();
    ofSetColor(0,0,255,100);
    //ofDrawLine(startposition, target);
    ofNoFill();
    
    ofSetColor(255,0,0);
    //  node.draw();
    ofSetColor(0,255,0);
    
    ofPushMatrix();
    ofTranslate(position);
    
    
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
    
    */
    
    // ofDrawBox(position.x,position.y,position.z,20,20,20);
}




void MovingWords::move(){
    if(bIsMoving){
        ofVec3f acc;
        ofVec3f p=position;
        ofVec3f t=target;
        ofVec3f dist=t-p;
        ofVec3f desired=t-p;
        desired.normalize();
        float d=dist.length();
        if(d < 500){
            float m = ofMap(d,0,500,0,maxspeed);
            desired*=m;
            
        }else{
            desired*=maxspeed;
        }
        
        ofVec3f steer=desired-velocity;
        steer.limit(0.09);
        acc+=steer;
        velocity+=acc;
        p+=velocity;
        
        if(d<1){
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
    startLifeTimer();
    bIsMoving=false;
    bIsRotating=false;
    STM->movingWordPositions.push_back(getDockPoint());
}


void MovingWords::setIsAlive(bool _b){
    bIsAlive=_b;
    
}

bool MovingWords::checkIsAlive(){
    return bIsAlive;
}


ofVec3f MovingWords::getDockPoint(){
    
    float angle;
    ofVec3f axis;//(0,0,1.0f);
    
    ofQuaternion q;
    q=node.getGlobalOrientation();
    q.getRotate(angle, axis);
    
    ofPushMatrix();
    ofSetColor(0,191,255);
    
    spacingFact=ofLerp(spacingFact,1.2,0.01);
    font->setLetterSpacing(spacingFact);
    boundingBox = font->getStringBoundingBox(data, 0, 0);
    ofVec3f p=boundingBox.getBottomRight();//position+boundingBox.getBottomRight();
    p=p*node.getGlobalTransformMatrix();
    
    return p;
}



ofVboMesh MovingWords::getUpdatedVboMesh(){
    scalefact=ofLerp(scalefact,1,0.001);
    node.setScale(scalefact);
    spacingFact=ofLerp(spacingFact,1.2,0.01);
    font->setLetterSpacing(spacingFact);
    vbom.clear();
    if(bIsOnScreen){//check if is on screen
        letterMesh = font->getStringMesh(data, 0, 0);
        vector<ofVec3f>& verts = letterMesh.getVertices();
        for(int j=0; j <  verts.size() ; j++){
            letterMesh.setVertex(j,verts[j]*node.getGlobalTransformMatrix());
            letterMesh.addColor(myColor);
        }
        vbom.append(letterMesh);
    }
    return vbom;
}


void MovingWords::setData(string _data){
    data=ofToUpper(_data);
    for(int i=0;i<data.size();i++){
        if(isVowel(data[i]))numvowels++;
    }
    numsyllables=countSyllables(data);
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
    float p=ABS((ofGetHeight()/2)-((position.y)));
    float dl= ofMap(p*(p/4),0,ofGetHeight()/2*(ofGetHeight()/2/4),1,10);
    spacingFact=dl;
    font->setLetterSpacing(spacingFact);
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

void MovingWords::setInitVelocity(ofVec3f _v){
    initvelocity.set(_v);
    velocity.set(_v);
}

// hooked off
void MovingWords::applyForce(ofVec3f _f){
    acceleration+=_f;
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


void MovingWords::setLifeTime(int _t){
    lifetime=_t;
}

void MovingWords::setLifeSpan(int _t){
    lifespan=_t;
}


int MovingWords::getLifeTime(){
    return lifetime;
    
}

void MovingWords::startLifeTimer(){
    lifetime=ofGetElapsedTimeMillis()+lifespan;
    bIsLifetimeRunning=true;
}

void MovingWords::stopLifeTimer(){
    userPointer->unregisterMovingWord(this);
    bIsLifetimeRunning=false;
    bIsAlive=false;
    STM->secondScreenbackgroundFbo.begin();
    STM->cam[1].begin();
    font->getFontTexture().bind();
    getUpdatedVboMesh().draw();
    font->getFontTexture().unbind();
    STM->cam[1].end();
    STM->secondScreenbackgroundFbo.end();
}

bool MovingWords:: isVowel(char c) {
    return std::string("AEIOU").find(c) != std::string::npos;
}

bool MovingWords:: isVowelForSyllables(char c) {
    return std::string("AEIOUY").find(c) != std::string::npos;
}


int MovingWords::getVowelcount(){
    return numvowels;
}


int MovingWords::getSyllablescount(){
    return numsyllables;
}


int MovingWords:: countSyllables(string _word)
{
    int numVowels = 0;
    bool lastWasVowel = false;
    
    for(auto wc:_word ){
        bool foundVowel = false;
        if(isVowelForSyllables(wc)&& lastWasVowel){
            foundVowel = true;
            lastWasVowel = true;
            continue;
        }else if(isVowelForSyllables(wc)&& !lastWasVowel){
            numVowels++;
            foundVowel = true;
            lastWasVowel = true;
            continue;
        }
        //if full cycle and no vowel found, set lastWasVowel to false;
        if (!foundVowel)
            lastWasVowel = false;
        
    }
    
    //remove es, it's _usually? silent
    if (_word.size() > 2 &&
        _word.substr(_word.size() - 2) == "es")
        numVowels--;
    // remove silent e
    else if (_word.size() > 1 &&
             _word.substr(_word.size() - 1) == "e")
        numVowels--;
    return numVowels;
}


void MovingWords::setUserPointer(User *_u){
    userPointer=_u;
}

User * MovingWords::getUserPointer(){
    return userPointer;
}

