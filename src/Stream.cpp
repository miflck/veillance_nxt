//
//  Stream.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#include "Stream.h"

Stream::Stream(){
}

void Stream::setup(){
    // listen to any of the events for the game
    ofAddListener(LetterEvent::events, this, &Stream::letterEvent);


}

void Stream::update(){
    
   // font->setLetterSpacing(spacingFact);
  //  float fontWidth = font->stringWidth(data);
   /* position.x-=speed;
    if(position.x<-fontWidth){
        position.x=ofGetWidth();
        position.y-=font->getLineHeight();
        float p=ABS(ofGetHeight()/2-position.y);
        spacingFact=ofMap(p,0,ofGetHeight()/2,1,10);
        speed=ofMap(p,0,ofGetHeight()/2,1,10);
    };*/

    if(words.size()>0){
   /* ofVec3f pos=words[0].getPosition();
    float p=ABS(ofGetHeight()/2-pos.y);
    float speed=ofMap(p,0,ofGetHeight()/2,1,10);
    pos.x-=speed;
    words[0].setPosition(pos);*/

    for(int i=0;i<words.size();i++){
       ofVec3f pos=words[i].getPosition();
        float p=ABS(ofGetHeight()/2-pos.y);
        float speed=ofMap(p,0,ofGetHeight()/2,1,10);
        pos.x-=speed;
        
        if(pos.x<-words[i].getWidth()){
            if(i==0){
                pos.x=ofGetWidth();
            }else{
                pos.x=(words[i-1].getPosition().x+words[i].getWidth());
            }
            pos.y-=font->getLineHeight();
        };

        
        
        words[i].setPosition(pos);
    }
    
    
    for(int i=0;i<words.size();i++){
        words[i].update();
    }
    
    
    }
    
    
    
    
}

void Stream::draw(){
    for(int i=0;i<words.size();i++){
        words[i].draw();
    }
}

void Stream::setData(vector<string> _data){
        data=_data;
   // cout<<data[0]<<endl;
}

void Stream::setFont(ofTrueTypeFont *f){
    font=f;

}


void Stream::addWord(Word _word){
    words.push_back(_word);
}


void Stream::addLetter(Letter * _l){
    letters.push_back(_l);
}

void Stream::letterEvent(LetterEvent &e) {
    
    cout << "Letter Event: "+e.message << endl;
    addLetter(e.letter);
    
   /* e.bug->timeBugKilled = ofGetElapsedTimef();
    e.bug->bSquashed = true;
    
    e.bullet->bRemove = true;
    
    bugsKilled ++;*/
}

