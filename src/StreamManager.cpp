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
    bigfont.load("FoundersGroteskMonoBold.ttf", 30);
    
    
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
        
        for(auto word:words){
           word->update();
        }
        
        for(auto movingWord:movingWords){
            movingWord->update();
          
        }

        for(auto letter:letters){
            letter->update();
        }
        
        
        // check if we want to remove the bullet
        for (int i=0;i<movingWords.size();i++){
            if(shouldRemoveMovingWord(movingWords[i])){
                delete (movingWords[i]);
                movingWords.erase(movingWords.begin()+i);
            }
        }        
    }
}

void StreamManager::draw(){
    if(bDraw){
      //  ofBackground(0); // this matters

        for(int i=0;i<cms.size();i++){
            cms[i].draw();
        }
        
        
      
        
        
        ofVboMesh m;
        for(auto letter:letters){
            ofVboMesh ms=letter->getUpdatedVboMesh();
            m.append(ms);
        }
        
        font.getFontTexture().bind();
        m.draw();
        font.getFontTexture().unbind();

        
        
        for(auto letter:letters){
           //letter->draw();
        }
        

        for(auto movingWord:movingWords){
            movingWord->draw();
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
    Word * w=new Word();
    w->setup(wordcounter);
    w->setData(_s);
    int lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(10000,50000));
    w->setLifeTime(lifeTime);
    
    float r=ofRandom(0,1);
    if(r<0.2 && _s!=" ")w->setIsSuggestion(true);
    
    for (auto ss : _s){
        char c = ss;
         Letter * l =new Letter();
        l->setFont(&font);
         l->setData(c);
        l->setWordId(wordcounter);
        l->setWordPointer(w);
         addLetter(l);
        cms[cms.size()-1].addMovement(letters[letters.size()-1]);
        w->addLetterPointer(l);
    }
    
    
    words.push_back(w);
    cout<<"words size "<<words.size()<<" letters Size "<<letters.size()<<endl;
    wordcounter++; // debug id
}


void StreamManager::addWord(string _s){
    Word *w;
    w->setup(words.size());
    w->setData(_s);
    words.push_back(w);
}


void StreamManager::addLetter(Letter *  _l){
    letters.push_back(_l);
}




void StreamManager::setDebug(bool _debug){
    debug=_debug;
    for(int i=0;i<cms.size();i++){
        cms[i].setDebugDraw(_debug);
    }

}


void StreamManager::addMovingWord(Word *_w){
    
    MovingWords *mw=new MovingWords();
    mw->setup();
    mw->setFont(&bigfont);
    mw->setData(_w->getMyData());
    cout<<"startpos from word"<<_w->getPosition()<<endl;

    mw->setStartPosition(_w->getPosition());
    mw->startMoving();
    movingWords.push_back(mw);

}


bool StreamManager::shouldRemoveMovingWord(MovingWords *mv){
    if(!mv->checkIsAlive()) return true;
    bool bRemove = false;
    
    // get the rectangle of the OF world
    ofRectangle rec = ofGetCurrentViewport();
    
/*    if(rec.inside(mv->getPosition()) == false) {
        mv->setIsAlive(false);
        bRemove = true;
    }*/ //not working
    return bRemove;
}


/*
void StreamManager::addWord(string _s){
    Word w;
    w.setup(words.size());
    w.setData(_s);
    words.push_back(w);
}

*/