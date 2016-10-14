//
//  Letter.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#include "Letter.hpp"
Letter::Letter(){
}

void Letter::setup(){
    
    static LetterEvent newEvent;
    newEvent.message = "New Letter";
    newEvent.letter     = this;
    ofNotifyEvent(LetterEvent::events, newEvent);
    
}

void Letter::update(){
    
}

void Letter::draw(){
    
    
}


void Letter::setData(char _data){
    data=_data;
}


char Letter::getData(){
    return data;
}