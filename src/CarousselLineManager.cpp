//
//  CarousselManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#include "CarousselLineManager.hpp"
#include "SceneManager.hpp"


CarousselLineManager::CarousselLineManager(){
    
}


CarousselLineManager::~CarousselLineManager(){
    
    for (int i =0; i< containers.size();i++)
    {
        delete (containers[i]);
    }
    containers.clear();
    lastTime=0;
    
}

void CarousselLineManager::setup(int _numlines, int _stackId, int _lineId, ofVec2f _position,float _mywidth, float _myheight, float _width,float _height){
    
    
    
    numlines=_numlines;
    stackId=_stackId;
    lineId = _lineId;
    id=(stackId+1)*lineId;
    
    position.set(_position);
    mywidth=_mywidth;
    myheight=_myheight;
    
    letterWidth=_width;
    letterHeight=_height;
    
    maxspeed=300.f;//;l/5;
    
    ofVec3f pos = ofVec3f(-letterWidth,position.y);
    float dl=mywidth/letterWidth+1;
    
    for(int i=0;i<dl;i++){
        CarousselContainer *c =new CarousselContainer();
        c->setBoundingBox(pos, ofVec2f(letterWidth,letterHeight));
        targetpositions.push_back(pos);
        c->id=i;
        containers.push_back(c);
        pos.x+=letterWidth;
    }
    
    
}

void CarousselLineManager::unregisterLetter(Letter *_l){
    for(int i=0;i<containers.size();i++){
        if (_l==containers[i]->getLetterPointer()){
            containers[i]->unregisterLetter();
            break;
        }
    }
    
}


void CarousselLineManager::update(){
    now=ofGetElapsedTimeMicros();
    deltaTime=now-lastTime;
    elapsedTime=now-starttime;
    
    
    if(bIsMoving){
        move();
    }
    
    for(int i=0;i<containers.size();i++){
        containers[i]->update();
    }
    lastTime=now;
}

void CarousselLineManager::draw(){
    
    
    
    
    
    
    
    //if(bDebugDraw){
    /* for(int i=0;i<containers.size();i++){
     containers[i].draw();
     }*/
    //}
}


void CarousselLineManager::move(){
    
    if(!bIsExploding){
        for(int i=0;i<containers.size();i++){
            ofVec2f p=containers[i]->getPosition();
            p.x-= deltaTime*maxspeed*speedfactor;
            //p.x-= deltaTime*maxspeed;

            containers[i]->setPosition(p);
        }
        
        if(elapsedTime*speedfactor+(8000*speedfactor)>time){
           // if(elapsedTime>time){
               //cout<<elapsedTime<<" "<<time<<" "<<time-(elapsedTime)<<" "<<deltaTime<<endl;

           // cout<<elapsedTime*speedfactor<<" "<<time<<" "<<time-(elapsedTime*speedfactor+(10000*speedfactor))<<" "<<deltaTime<<endl;

        //    if(elapsedTime*speedfactor>time){

            for(int i=0;i<containers.size();i++){
                containers[i]->setPosition(containers[i]->getTarget());
                containers[i]->bIsMoving=false;
            }
            stopMoving();
        }
    }
        
        
    if(bIsExploding){
        for(int i=0;i<containers.size();i++){
            ofVec2f p=containers[i]->getPosition();
            ofVec2f target=containers[i]->getTarget();
            ofVec2f dist=target-p;
            ofVec2f speed=dist;
            explosionspeed*=damping;
            speed.limit(explosionspeed);
            p+=speed;
            containers[i]->setPosition(p);

            
            if(explosionspeed<0.1){
                p.set(target);
                containers[i]->bIsMoving=false;
            }
            
            
            //check if finished;
             bool move=false;
             for(int i=0;i<containers.size();i++){
             if(containers[i]->bIsMoving){
             move=true;
             break;
             }
             }
             if(!move){
            stopMoving();
             }
            
            
            
            
            
        }
        
      
        
        
        
    }
    
    
   
    
}



void CarousselLineManager::cicle(){
    if(!bIsMoving){
        for(int i=1;i<containers.size();i++){
            
            
            // containers[i]->setTarget(containers[i-1]->getPosition());
            containers[i]->setTarget(targetpositions[i-1]);
            
            
            
        }
        // ofVec2f p=containers[containers.size()-1]->getPosition();
        ofVec2f p=targetpositions[targetpositions.size()-1];
        
        ofVec2f d=ofVec2f(containers[containers.size()-1]->getDimension().x,0);
        containers[0]->setPosition(p+d);
        containers[0]->setTarget(p);
        std::rotate(containers.begin(),containers.begin()+1,containers.end());
        startMoving();
    }
}

void CarousselLineManager::startMoving(){
    Letter * l=buffer[0];
    l->setIsOnScreen(true);
    buffer.erase(buffer.begin());
    containers[containers.size()-1]->setLetterPointer(l);
    
    
    starttime=ofGetElapsedTimeMicros();
    
    
    // if first line
    if(lineId==numlines-1){
        // cout<<"push"
        
        STM->letters.push_back(l);
        //        STM->letters[l]=l;
        
        STM->lettermap.erase(l);
        //delete l;
        
        /*
         auto it = std::find(STM->letterbuffer.begin(), STM->letterbuffer.end(), l);
         if (it != STM->letterbuffer.end()) {
         STM->letterbuffer.erase(it);
         // int i= it - STM->letters.begin();
         // if(i>1 && STM->letters[i-1]!=nullptr)STM->letters[i-1]->setBRemove(true);
         }*/
        
        
    }
    
    
    
    
    static CarousselEvent newEvent;
    newEvent.message = "START";
    newEvent.id=id;
    newEvent.stackId=stackId;
    newEvent.lineId=lineId;
    ofNotifyEvent(CarousselEvent::events, newEvent);
    
    bIsMoving=true;
    for(int i=1;i<containers.size();i++){
        containers[i]->bIsMoving=true;
    }
}

void CarousselLineManager::stopMoving(){
    if(!bIsExploding){
        bIsMoving=false;
        static CarousselEvent newEvent;
        newEvent.message = "STOP";
        newEvent.id=id;
        newEvent.stackId=stackId;
        newEvent.lineId=lineId;
        ofNotifyEvent(CarousselEvent::events, newEvent);
        checkBuffer();
    }else{
        bIsMoving=false;
        
        bStoppedExploding=true;
        static CarousselEvent newEvent;
        newEvent.message = "EXPLODE STOP";
        newEvent.id=id;
        newEvent.stackId=stackId;
        newEvent.lineId=lineId;
        ofNotifyEvent(CarousselEvent::events, newEvent);
    }
}


void CarousselLineManager::checkBuffer(){
    //check if we have some movement in buffer
    if(!bIsMoving){
        if(buffer.size()>0){
            cicle();
        }else{
            static CarousselEvent newEvent;
            newEvent.message = "BUFFER EMPTY";
            newEvent.id=id;
            newEvent.stackId=stackId;
            newEvent.lineId=lineId;
            ofNotifyEvent(CarousselEvent::events, newEvent);
            
        }
    }
    
    
    
}




void CarousselLineManager::setPosition(ofVec2f _p){
    position.set(_p);
    
    /*ofVec3f pos = ofVec3f(-letterWidth,position.y);
     for(int i=0;i<containers.size();i++){
     pos.set(containers[i].getPosition());
     float diff=pos.y-_p.y;
     
     
     pos.y=_p.y;
     containers[i].setPosition(pos);
     
     pos.set(containers[i].getTarget());
     pos.y+=diff;
     containers[i].setTarget(pos);
     
     
     }*/
}


void CarousselLineManager::setId(int _id){
    id=_id; // deprecated
    lineId=_id;
}

void CarousselLineManager::setStackId(int _id){
    stackId=_id; // deprecated
    
}


void CarousselLineManager::addMovement(Letter *_l){
    buffer.push_back(_l);
    // cout<<buffer.size()<<endl;
    cicle();
}



char CarousselLineManager::getLastElementChar(){
    return containers[0]->getChar();
}


Letter* CarousselLineManager::getLastElementPointer(){
    return containers[0]->getLetterPointer();
}

void CarousselLineManager::deleteLastLetter(){
    containers[0]->setLetterPointer(nullptr);
}


void CarousselLineManager::setDebugDraw(bool _d){
    bDebugDraw=_d;
};

void CarousselLineManager::explode(){
    bIsExploding=true;
    bIsMoving=true;
    
    explosionspeed=ofRandom(10,15);
    
    for(int i=1;i<containers.size();i++){
        containers[i]->explode();
        ofVec2f p=containers[i]->getPosition();
        ofVec2f middle=parentposition+ofVec2f(mywidth/2,myheight/2);//+ofVec2f(mywidth/2,myheight/2);
        ofVec2f newTarget=p-middle;
        newTarget*=100;
        newTarget.rotate(ofRandom(-30,30));
        
        //containers[i]->setTarget(ofVec3f(ofRandom(-mywidth,2*mywidth),ofRandom(-1000,2000),ofRandom(-1000,1000)));
        // containers[i]->setTarget(ofVec3f(mywidth/2,myheight/2,0));
        
        containers[i]->setTarget(p+newTarget);
        
       // maxspeed=ofRandom(10,15);
        
        
        containers[i]->bIsMoving=true;
    }
    
}

