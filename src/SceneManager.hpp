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
#include "helpers.hpp"

#include "VerticalCaroussel.hpp"
#include "OrthoCamera.h"

#include "globals.hpp"




#include "ofxUnicode.h"


//for convenience
#define STM SceneManager::getInstance()








class SceneManager {
    
public:
    static SceneManager* getInstance();
    void initialize();
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
    void addDNS(dns _dns);

    void addDNSEntity(dns _dns);
    vector <dns> dnsBuffer;


    
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
    
    User * getUserWithMostWordsInBuffer();

    
    
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
    void makeRandomBurst(int _amt);

    
    // BACKGROUNDS
    ofFbo backgroundFBO; //FBO for all screens
    
    //ofFbo backgroundFBO0; // FBO for screen two. Holds the freezed Moving Words and fades out
    //ofFbo backgroundFBO1; // FBO for screen two. Holds the freezed Moving Words and fades out
    //ofFbo backgroundFBO2; // FBO for screen two. Holds the freezed Moving Words and fades out
    ofFbo backgroundFBO3; // FBO for screen two. Holds the freezed Moving Words and fades out

    ofFbo backgroundDNSFBO; // FBO for screen two. Holds the freezed Moving Words and fades out

    
    
    ofColor backgroundcolor;
    
    //FONT
    ofTrueTypeFont  font;
    ofTrueTypeFont  bigfont;
    ofTrueTypeFont  dnsfont;
    
    
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
    
    orthoCamera camFront;
    orthoCamera camFront2;

    
    ofCamera cam[5];
    ofRectangle viewFront;
    ofRectangle viewBack;
    
    
    ofRectangle viewLeft;
    ofRectangle viewRight;
    
    
    ofRectangle blende;
    
    
   // int viewportwidth; // FULLHD
    //int viewportwidth=1280; //WXGA
   // int viewportheight;
    

    //DEBUG
    bool debug=false;
    void setDebug(bool debug);
    int drawMode=2;
    bool bSoundStuff=false;
    vector<float>speeds;

    
    
    
    
    
    ofColor color1,color2,color3,color4,color5;
    
    void explode();
    
    
    void reset();
    
    
    void checkRemove();
    
    
    
    // SYSTEM VARS
   // float fontsize;
   // float CCwidth;
   // float CCheight;
    
    int minspeed=2;
    int maxspeed=5;
    int stackmanagertotalbuffer=0;

    int totalWordsInBuffer=0;
    
    //int maxWordsInBuffer=10000;

    
    void drawTrails(bool _b);
    void toggleDrawTrails();
    
    float leftTheta=0;
    float rightTheta=0;

    
    bool bGetMostUser=true;
    
    
    int burstTimer=0;
    int burstTimerDuration=1000;
    bool bIsBursting=false;
    
    bool bIsDNSList=true;
    
    
private:
    
    
    clusterpoint clusterpointleft;
    clusterpoint clusterpointright;

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
    
    bool bDrawTrails=true;
    

};


#endif /* SceneManager_hpp */
