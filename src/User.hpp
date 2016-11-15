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

class Letter;
class Word;
class Fragment;


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
    

    void addWordPointer(Word * _w);

    
    
    void setUserId(int _id);
    int getUserId();
    int getNumWords();
    int getNumLetters();

    void setBRemove(bool _r);
    bool getBRemove();
  
    ofColor getColor();
    ofColor getBackgroundColor();
    void setColor(ofColor _c);
    
    
    void setUserName(string _name);
    string getUserName();
    
    
    

private:
    
    string username;
    
    int userId;
    bool bRemove=false;
    
    vector<Fragment *> myFragments;
    vector<Letter *> myLetters;
    vector<Word *> myWords;

    
    ofColor myColor;
    ofColor myInitColor;
    
    ofColor targetColor;
    ofColor backgroundColor;




};

#endif /* User_hpp */
