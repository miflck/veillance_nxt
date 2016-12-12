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

    
    //float minspeed=2;
   //minspeed=ofRandom(3,7);
    
    
    
    
    float speed;
    containerHeight=STM->CCheight;
    float w=STM->CCwidth;
    int time=w/minspeed;//int(w/minspeed); ->smooth out

    int lines=floor(myheight/containerHeight);
   // cout<<"lines "<<lines<<endl;
    for(int i = 0; i < lines; i++){
        CarousselLineManager cm;
        
 
        
        
//        float p=ABS((myheight/2)-((i*containerHeight/2)));
        float p=ABS(((myheight/2)+(containerHeight/2))-(containerHeight+(i*containerHeight)));

       // cout<<i<<" "<<p<<endl;
        float dl= ofMap(p*(p/4),0,myheight/2*(myheight/2/4),0,20);
        
        
        
       // cout<<"dl "<<dl<<endl;

       /* float p=ABS((myheight)-((i*containerHeight)));
        float dl= ofMap(p*(p/4),0,myheight*(myheight/4),10,1);*/
       // containerWidth = roundf(w+dl / time) * time;

        
         containerWidth=w+dl;
        
        
        
        // s=v*t  s/v=t  v=s/t
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
   // position.y+=0.1;
    
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
            cms[e.lineId].deleteLastLetter();
           // cms[e.lineId].unregisterLetter(l);
            
           //if(l!=nullptr){
         
            auto it = std::find(STM->letters.begin(), STM->letters.end(), l);
            if (it != STM->letters.end()) {
                (*it)->setBRemove(true);
                //int i= it - STM->letters.begin();
               // cout<<"remove "<<(*it)->getData()<<" "<<STM->letters[i]->getData()<<endl;
              //  STM->letters[i]->setBRemove(true);
                //if(i>1 && STM->letters[i-1]!=nullptr)STM->letters[i-1]->setBRemove(true);
           // }
              }
            
            
        }
        
    }

    
    if(e.message=="BUFFER EMPTY"){
        if(e.id==cms.size()-1){
        addDataFromBuffer();
        }
        
        /*if(e.id==cms.size()-1){
         STM->registerStackManagerReady(this);
        }*/
    }
    
    
    if(e.message=="EXPLODE STOP"){
       // cout<<"explode from csm "<<stackId<<endl;
       // STM->reset();
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
        m.text=messagestring[0];
        messagestring.erase(messagestring.begin());
        STM->addWordFromManager(this, m);
    }
    
    
    
    

}




void CarousselStackManager::addMessage(message _m){
    mymessage=_m;
    mymessage.text.erase( std::remove(mymessage.text.begin(), mymessage.text.end(), '\r'), mymessage.text.end() );
    mymessage.text=ofToUpper(ofToString(mymessage.text));

    messagestring = ofSplitString(mymessage.text , " ");
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
    cout<<"unreg "<<l<<endl;
        for(auto cm:cms){
        cm.unregisterLetter(l);
    }
    
}


void CarousselStackManager::addMovement(Letter *l){
   cms[cms.size()-1].addMovement(l);
}

int CarousselStackManager::getStringsize(){
    return messagestring.size();
}
