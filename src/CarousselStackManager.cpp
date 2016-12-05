//
//  CarousselStackManager.cpp
//  Veillance
//
//  Created by Flückiger Michael on 30.11.16.
//
//

#include "CarousselStackManager.hpp"
#include "SceneManager.hpp"

CarousselStackManager::CarousselStackManager(){
}

void CarousselStackManager::setup(int _id, ofVec2f _position,float _mywidth, float _myheight){
  
    stackId=_id;
    position.set(_position);
    
    
    mywidth=_mywidth;
    myheight=_myheight;
    
    bIsExploding=false;

    
 
    // CAROUSSEL
    //These are the animationcontrollers of the background. Each one controlls a Line
    
    //float minspeed=2;
    minspeed=ofRandom(2,6);
   // cout<<"min "<<minspeed<<"min2 "<<minspeed2<< " id "<<stackId<<endl;
    float speed;
     containerHeight=20;
    float w=10;
    
    int lines=floor(myheight/containerHeight);
   // cout<<"lines "<<lines<<endl;
    for(int i = 0; i < lines; i++){
        CarousselLineManager cm;
        
 
        
        
//        float p=ABS((myheight/2)-((i*containerHeight/2)));
        float p=ABS(((myheight/2)+(containerHeight/2))-(containerHeight+(i*containerHeight)));

       // cout<<i<<" "<<p<<endl;
        float dl= ofMap(p*(p/4),0,myheight/2*(myheight/2/4),1,20);
       // cout<<"dl "<<dl<<endl;

       /* float p=ABS((myheight)-((i*containerHeight)));
        float dl= ofMap(p*(p/4),0,myheight*(myheight/4),10,1);*/
         containerWidth=w+dl;
        // s=v*t  s/v=t  v=s/t
        float time=w/minspeed;
        float dv=containerWidth/time;
        float speed=dv;
        //float r=ofRandom(0,50);
        cm.setup(lines,stackId,i,ofVec2f(position.x-mywidth,position.y+(i*containerHeight)),mywidth,ofGetHeight(),containerWidth,containerHeight);
        cm.maxspeed=speed;
        cm.setId(i);
        cms.push_back(cm);

    }
   // cout<<"cms size "<<cms.size()<<endl;
    ofAddListener(CarousselEvent::events, this, &CarousselStackManager::carousselEvent);
    
}

void CarousselStackManager::update(){
    // UPDATE CAROUSSEL
    position.y-=1;
    
    for(int i=0;i<cms.size();i++){
        cms[i].setPosition(ofVec2f(position.x-mywidth,position.y+(i*containerHeight)));
    }
    
    for(int i=0;i<cms.size();i++){
        cms[i].update();
    }
}

void CarousselStackManager::draw(){

    for(auto cm:cms){
        cm.draw();
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
    if(e.message=="STOP"){
        if(e.lineId>0){
            Letter *l=cms[e.lineId].getLastElementPointer();
            if(l!=nullptr){
                cms[e.lineId-1].addMovement(l);
            }
        }
        
        if(e.lineId==0){
            
            //remove Letter
           //cms[e.id].getLastElementPointer()->setBRemove(true);
            Letter *l=cms[e.lineId].getLastElementPointer();
            cms[e.lineId].unregisterLetter(l);
            
            
            auto it = std::find(STM->letters.begin(), STM->letters.end(), l);
            if (it != STM->letters.end()) {
                (*it)->setBRemove(true);
               // int i= it - STM->letters.begin();
               // if(i>1 && STM->letters[i-1]!=nullptr)STM->letters[i-1]->setBRemove(true);
            }
            
            
            
        }
        
    }

    
    if(e.message=="BUFFER EMPTY"){
        if(e.id==cms.size()-1){
        addDataFromBuffer();
        }
        
     /*   if(e.id==cms.size()-1){
         STM->registerStackManagerReady(this);
        }*/
    }
    
   /* if(e.message=="STOP"){
        if(e.id>0){
            Letter *l=cms[e.id].getLastElementPointer();
            if(l!=nullptr){
                cms[e.id-1].addMovement(l);
            }
        }
        
        if(e.id==0){
            Letter *l=cms[e.id].getLastElementPointer();
            auto it = std::find(letters.begin(), letters.end(), l);
            if (it != letters.end()) {
                int i= it - letters.begin();
                if(i>0)letters[i-1]->setBRemove(true);
            }
        }
        
    }
    
    
    
    if(e.message=="EXPLODE"){
        reset();
    }
    
    
    
    if(e.message=="START"){
        if(e.id>0){
            //cms[e.id-1].addMovement(cms[e.id].getLastElementChar());
        }
    }
    
    
    if(e.message=="BUFFER EMPTY"){
        if(e.id==cms.size()-1){
            bIsReadyForData=true;
            
        }
    }*/
}


void CarousselStackManager::addDataFromBuffer(){
    //cout<<mymessage.text.size()<<endl;

    if(mymessage.text.size()==0){
        STM->registerStackManagerReady(this);
    }else{
        
        message m=mymessage;
        
        
        // First, find the index for the first space:
        auto first_space = mymessage.text.find(' ');
        
        // The part of the string we want to keep
        // starts at the index after the space:
        auto second_word = first_space + 1;
        
        
        string word = mymessage.text.substr(0, first_space);

        mymessage.text= mymessage.text.substr(second_word);
        
        
        //std::string::size_type word = 0;
               //mymessage.text= mymessage.text.substr( mymessage.text.find_first_of(" \t")+1);

        
        m.text=word;
        m.text+=" ";
       // cout<<"word "<<m.text<<endl;
        
        STM->addDataFromManager(this, m);
    
    
    }
    
    
    
    

}




void CarousselStackManager::addMessage(message _m){
    mymessage=_m;
            addDataFromBuffer();
}



void CarousselStackManager::explode(){
    bIsExploding=true;
    for(int i=0;i<cms.size();i++){
        cms[i].explode();
    }

}


void CarousselStackManager::unregisterLetter(Letter *l)
{
        for(auto cm:cms){
        cm.unregisterLetter(l);
    }
    
}


void CarousselStackManager::addMovement(Letter *l){
   cms[cms.size()-1].addMovement(l);
}

