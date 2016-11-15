//
//  Fragment.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 01.11.16.
//
//

#ifndef Fragment_hpp
#define Fragment_hpp

#include <stdio.h>
#include "ofMain.h"

class Letter;
class Word;
class User;

class Fragment {
    
public:
    Fragment();
    void setup();
    void update();
    void draw();
    
    


    void addLetterPointer(Letter * _l);
    
    void registerLetter(Letter * _l);
    void unregisterLetter(Letter * _l);
    
    
    void registerWord(Word * _w);
    void unregisterWord(Word * _w);
    

    void addWordPointer(Word * _w);
    vector<Word *> myWords;

    void setFragmentId(int _id);
    
    int getFragmentId();
    int getNumWords();
    
    ofRectangle getBoundingBox();
    Word * getWordByIndex(int _index);
    
    void setBRemove(bool _r);
    bool getBRemove();
  
    
    
    ofColor getColor();
    ofColor getBackgroundColor();
    void setColor(ofColor _c);
    
    
    User * myUserPointer;
    void setUserPointer(User * _u);

private:
    int fragmentId;
    bool bRemove=false;
    
    
    vector<Letter *> myLetters;
    
    
    ofColor myColor;
    ofColor myInitColor;
    
    ofColor targetColor;
    ofColor backgroundColor;




};

#endif /* Fragment_hpp */
