//
//  CarousselStackManager.cpp
//  Veillance
//
//  Created by Flückiger Michael on 30.11.16.
//
//

#include "CarousselStackManager.hpp"
CarousselStackManager::CarousselStackManager(){
}

void CarousselStackManager::setup(ofVec2f _position,float _mywidth, float _myheight){
  
    position.set(_position);
    
    
    mywidth=_mywidth;
    myheight=_myheight;
    
    
    
 
    // CAROUSSEL
    //These are the animationcontrollers of the background. Each one controlls a Line
    
    //float minspeed=2;
    float speed;
    int containerHeight=20;
    int w=10;
    
    int lines=floor(myheight/containerHeight);
    cout<<"lines "<<lines<<endl;
    for(int i = 0; i < lines; i++){
        CarousselLineManager cm;
        float p=ABS((myheight/2)-((i*containerHeight)));
        float dl= ofMap(p*(p/4),0,myheight/2*(myheight/2/4),1,100);
         containerWidth=w+dl;
        // s=v*t  s/v=t  v=s/t
        float time=w/minspeed;
        float dv=containerWidth/time;
        float speed=dv;
        float r=ofRandom(0,50);
        cm.setup(ofVec2f(position.x-mywidth,position.y+(i*containerHeight)),mywidth,ofGetHeight(),containerWidth,containerHeight);
        cm.maxspeed=speed;
        cm.setId(i);
        cms.push_back(cm);
    }

    ofAddListener(CarousselEvent::events, this, &CarousselStackManager::carousselEvent);
    
}

void CarousselStackManager::update(){
    
    // UPDATE CAROUSSEL
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



// CAROUSSEL STUFF -> ANIMATION
void CarousselStackManager::carousselEvent(CarousselEvent &e){
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
