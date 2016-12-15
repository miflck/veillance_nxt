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
#include "SoundManager.hpp"

User::User(){
}


void User::setup(){
    

    
   // backgroundColor=ofColor(ofRandom(50,255),ofRandom(50,255),ofRandom(50,255));
    backgroundColor.setHsb(ofRandom(0,255),255,255);
    
    myColor=ofColor(0,0,255);
    myInitColor=ofColor(0,0,255);
    
    targetColor=ofColor(0,0,255);


}


void User::update(){
    if(STM->bSoundStuff)checksoundZpos();
}


void User::draw(){



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


void User::unregisterMovingWord(MovingWords *_w){
    
    
    /*
    if(_w->bHasSound){
        int i=getUserId();
        switch (i) {
            case 0:
                //Send info to soundmanager -> hacky
                SoundM->user1vowelcount.set(0);
                SoundM->user1sylcont1.set(0);
                break;
                
            case 1:
                //Send info to soundmanager -> hacky
                SoundM->user2vowelcount.set(0);
                SoundM->user2sylcont1.set(0);
                break;
                
            case 2:
                //Send info to soundmanager -> hacky
                SoundM->user3vowelcount.set(0);
                SoundM->user3sylcont1.set(0);
                break;
                
            default:
                break;
        }
    }*/

    
    
    
    auto it = std::find(myMovingWords.begin(), myMovingWords.end(), _w);
    if (it != myMovingWords.end()) { myMovingWords.erase(it); }
    
    
    if(myMovingWords.size()==0){
        //setBRemove(true);
    }
    
    
    
       /// myLetters.push_back(_l);
}


void User::registerMovingWord(MovingWords *_w){
    myMovingWords.push_back(_w);
    if(STM->bSoundStuff)checkSoundHack();
}


void User::checksoundZpos(){
    
    if(myMovingWords.size()<1)return;
    
    bool hasSound=false;
    int index=0;
    for (int i=0;i<myMovingWords.size();i++){
        if(myMovingWords[i]->bHasSound){
            hasSound=true;
            index=i;
            break;
        }
    }
    
    
    
    if(hasSound){
        int i=getUserId();
        //int index=myMovingWords.size()-1;
        
        ofVec3f p=myMovingWords[index]->getPosition();
        
        float mappedZ=ofMap(p.z,0,500,0,1,true);
        float mappedX=ofMap(p.x,-1000,1000,-1,1,true);

        
        switch (i) {
            case 0:
                //Send info to soundmanager -> hacky
                SoundM->user1pan.set(mappedX);
                SoundM->user1Zpos.set(mappedZ);
                break;
                
            case 1:
                //Send info to soundmanager -> hacky
                SoundM->user2pan.set(mappedX);
                SoundM->user2Zpos.set(mappedZ);
                
                break;
                
            case 2:
                //Send info to soundmanager -> hacky
                SoundM->user3pan.set(mappedX);
                SoundM->user3Zpos.set(mappedZ);
                
                break;
                
                
            case 3:
                //Send info to soundmanager -> hacky
                SoundM->user4pan.set(mappedX);
                SoundM->user4Zpos.set(mappedZ);
                
                break;
                
                
            default:
                break;
        }

        
        
        
        
        
        if(p.z>550){
            switch (i) {
                case 0:
                    //Send info to soundmanager -> hacky
                    SoundM->user1vowelcount.set(0);
                    SoundM->user1sylcont1.set(0);
                    myMovingWords[index]->bHasSound=false;
                    break;
                    
                case 1:
                    //Send info to soundmanager -> hacky
                    SoundM->user2vowelcount.set(0);
                    SoundM->user2sylcont1.set(0);
                    myMovingWords[index]->bHasSound=false;

                    break;
                    
                case 2:
                    //Send info to soundmanager -> hacky
                    SoundM->user3vowelcount.set(0);
                    SoundM->user3sylcont1.set(0);
                    myMovingWords[index]->bHasSound=false;

                    break;
                    
                    
                case 3:
                    //Send info to soundmanager -> hacky
                    SoundM->user4vowelcount.set(0);
                    SoundM->user4sylcont1.set(0);
                    myMovingWords[index]->bHasSound=false;
                    
                    break;
                    
                    
                default:
                    break;
            }
        }
    }

}


void User::checkSoundHack(){
    
    if(myMovingWords.size()<1)return;
    bool hasSound=false;
    for (auto word:myMovingWords){
        if(word->bHasSound){
           hasSound=true;
        }
    }
    
    int i=getUserId();

    cout<<"hassound "<<hasSound<<" "<<i<<endl;

    
    if(!hasSound){
    int index=myMovingWords.size()-1;
        cout<<"set sound for "<<i<<endl;

    switch (i) {
        case 0:
            //Send info to soundmanager -> hacky
            SoundM->user1vowelcount.set(myMovingWords[index]->getSyllablescount());
            SoundM->user1sylcont1.set(myMovingWords[index]->getVowelcount());
            myMovingWords[index]->bHasSound=true;
            break;
            
        case 1:
            //Send info to soundmanager -> hacky
            SoundM->user2vowelcount.set(myMovingWords[index]->getSyllablescount());
            SoundM->user2sylcont1.set(myMovingWords[index]->getVowelcount());
            myMovingWords[index]->bHasSound=true;
            break;
            
        case 2:
            //Send info to soundmanager -> hacky
            SoundM->user3vowelcount.set(myMovingWords[index]->getSyllablescount());
            SoundM->user3sylcont1.set(myMovingWords[index]->getVowelcount());
            myMovingWords[index]->bHasSound=true;
            break;
            
        case 3:
            //Send info to soundmanager -> hacky
            SoundM->user4vowelcount.set(myMovingWords[index]->getSyllablescount());
            SoundM->user4sylcont1.set(myMovingWords[index]->getVowelcount());
            myMovingWords[index]->bHasSound=true;
            break;
            
        default:
            break;
    }

    }

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
    
    //debug!!
    backgroundColor.setHsb(255/10*_id,255,255);

}

int User::getUserId(){
    return userId;
}

int User::getNumWords(){
    return myWords.size();
}

int User::getNumWordsOnScreen(){
    int n=0;
    for(auto w:myWords){
        if(w->checkIsOnScreen())n++;
    }
    
    return n;
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


void User::reset(){



}




