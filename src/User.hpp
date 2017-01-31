//
//  Fragment.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 01.11.16.
//
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Background.h"

class Letter;
class Word;
class Fragment;
class MovingWords;


class User {
    
public:
    User();
    void setup();
    void update();
    void draw();
    
    


    void addLetterPointer(Letter * _l);
    
    
    // Register stuff
    void registerFragment(Fragment * _f);
    void unregisterFragment(Fragment * _f);
    
    
    void registerLetter(Letter * _l);
    void unregisterLetter(Letter * _l);
    
    void registerWord(Word * _w);
    void unregisterWord(Word * _w);
    
    
    // Register stuff
    void registerMovingWord(MovingWords * _w);
    void unregisterMovingWord(MovingWords * _w);
    
    

    void addWordPointer(Word * _w);

    
    
    void setUserId(int _id);
    int getUserId();
    int getNumWords();
    int getNumLetters();
    
    
    int getNumWordsInBuffer();
    void setNumWordsInBuffer(int _num);
    void addNumWordsInBuffer(int _num);




    void setBRemove(bool _r);
    bool getBRemove();
  
    ofColor getColor();
    ofColor getBackgroundColor();
    void setColor(ofColor _c);
    
    
    void setUserName(string _name);
    string getUserName();
    
    
    int getNumWordsOnScreen();
    
    void checkSoundHack();
    void checksoundZpos();
    
    
    
    void reset();
    
    bool bIsIpColor=true;

    
    
  //  Background * backgroundSound;

private:
    
    string username;
    
    int userId;
    bool bRemove=false;
    
    vector<Fragment *> myFragments;
    vector<Letter *> myLetters;
    vector<Word *> myWords;
    vector<MovingWords *> myMovingWords;

    
    ofColor myColor;
    ofColor myInitColor;
    
    ofColor targetColor;
    ofColor backgroundColor;


    int numWordsInBuffer;


};

#endif /* User_hpp */
