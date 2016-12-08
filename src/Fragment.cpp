//
//  Fragment.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 01.11.16.
//
//

#include "Fragment.hpp"
#include "Letter.hpp"
#include "SceneManager.hpp"


Fragment::Fragment(){
}


void Fragment::setup(){
    

    backgroundColor=ofColor(ofRandom(50,255),ofRandom(50,255),ofRandom(50,255));
    myColor=ofColor(0,0,255);
    myInitColor=ofColor(0,0,255);
    
    targetColor=ofColor(0,0,255);


}


void Fragment::update(){
    
    if(checkShouldRemove()){
    cout<<"unregister fragment"<<getFragmentId()<<endl;
    myUserPointer->unregisterFragment(this);
        setBRemove(true);
    }
}


void Fragment::draw(){

    /*
    STM->backgroundFbo.begin();
    ofDrawRectangle(getBoundingBox().getPosition(), getBoundingBox().width,getBoundingBox().height);
    STM->backgroundFbo.end();
     */

}


ofRectangle Fragment::getBoundingBox(){
    ofVec2f p=myLetters[0]->getPosition();
    ofVec2f p2=myLetters[myLetters.size()-1]->getPosition();
    return ofRectangle(p,p2);
}


void Fragment::addLetterPointer(Letter *_l){
    myLetters.push_back(_l);
}


void Fragment::registerLetter(Letter *_l){
    myLetters.push_back(_l);
}

void Fragment::unregisterLetter(Letter *_l){
    
    auto it = std::find(myLetters.begin(), myLetters.end(), _l);
    if (it != myLetters.end()) {
        myLetters.erase(it);
    }
}


void Fragment::unregisterWord(Word *_w){
    auto it = std::find(myWords.begin(), myWords.end(), _w);
    if (it != myWords.end()) { myWords.erase(it); }
    
    
    if(myWords.size()==0){
      //  setBRemove(true);
    }
    
    /// myLetters.push_back(_l);
}


void Fragment::registerWord(Word *_w){
    myWords.push_back(_w);
}


void Fragment::setBRemove(bool _b){
    bRemove=_b;
}

bool Fragment::getBRemove(){
    return bRemove;
}


void Fragment::addWordPointer(Word *_w){
    myWords.push_back(_w);
}

void Fragment::setFragmentId(int _id){
    fragmentId=_id;
}

int Fragment::getFragmentId(){
    return fragmentId;
}

int Fragment::getNumWords(){
    return myWords.size();
}

Word* Fragment::getWordByIndex(int _index){
    if(_index<getNumWords()){
        return myWords[_index];
    }else return nullptr;
}



void Fragment::setColor(ofColor _c){
    myColor=_c;
}


ofColor Fragment::getColor(){
    return myColor;
}

ofColor Fragment::getBackgroundColor(){
   // return backgroundColor;
  //  if(myUserPointer==NULL)cout<<getFragmentId()<<endl;
    return myUserPointer->getBackgroundColor();
}

void Fragment::setUserPointer(User *_u){
    myUserPointer=_u;
}

bool Fragment::checkShouldRemove(){
    bool b=false;
    if(myLetters.size()==0)b = true;
    return b;
}
