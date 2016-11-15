//
//  SceneManager.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Word.h"


#include "CarousselManager.hpp"
#include "CarousselEvent.hpp"
#include "Letter.hpp"


#include "Fragment.hpp"


#include "MovingWords.hpp"



//for convenience
#define STM SceneManager::getInstance()




struct message {
    int uuid;
    string name;
    string type;
    string text;
};



struct action {
    int uuid;
    int startwordcounter;
    int endwordcounter;
    string name;
    string type;
    string text;
};







class SceneManager {
    
public:
    static SceneManager* getInstance();
    void initialize();
    bool isInitialized();
    
    
    void update();
    void draw();
    
    
    //Mesh
    ofVboMesh drawMesh;

    
    
    
    // CAROUSSEL
    CarousselManager cm;
    vector<CarousselManager> cms;
    void carousselEvent(CarousselEvent &e);

    
    
    // DATA
    
    void addDataFromBuffer();

    
    
    void addData(string _s, int _fragmentId);
    void addWord(string _s);

    vector<Fragment *> fragments;

    
    
    
    //LETTER
    vector<Letter *>letters;
    void addLetter(Letter * _l);
    
    vector<Word *> words;

    
    //Moving Words
    vector<MovingWords *> movingWords;
    void addMovingWord(Word * _w);
    
    vector <ofVec3f> movingWordPositions;

    
    
    
    
    //Background
    ofImage bkg;
    
    
    //FONT
    
    ofTrueTypeFont  font;
    ofTrueTypeFont  bigfont;
    
    
    
    
    
    
    //BUFFER
    
    vector <message> messageBuffer;
    void addMessage(message _m);
    
    vector <action> actionBuffer;
    void addAction(action _a);
    
    
    
    
    //debug
    bool bUpdate=true;
    bool bDraw=true;
    
    bool debug;
    void setDebug(bool debug);
    
    static bool shouldRemoveMovingWord(MovingWords *mw); // why static
    
    
    static bool shouldRemoveLetter(Letter *l); // why static

    
    
    Fragment* getFragmentById(int _id);
    void makeMovingWordByFragmentId(int _id,int _wordindex);
    
    
    bool tryMakeMovingWordByFragmentId(int _id,int _wordindex);

    
    void makeRandomMovingWord();
    
    
    
    ofCamera cam[2];
    ofRectangle viewFront;
    ofRectangle viewBack;

    
    ofFbo backgroundFbo;

    
private:
    SceneManager();
    static SceneManager* instance;
    bool initialized;
    int wordcounter=0;
    
    
    bool bIsReadyForData=true;
    
    
    
};


#endif /* SceneManager_hpp */
