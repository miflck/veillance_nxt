//
//  Word.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#include "Word.h"
Word::Word(){
}

void Word::setup(int _index){
    wordIndex=_index;
    cout<<wordIndex<<endl;

}

void Word::update(){
}

void Word::draw(){
    }

void Word::setData(string _data){
    data=_data;
}

void Word::setFont(ofTrueTypeFont *f){
    font=f;
}

float Word::getWidth(){
    return wordwidth;
};

ofVec3f Word::getPosition(){
    return position;

}

void Word::setPosition(ofVec3f pos){
    position.set(pos);
  }

/*
void Word::makeLetters(string _datastring){
    ofVec3f position=ofVec3f(0,0,0);
    
    //font.setKerning(true);
    
    string s = _datastring;
    float x = 0;
    float y = 0;
    
    vector < ofRectangle > rects;
    for (auto ss : s){
        string sss = "";
        sss += ss;
        ofRectangle r = font->getStringBoundingBox(sss, x, y);
        //cout << x << " " << r.x << endl;
        if (ss == ' '){
            //r.width = 10;
            r=font->getStringBoundingBox("H", x, y);
        }
        r.x = x;
        rects.push_back(r);
        float dx = x - r.x;
        ofNoFill();
        //ofRect(r);
        ofFill();
        x = (r.x + r.width);
        Letter l;
        l.setup();
        l.setData(ss);
        letters.push_back(l);
        }
}
*/


