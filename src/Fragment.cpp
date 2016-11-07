//
//  Fragment.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 01.11.16.
//
//

#include "Fragment.hpp"
Fragment::Fragment(){
}


void Fragment::setup(){


}


void Fragment::update(){

}


void Fragment::draw(){


}


void Fragment::addLetterPointer(Letter *_l){
    myLetters.push_back(_l);
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

