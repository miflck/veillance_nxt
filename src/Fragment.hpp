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


class Fragment {
    
public:
    Fragment();
    void setup();
    void update();
    void draw();
    
    


    void addLetterPointer(Letter * _l);
    vector<Letter *> myLetters;

    void addWordPointer(Word * _w);
    vector<Word *> myWords;

    void setFragmentId(int _id);
    
    int getFragmentId();
    int getNumWords();
    
    
    ofRectangle getBoundingBox();
    
    Word * getWordByIndex(int _index);

private:
    int fragmentId;



};

#endif /* Fragment_hpp */
