//
//  Stream.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 10.10.16.
//
//

#ifndef Stream_h
#define Stream_h

#include <stdio.h>
#include "ofMain.h"
#include "Word.h"
#include "LetterEvent.hpp"
#include "Letter.hpp"



class Stream {
    
public:
    Stream();
    void setup();
    void update();
    void draw();
    
    
    //DATA
    vector<string> data; //declare a vector of strings to store data
    void setData(vector<string> _data);
    
    ofTrueTypeFont  *font;
    void setFont(ofTrueTypeFont *f);

    void addWord(Word _word);
    vector<Word> words;
    
    
    void addLetter(Letter *_l);
    vector<Letter *>letters;
    
    
    void letterEvent(LetterEvent &e);

    
private:
};





#endif /* Stream_h */
