//
//  StreamManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#include "StreamManager.hpp"


StreamManager* StreamManager::instance = 0;

StreamManager* StreamManager::getInstance() {
    if (!instance) {
        instance = new StreamManager();
    }
    return instance;
}


StreamManager::StreamManager(){
}


void StreamManager::initialize() {
    
    initialized=true;
    cout<<"init StreamManager"<<endl;
    
    font.load("FoundersGroteskMonoRegular.ttf", 10);
    bigfont.load("FoundersGroteskMonoRegular.ttf", 50);
    
    
    float minspeed=2;
    float speed;
    int h=20;
    int w=10;
    
    int lines=floor(ofGetHeight()/h);
    cout<<"lines"<<lines<<ofGetHeight()/h<<endl;
    for(int i = 0; i < lines; i++){
        CarousselManager cm;
        float p=ABS((ofGetHeight()/2)-((i*h)));
        float dl= ofMap(p*(p/4),0,ofGetHeight()/2*(ofGetHeight()/2/4),1,100); 
        float dW=w+dl;
        // s=v*t
        // s/v=t
        //v=s/t
        float time=w/minspeed;
        float dv=dW/time;
        float speed=dv;//(w/minspeed)*dW;
        float r=ofRandom(0,50);
        cm.setup(ofVec2f(0,(i*h)),dW,h);
        cm.maxspeed=speed;//minspeed*dl;
        cm.setId(i);
        cms.push_back(cm);
    }
    ofAddListener(CarousselEvent::events, this, &StreamManager::carousselEvent);

}




void StreamManager::update(){
    if(bUpdate){
        for(int i=0;i<cms.size();i++){
            cms[i].update();
        }
    }
}

void StreamManager::draw(){
    if(bDraw){
        for(int i=0;i<cms.size();i++){
            cms[i].draw();
        }
    }

}





void StreamManager::carousselEvent(CarousselEvent &e){
    if(e.message=="STOP"){
        if(e.id>0){
            Letter *l=cms[e.id].getLastElementPointer();
            if(l!=nullptr){
                cms[e.id-1].addMovement(l);
            }
        }
    }
    
    
    if(e.message=="START"){
        if(e.id>0){
            //  cms[e.id-1].addMovement(cms[e.id].getLastElementChar());
        }
    }
}







bool StreamManager::isInitialized(){
    return initialized;
}


void StreamManager::addData(string _s){
    
    
    for (auto ss : _s){
        
        char c = ss;
         Letter * l =new Letter();
         l->setData(c);
         l->setFont(&font);
         addLetter(l);
        cms[cms.size()-1].addMovement(letters[letters.size()-1]);
    }
    cout<<"letters Size "<<letters.size()<<endl;
}


void StreamManager::addLetter(Letter *  _l){
    letters.push_back(_l);
}


/*
void StreamManager::addWord(string _s){
    Word w;
    w.setup(words.size());
    w.setData(_s);
    words.push_back(w);
}

*/