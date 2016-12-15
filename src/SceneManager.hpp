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

#include "CarousselStackManager.hpp"
#include "CarousselLineManager.hpp"
#include "CarousselEvent.hpp"

#include "User.hpp"
#include "Fragment.hpp"
#include "Word.h"
#include "Letter.hpp"


#include "MovingWords.hpp"
#include "ofxBlurShader.h"
#include "helpers.hpp"

#include "VerticalCaroussel.hpp"



//for convenience
#define STM SceneManager::getInstance()








class SceneManager {
    
public:
    static SceneManager* getInstance();
    void initialize(int width, int height,int entrypoints,int linesPerPoint);
    bool isInitialized();
    
   void initializeCaroussel();
    
    void update();
    void draw();
    
    //LETTERMESH
    // draws all the letters with one drawcall
    ofVboMesh letterMesh;
    
    
    // CAROUSSEL
    vector<CarousselStackManager *> csm;
    vector<CarousselStackManager *> stackManagerBuffer;
    void registerStackManagerReady(CarousselStackManager * _s);
    
    CarousselStackManager * getStackmanagerWithSmallestBuffer();
    
    
    ofImage png;
    vector<ofImage *> entrypointBackgrounds;

    void unregisterLetter(Letter *l);
    
    
    void carousselEvent(CarousselEvent &e);
    
    
    
    
    VerticalCaroussel vC;
    void addDNS(string _s);

    
    // DATA
    void addDataFromBuffer();
    
    void addDataFromBuffer(CarousselStackManager * _s);
    void addMessageFromBuffer(CarousselStackManager * _s);
    
    void addMessageFromPriorityBuffer(CarousselStackManager * _s);

    

    void addWordFromManager(CarousselStackManager * _s, message m);

    
    
   // void addData(string _s, int _fragmentId);
    void addWord(string _s);

    
    //USER
    vector<User *>users;
    User * getUserByUsername(string _name);
    int getUserIndexByUsername(string _name);
    User * getUserWithMostLetters();
    
    
    //FRAGMENTS WORDS LETTERs
    vector<Fragment *> fragments;

    //Letters on screen
    vector<Letter *>letters;
    // Letters waiting to get on screen;
    map<Letter *, Letter *> lettermap;

    
    vector<Word *> words;
    Fragment* getFragmentById(int _id);
    Word * getWordByFragmentId(int _id,int _wordindex);


    
    //MOVING WORDS
    vector<MovingWords *> movingWords;
    void addMovingWord(Word * _w);
    vector <ofVec3f> movingWordPositions;
    
    void makeMovingWordByFragmentId(int _id,int _wordindex);
    bool tryMakeMovingWordByFragmentId(int _id,int _wordindex);
    void makeRandomMovingWord();

    
    // BACKGROUNDS
    ofFbo backgroundFbo; //FBO for screen One. To do the backgroundcolors
    ofFbo secondScreenbackgroundFbo; // FBO for screen two. Holds the freezed Moving Words and fades out
    ofColor backgroundcolor;
    
    //FONT
    ofTrueTypeFont  font;
    ofTrueTypeFont  bigfont;
    
    
    //INCOMING MESSAGES BUFFER
    vector <message> messageBuffer;
    void addMessage(message _m);
    
    
    //INCOMING MESSAGES BUFFER
    vector <message> priorityMessageBuffer;
    void addPriorityMessage(message _m);
    
    vector <action> actionBuffer;
    void addAction(action _a);
    
  
    // NOT CONSISTEND, fragments are not removed like that! shame!
    static bool shouldRemoveMovingWord(MovingWords *mw); // why static?
    static bool shouldRemoveLetter(Letter *l); // why static?

    
    
    // VIEWPORTS
    ofCamera cam[2];
    ofRectangle viewFront;
    ofRectangle viewBack;
    int viewportwidth; // FULLHD
    //int viewportwidth=1280; //WXGA
    int viewportheight;
    

    //DEBUG
    bool debug=false;
    void setDebug(bool debug);
    int drawMode=2;
    bool bSoundStuff=true;
    vector<float>speeds;

    
    
    
    
    ofxBlurShader blur;
    
    ofColor color1,color2,color3,color4,color5;
    
    void explode();
    
    
    void reset();
    
    
    void checkRemove();
    
    
    
    // SYSTEM VARS
    float fontsize;
    float CCwidth;
    float CCheight;
    
    int minspeed=2;
    int maxspeed=5;
    int stackmanagertotalbuffer=0;

    int totalWordsInBuffer=0;
    
    int maxWordsInBuffer=10000;

    
private:
    
    int numEntrypoints;
    int numLines;
    int managerheight;
    
    SceneManager();
    static SceneManager* instance;
    bool initialized;
    int wordcounter=0;
    
    // FLAG to load data from buffer
    bool bIsExploding=false;
    int explodestopcounter=0;
    bool bShouldReset=0;
    

};


#endif /* SceneManager_hpp */
