//
//  StreamManager.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#ifndef StreamManager_hpp
#define StreamManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Word.h"
#include "WordManager.hpp"


#include "CarousselManager.hpp"
#include "CarousselEvent.hpp"
#include "Letter.hpp"


#include "MovingWords.hpp"



//for convenience
#define STM StreamManager::getInstance()



class StreamManager {
    
public:
    static StreamManager* getInstance();
    void initialize();
    bool isInitialized();
    
    
    void update();
    void draw();
    
    
    
    // CAROUSSEL
    CarousselManager cm;
    vector<CarousselManager> cms;
    void carousselEvent(CarousselEvent &e);

    
    
    // DATA
    void addData(string _s);
    void addWord(string _s);

    
    
    //LETTER
    vector<Letter *>letters;
    void addLetter(Letter * _l);
    
    vector<Word *> words;

    
    //Moving Words
    vector<MovingWords *> movingWords;
    void addMovingWord(Word * _w);
    
    
    
    //FONT
    
    ofTrueTypeFont  font;
    ofTrueTypeFont  bigfont;
    
    
    
    //debug
    bool bUpdate=true;
    bool bDraw=true;
    
    
    bool debug;
    void setDebug(bool debug);
    
    
    static bool shouldRemoveMovingWord(MovingWords *mw); // why static
    
    
private:
    StreamManager();
    static StreamManager* instance;
    bool initialized;
    int wordcounter=0;
    
};


#endif /* StreamManager_hpp */
