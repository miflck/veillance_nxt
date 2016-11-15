//
//  Fragment.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 01.11.16.
//
//

#include "User.hpp"
#include "Letter.hpp"
#include "SceneManager.hpp"


User::User(){
}


void User::setup(){
    

    backgroundColor=ofColor(ofRandom(50,255),ofRandom(50,255),ofRandom(50,255));
    myColor=ofColor(0,0,255);
    myInitColor=ofColor(0,0,255);
    
    targetColor=ofColor(0,0,255);


}


void User::update(){

}


void User::draw(){

    STM->backgroundFbo.begin();
    
    
    STM->backgroundFbo.end();

}




void User::addLetterPointer(Letter *_l){
    myLetters.push_back(_l);
}


void User::registerLetter(Letter *_l){
    myLetters.push_back(_l);
}

void User::unregisterLetter(Letter *_l){
    
 //   cout<<"unregister from fragment "<<fragmentId<<" "<<myLetters.size()<<" "<<myWords.size()<<endl;
    
    
    auto it = std::find(myLetters.begin(), myLetters.end(), _l);
    if (it != myLetters.end()) {
        myLetters.erase(it);
    }
    
   // cout<<"letters now "<<fragmentId<<" "<<myLetters.size()<<endl;

    
    if(myLetters.size()==0){
        setBRemove(true);
    }
    
}


void User::unregisterWord(Word *_w){
    auto it = std::find(myWords.begin(), myWords.end(), _w);
    if (it != myWords.end()) { myWords.erase(it); }
    
    
    if(myWords.size()==0){
      //  setBRemove(true);
    }
    
    /// myLetters.push_back(_l);
}


void User::registerWord(Word *_w){
    myWords.push_back(_w);
}





void User::registerFragment(Fragment *_f){
    myFragments.push_back(_f);
}

void User::unregisterFragment(Fragment *_f){
    auto it = std::find(myFragments.begin(), myFragments.end(), _f);
    if (it != myFragments.end()) { myFragments.erase(it); }
    if(myFragments.size()==0){
        setBRemove(true);
        cout<<"user "<<username<<"can be removed"<<endl;
    }
}



void User::setBRemove(bool _b){
    bRemove=_b;
}

bool User::getBRemove(){
    return bRemove;
}


void User::addWordPointer(Word *_w){
    myWords.push_back(_w);
}


void User::setUserName(string _name){
    username=_name;
}

string User::getUserName(){
    return username;
}


void User::setUserId(int _id){
   userId=_id;
}

int User::getUserId(){
    return userId;
}

int User::getNumWords(){
    return myWords.size();
}


int User::getNumLetters(){
    return myLetters.size();
}


void User::setColor(ofColor _c){
    myColor=_c;
}


ofColor User::getColor(){
    return myColor;
}

ofColor User::getBackgroundColor(){
    return backgroundColor;
}




