//
//  CarousselStackManager.cpp
//  Veillance
//
//  Created by Flückiger Michael on 30.11.16.
//
//

#include "CarousselStackManager.hpp"
#include "SceneManager.hpp"
#include "SoundManager.hpp"


#include "stdio.h"
#include "assert.h"

CarousselStackManager::CarousselStackManager(){
}


CarousselStackManager::~CarousselStackManager(){
    ofRemoveListener(CarousselEvent::events, this, &CarousselStackManager::carousselEvent);

    
    
    for (int i =0; i< cms.size();i++)
    {
        delete (cms[i]);
    }
    cms.clear();
    
    
}


void CarousselStackManager::setup(int _id, ofVec2f _position,float _mywidth, float _myheight){
  
    stackId=_id;
    position.set(_position);
    
    
    mywidth=_mywidth;
    myheight=_myheight;
    
    bIsExploding=false;
    
    float speed;
    containerHeight=CCheight;
    float w=CCwidth;
   // float time=int(ofRandom(112500,375000));
    float time=int(ofRandom(222500,375000));

    //float time=int(100000);

    
    int lines=floor(myheight/containerHeight);
    for(int i = 0; i < lines; i++){
        CarousselLineManager * cm=new CarousselLineManager();
        cm->parentposition=ofVec2f(position);
        float p=ABS(((myheight/2)+(containerHeight/2))-(containerHeight+(i*containerHeight)));
      
        double dl= ofMap(p*(p/4),0,myheight/2*(myheight/2/4),0,30);
        if(lines<3)dl=i*10+2;
        
        containerWidth=w+dl;
        float dv=containerWidth/time;
        cout<<"dv "<<dv<<endl;
        double speed=dv;
        cm->setup(lines,stackId,i,ofVec2f(position.x,position.y+(i*containerHeight)),mywidth,myheight,containerWidth,containerHeight);
        cm->time=time;
        cm->maxspeed=speed;
        cm->setId(i);
        cms.push_back(cm);

    }
    ofAddListener(CarousselEvent::events, this, &CarousselStackManager::carousselEvent);
    cout<<"Setup Stack Manager "<<stackId<<" "<<cms.size()<<endl;
    messagestring.clear();
    
    
    backgroundSound=SoundM->addBackgroundSound();

    
    
}

void CarousselStackManager::update(){
    int now=ofGetElapsedTimeMillis();

    if(bIsCountingDown && now>lifetime){
        stopCountDown();
    }
    
    
    bool ismoving=false;
    
    for(int i=0;i<cms.size();i++){
        cms[i]->update();
        if(cms[i]->bIsMoving)ismoving=true;
    }


    if(backgroundSound!=nullptr){
        if(ismoving){
            backgroundSound->setNumWords(ofMap(getStringsize(),0,200,1,100,true));
        }else{
            backgroundSound->setNumWords(0);
        }
    }
}

void CarousselStackManager::draw(){
    for(auto cm:cms){
        cm->draw();
    }
   
}

void CarousselStackManager::setId(int _id){
    id=_id;
}
void CarousselStackManager::setStackId(int _id){
    stackId=_id;
}


// CAROUSSEL STUFF -> ANIMATION
void CarousselStackManager::carousselEvent(CarousselEvent &e){
    
    if(e.stackId != stackId) return;
   
    if(e.message=="STOP" &&!bIsExploding){
        
        if(e.lineId>0 ){
            Letter *l=cms[e.lineId]->getLastElementPointer();
            if(l!=nullptr){
                cms[e.lineId-1]->addMovement(l);
            }
        }
        if(e.lineId==0){
            Letter *l=cms[e.lineId]->getLastElementPointer();
            cms[e.lineId]->deleteLastLetter();
            auto it = std::find(STM->letters.begin(), STM->letters.end(), l);
            if (it != STM->letters.end()) {
                (*it)->setBRemove(true);
        }
        }
    }
    
    if(e.message=="STOP" && bIsExploding){
        startCountdown();
        if(e.lineId>0 ){
            Letter *l=cms[e.lineId]->getLastElementPointer();
            if(l!=nullptr){
                cms[e.lineId-1]->addMovement(l);
            }
        }
    }

    
    if(e.message=="BUFFER EMPTY" && !bIsExploding){
        if(e.id==cms.size()-1){
        addDataFromBuffer();
        }
    }
    
    
    if(e.message=="EXPLODE STOP"){

    }
    
    
 }


void CarousselStackManager::addDataFromBuffer(){
    //cout<<mymessage.text.size()<<endl;

    if(messagestring.size()==0){
        STM->registerStackManagerReady(this);
    }else{
        
       /* message m=mymessage;
        // First, find the index for the first space:
        auto first_space = mymessage.text.find(' ');
        // The part of the string we want to keep
        // starts at the index after the space:
        auto second_word = first_space + 1;
        string word = mymessage.text.substr(0, first_space);
        mymessage.text= mymessage.text.substr(second_word);
        m.text=word;
        m.text+=" ";
       // cout<<"word "<<m.text<<endl;
        
        */
        message m=mymessage;
        
        m.text= messagestring[0];
        

        
        messagestring.erase(messagestring.begin());
        STM->addWordFromManager(this, m);
    }
    
    
    
    

}




void CarousselStackManager::addMessage(message _m){
    mymessage=_m;
    mymessage.text.erase( std::remove(mymessage.text.begin(), mymessage.text.end(), '\r'), mymessage.text.end() );
    
    std::string utf8_6_toUpper = ofx::UTF8::toUpper(mymessage.text);
    // cout<<mymessage.text<<" "<<utf8_6_toUpper<<endl;
    messagestring.clear();
   // messagestring = ofSplitString(mymessage.text , " ");
    messagestring = ofSplitString(utf8_6_toUpper, " ");

    addDataFromBuffer();
}



void CarousselStackManager::explode(){
    bIsExploding=true;
    for(int i=0;i<cms.size();i++){
        if(!cms[i]->bIsMoving){
            cms[i]->explode();
        }
       // cms[i].explode();
    }

}


void CarousselStackManager::unregisterLetter(Letter *l)
{
    cout<<"unreg "<<l<<endl;
        for(auto cm:cms){
        cm->unregisterLetter(l);
    }
    
}


void CarousselStackManager::addMovement(Letter *l){
   cms[cms.size()-1]->addMovement(l);
}

int CarousselStackManager::getStringsize(){
    return messagestring.size();
}

ofVec2f CarousselStackManager::getPosition(){
    return position;
}

ofColor CarousselStackManager::getBackgroundColor(){
    
  ofColor c=cms[cms.size()-1]->containers[cms[cms.size()-1]->containers.size()-1]->getBackgroundColor();
    return c;
}

void CarousselStackManager::startCountdown(){
    bIsCountingDown=true;
    lifespan=int(ofRandom(1000,2000));
    lifetime=ofGetElapsedTimeMillis()+lifespan;
}

void CarousselStackManager::stopCountDown(){
    
     bIsCountingDown=false;
    for(int i=0;i<cms.size();i++){
        cms[i]->explode();
    }


}





