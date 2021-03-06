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
#include "SoundManager.hpp"


MovingWords::MovingWords(){
}


void MovingWords::setup(){
    
    bIsOnScreen=true;
    setIsAlive(true);
    
    //viewportwidth=STM->viewportwidth;
    
    
    float r=ofRandom(0,1);
    ofVec3f t;
    if(r>0.5){
        t=ofVec3f(1000,200,0);
    }else{
        t=ofVec3f(-500,200,0);
        
        
    }
    
    //t.set(ofGetWidth()/4+ofRandom(-200,200),ofGetHeight()/2+ofRandom(-200,200),5000);
    //t.set(ofGetWidth()/4+ofRandom(-200,200),ofGetHeight()/2+ofRandom(-200,200),5000);
    // t.set(ofGetWidth()*2,ofGetHeight()/2+ofRandom(-200,200),0);
    
    
    /*
     t*=ofRandom(3000,5000);
     float angleY=ofRandom(-80,-70);
     t.rotate(angleY, ofVec3f(0,1,0));
     float angleZ=ofRandom(-90);
     t.rotate(angleZ, ofVec3f(0,0,1));
     */
    
    target.set(t);
    startposition.set(ofRandom(ofGetWidth()/2-200,ofGetWidth()/2+200),ofGetHeight()/2,-1000);
    position.set(startposition);
    
    scalefact=0.2;
    node.setScale(scalefact);
    
    
    maxspeed=ofRandom(0.5,1.7);
  //  shrinkmaxspeed=ofMap(maxspeed,0.5,2,0.00003,0.002);
    
    //fade
   // shrinkmaxspeed=ofMap(maxspeed,0.5,2,0.06,0.15);
    shrinkmaxspeed=ofMap(maxspeed,0.5,2,0.08,0.2);


    
    
    
    maxscale=ofRandom(1,fgmaxScalefact);
    
    
    // plane.set(100, 100);   ///dimensions for width and height in pixels
    // plane.setPosition(startposition); /// position in x y z
    
    rollangle=0;
    panangle=0;
    tiltangle=0;
    
    
    rollspeed=ofRandom(0.1,0.2);
    panspeed=ofRandom(0.1,0.2);
    tiltspeed=ofRandom(0.1,0.2);
    
    
    myColor=ofColor(0,191,255);
    lookat.set(position+ofVec3f(0,0,1));
    foregroundSound=nullptr;
    
    // addSound();
    
    alphafact=200;
    
}



float MovingWords::shrink(float _in, float _acceleration){
    shrinkspeed+=_acceleration;
    if(shrinkspeed>shrinkmaxspeed)shrinkspeed=shrinkmaxspeed;
    _in -= shrinkspeed;
    if (_in<0) _in=0;
    return _in;
}


float MovingWords::easeIn (float t,float b , float c, float d) {
    return c*(t/=d)*t + b;
}
float MovingWords::easeOut(float t,float b , float c, float d) {
    return -c *(t/=d)*(t-2) + b;
}

void MovingWords::update(){
    
    
    int now=ofGetElapsedTimeMillis();
    if(bIsLifetimeRunning && now>lifetime){
        stopLifeTimer();
    }
    
    
    move();
    node.setPosition(position);
    
    
    
    
    if(bIsLeft){
        distanceToMidscreen=ABS(-viewportwidth/2-position.x);
        if(position.x>-viewportwidth){//-viewportwidth/3){
            if(slowpop){
            scalefact=ofLerp(scalefact,maxscale,0.0005);
            }else{
            scalefact=ofLerp(scalefact,maxscale,0.003);
            }
        }else{
            
            if(!bIsShrinking) {
                bIsShrinking=true;
                shrinkingstarttime=ofGetElapsedTimeMillis();
                beginningscalefact=scalefact;
                
            }
            alphafact=shrink(alphafact,7);//7
            myColor=ofColor(myColor,alphafact);
          //  scalefact=shrink(scalefact,0.00001);

            //scalefact=ofLerp(scalefact,0,0.002);
            //scalefact=ofLerp(shrink(scalefact,0.0001),0,0.2);


        }
    }
    if(!bIsLeft){
        distanceToMidscreen=ABS(viewportwidth+viewportwidth/2-position.x);
        
        if(position.x<2*viewportwidth){//+viewportwidth/3){
            if(slowpop){
                scalefact=ofLerp(scalefact,maxscale,0.0005);
            }else{
                scalefact=ofLerp(scalefact,maxscale,0.003);

            }
        }else{
            //  scalefact=ofLerp(scalefact,0,0.002);
            //scalefact=shrink(scalefact,0.00001);
            alphafact=shrink(alphafact,7);
            myColor=ofColor(myColor,alphafact);
            
           /* if(!bIsShrinking) {
                bIsShrinking=true;
                shrinkingstarttime=ofGetElapsedTimeMillis();
                beginningscalefact=scalefact;
            }
            scalefact=easeOut(ofGetElapsedTimeMillis()-shrinkingstarttime,beginningscalefact,maxscale,shrinkingduration);
*/
        }
    }
    
    
    
    //do the rotation
    if(spacingFact<1.6 && bIsRotating){
        rollangle+=(rollspeed*rollfact);
        
        
        panangle+=(panspeed*panfact);
        tiltangle+=(tiltspeed*tiltfact);
        
        lookat.set(position+ofVec3f(0,0,1));
        
        node.lookAt(lookat);
        node.pan(180+panangle);
        node.roll(rollangle);
        node.tilt(tiltangle);
    }
    
    
    
    if(foregroundSound!=nullptr){
        foregroundSound->setPosition(position);
        foregroundSound->setScalefact(scalefact);
        foregroundSound->setDistanceToMidScreen(distanceToMidscreen);
        
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
        ofVec3f t=waypoints[0];
        
        // ofVec3f t=target;
        ofVec3f dist=t-p;
        ofVec3f desired=t-p;
        desired.normalize();
        float d=dist.length();
        if(d < 50){
            if(waypoints.size()>0){
                waypoints.erase( waypoints.begin() );
            }
        }
        //  float m = ofMap(d,0,500,0,maxspeed*movingwordSpeedFact);
        
       //   desired*=m;
        
    // }else{
        desired*=maxspeed*movingwordSpeedFact;
        // }
        
        ofVec3f steer=desired-velocity;
        //steer.limit(0.09);
        steer.limit(0.09);

        acc+=steer;
        velocity+=acc;
        p+=velocity;
        
        if(d<4 && waypoints.size()==0){
                //p.set(target);
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
    
    // HACK we dont have clusters anymore. so stop everything...
    // stopLifeTimer();
    bIsMoving=false;
    //bIsRotating=false;
    // STM->movingWordPositions.push_back(getDockPoint());
    //if(bIsLeft) {STM->leftTheta+=0.005;}else{
    //STM->rightTheta+=0.005;
    // }
    
    if(foregroundSound!=nullptr){
        
        foregroundSound->setBRemove();
        foregroundSound=nullptr;
    }
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
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    
    
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
    
    ofPopStyle();
    return vbom;
    
}


void MovingWords::setData(string _data){
    data=ofToUpper(_data);
    for(int i=0;i<data.size();i++){
        if(isVowel(data[i])){
            numvowels++;
            vouwels+=data[i];
        }
    }
    numsyllables=countSyllables(data);
    
    
    addSound();
    
    
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
    
    
        ofVec3f v=target-position;
        v/=3;
       v+=position;
      
        //v+=position;
        float r=ofRandom(-100,ofGetHeight()/3);
        v.y=ofGetHeight()/2-r;
        waypoints.push_back(v);
        waypoints.push_back(target);

    
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
}

bool MovingWords:: isVowel(char c) {
    return std::string("AEIOUY").find(c) != std::string::npos;
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


void MovingWords::addSound(){
    // if(SoundM->foregrounds.size()<maxForegroundSound){
    foregroundSound = SoundM->addForegroundSound(numsyllables,vouwels,ofVec3f(0,0,0));
    // }
    //STM->addForegroundSound
    
}


