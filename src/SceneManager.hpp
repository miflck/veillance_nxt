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



//for convenience
#define STM SceneManager::getInstance()





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
    void initialize(int width, int height,int entrypoints,int linesPerPoint);
    bool isInitialized();
    
    void update();
    void draw();
    
    //LETTERMESH
    // draws all the letters with one drawcall
    ofVboMesh letterMesh;
    
    
    // CAROUSSEL
    CarousselLineManager cm;
    
    vector<CarousselLineManager> cms;
    
    
    vector<CarousselStackManager *> csm;
    vector<CarousselStackManager *> stackManagerBuffer;
    
    void registerStackManagerReady(CarousselStackManager * _s);

    
    void unregisterLetter(Letter *l);
    
    
    void carousselEvent(CarousselEvent &e);

    
    // DATA
    void addDataFromBuffer();
    
    void addDataFromBuffer(CarousselStackManager * _s);

    
    void addDataFromManager(CarousselStackManager * _s, message m);

    
    
    void addData(string _s, int _fragmentId);
    void addWord(string _s);

    
    //USER
    vector<User *>users;
    User * getUserByUsername(string _name);
    int getUserIndexByUsername(string _name);
    User * getUserWithMostLetters();
    
    
    //FRAGMENTS WORDS LETTERs
    vector<Fragment *> fragments;
    vector<Letter *>letters;
    
    vector<Letter *>letterbuffer;
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
    int drawMode=0;
    bool bSoundStuff=true;
    
    
    
    
    
    ofxBlurShader blur;
    ofImage png;
    
    ofColor color1,color2,color3,color4,color5;
    
    void explode();
    
    
    void reset();
    
    
    
private:
    
    int numEntrypoints;
    int numLines;
    
    SceneManager();
    static SceneManager* instance;
    bool initialized;
    int wordcounter=0;
    
    // FLAG to load data from buffer
    bool bIsReadyForData=true;
    
    bool bIsExploding=false;
    
};


#endif /* SceneManager_hpp */
