//
//  WordManager.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#ifndef WordManager_hpp
#define WordManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Word.h"
#include "Letter.hpp"


class WordManager {
    
public:
    WordManager();
    void setup();
    void update();
    void draw();
    
    void addWord(string _s);


    vector<Word> words;


};
#endif /* WordManager_hpp */
