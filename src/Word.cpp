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

void Word::setup(){
    
}

void Word::update(){
    float p=ABS(ofGetHeight()/2-position.y);
    spacingFact=ofMap(p,0,ofGetHeight()/2,1,10);
    
    font->setLetterSpacing(spacingFact);
    wordwidth = font->stringWidth(data);
  


    /*font->setLetterSpacing(spacingFact);
     float fontWidth = font->stringWidth(data);

    position.x-=speed;
    if(position.x<-fontWidth){
        position.x=ofGetWidth();
        position.y-=font->getLineHeight();
        spacingFact=ofMap(p,0,ofGetHeight()/2,1,10);
        speed=ofMap(p,0,ofGetHeight()/2,1,10);
    };*/
 
}

void Word::draw(){
    font->setLetterSpacing(spacingFact);

    ofSetColor(0);
    ofPushMatrix();
   ofTranslate(position.x,position.y,position.z);
   font->drawString(data, 0,0);
    ofPopMatrix();
 ;
}

void Word::setData(string _data){
    data=_data;
    makeLetters(data);
    cout<<data<<endl;
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
    float p=ABS(ofGetHeight()/2-position.y);
    spacingFact=ofMap(p,0,ofGetHeight()/2,1,10);
    //font->setLetterSpacing(spacingFact);
    speed=10;

}


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



