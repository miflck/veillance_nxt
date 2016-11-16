//
//  SceneManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#include "SceneManager.hpp"
#include "SoundManager.hpp"

SceneManager* SceneManager::instance = 0;
SceneManager* SceneManager::getInstance() {
    if (!instance) {
        instance = new SceneManager();
    }
    return instance;
}


SceneManager::SceneManager(){
}


void SceneManager::initialize(int width, int height) {
    
    initialized=true;
    cout<<"init SceneManager"<<endl;
    
    font.load("FoundersGroteskMonoBold.ttf", 10);
    bigfont.load("FoundersGroteskMonoBold.ttf", 60);
    
    viewportwidth=width/2;
    viewportheight=height;
    // CAROUSSEL
    //These are the animationcontrollers of the background. Each one controlls a Line
    
    float minspeed=2;
    float speed;
    int h=20;
    int w=10;
    
    int lines=floor(ofGetHeight()/h);
    cout<<"lines"<<lines<<endl;
    for(int i = 0; i < lines; i++){
        CarousselManager cm;
        float p=ABS((ofGetHeight()/2)-((i*h)));
        float dl= ofMap(p*(p/4),0,ofGetHeight()/2*(ofGetHeight()/2/4),1,100);
        float dW=w+dl;
        // s=v*t  s/v=t  v=s/t
        float time=w/minspeed;
        float dv=dW/time;
        float speed=dv;
        float r=ofRandom(0,50);
        cm.setup(ofVec2f(0,(i*h)),viewportwidth,ofGetHeight(),dW,h);
        cm.maxspeed=speed;
        cm.setId(i);
        cms.push_back(cm);
    }
    
    // Event listener for the Carousselevents. Tells the Scenemanager when to feed the buffer or move one line up etc
    ofAddListener(CarousselEvent::events, this, &SceneManager::carousselEvent);
    
    
    // CAMERA AND VIEWPORTS
    
    //Viewports
    viewFront.x = 0;
    viewFront.y = 0;
    viewFront.width = ofGetWidth()/2;
    viewFront.height = ofGetHeight();
    
    viewBack.x = ofGetWidth()/2;
    viewBack.y = 0;
    viewBack.width = ofGetWidth()/2;
    viewBack.height = ofGetHeight();
    
    // Camera
    cam[0].setVFlip(true);
    cam[0].setFov(60);
    float d=cam[0].getImagePlaneDistance(viewFront);
    cam[0].setPosition(viewportwidth/2, ofGetHeight()/2, d);
    
    
    cam[1].setVFlip(true);
    cam[1].setNearClip(10);
    cam[1].setPosition(viewportwidth/2, ofGetHeight()/2, d-200);
    cam[1].pan(180);
    
    
    // BACKGROUNDCOLOR
    // Background FBO for Backgroundcolorstuff.
    backgroundFbo.allocate(viewportwidth, ofGetHeight(),GL_RGBA);
    backgroundFbo.begin();
    ofClear(255,255,255, 0);
    backgroundFbo.end();
    
    secondScreenbackgroundFbo.allocate(viewportwidth, ofGetHeight(),GL_RGBA);
    secondScreenbackgroundFbo.begin();
    ofClear(255,255,255, 0);
    secondScreenbackgroundFbo.end();
    ofEnableAlphaBlending();
    
    
    
}




void SceneManager::update(){
    
    // Check if we have to feed data from Buffer to Caroussel
    if(bIsReadyForData){
        bIsReadyForData=false;
        addDataFromBuffer();
    }
    
    // Check if we have actions to make
    if(actionBuffer.size()>0){
        for (int i=0;i<actionBuffer.size();i++){
            action a=actionBuffer[i];
            
            Word*w =getWordByFragmentId(a.uuid,a.startwordcounter);
            if(w!=nullptr){
                if(w->getIsLocked()){
                }else{
                w->setIsSuggestion(true);
                }
                actionBuffer.erase(actionBuffer.begin()+i);
            }else{
                //cout<<"suggestion is not on screen"<<endl;
            }
            
            
            
            /*if(tryMakeMovingWordByFragmentId(a.uuid,a.startwordcounter) || tryMakeMovingWordByFragmentId(a.uuid,a.endwordcounter)){
                actionBuffer.erase(actionBuffer.begin()+i);
            }*/
            
            
        }
        
    }
    
    
    
    
    
    // UPDATE CAROUSSEL
    for(int i=0;i<cms.size();i++){
        cms[i].update();
    }
    
    
    // REMOVE STUFF FROM SCREEN AND MEMORY -> Wrap that up?
    
    for (int i=0;i<letters.size();i++){
        if(letters[i]->getBRemove()){
            delete (letters[i]);
            letters.erase(letters.begin()+i);
        }
    }
    
    
    for (int i=0;i<words.size();i++){
        if(words[i]->getBRemove()){
            delete (words[i]);
            words.erase(words.begin()+i);
        }
    }
    
    for (int i=0;i<fragments.size();i++){
        if(fragments[i]->getBRemove()){
            delete (fragments[i]);
            fragments.erase(fragments.begin()+i);
        }
    }
    
    // check if we want to remove movingwords
    for (int i=0;i<movingWords.size();i++){
        if(shouldRemoveMovingWord(movingWords[i])){
            delete (movingWords[i]);
            movingWords.erase(movingWords.begin()+i);
        }
    }
    
    //UPDATE
    for(auto word:words){
        word->update();
    }
    
    for(auto movingWord:movingWords){
        movingWord->update();
        /*
         if(movingWords[movingWord->myDockingNode]!=nullptr && movingWords[movingWord->myDockingNode]!= 0 && !movingWords[movingWord->myDockingNode]->bIsMoving){
         movingWord->setTarget(movingWords[movingWord->myDockingNode]->getDockPoint());
         }
         */
    }
    
    for(auto letter:letters){
        letter->update();
    }
    
    
    
    
    // ADD BLACK SQUARE TO BACKGROUNDCOLOR
    backgroundFbo.begin();
    ofSetColor(0,0,0,10);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    ofEnableAlphaBlending();
    ofDrawRectangle(0, 0, backgroundFbo.getWidth(), backgroundFbo.getHeight());
    ofDisableBlendMode();
    backgroundFbo.end();
    
    secondScreenbackgroundFbo.begin();
    ofSetColor(0,0,0,5);
    ofEnableAlphaBlending();
    if(ofGetFrameNum()%10==0)ofDrawRectangle(0, 0, backgroundFbo.getWidth(), backgroundFbo.getHeight());
    secondScreenbackgroundFbo.end();
    
    //Sound-> hacked draft constrain to 100 Words
    if(users.size()>0){
        
        int w= users[0]->getNumWordsOnScreen();
        if(w>100)w=100;
        SoundM->user1wordcount.set(w);
        
        if(users.size()>1){
            int w= users[1]->getNumWordsOnScreen();
            if(w>100)w=100;
            SoundM->user2wordcount.set(w);
        }
    
        if(users.size()>2){
            int w= users[2]->getNumWordsOnScreen();
            if(w>100)w=100;
            SoundM->user3wordcount.set(w);
        }
        
        
    }
    
}


void SceneManager::draw(){
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // background
    if(debug) backgroundFbo.draw(0,0);
    secondScreenbackgroundFbo.draw(viewportwidth,0);
    
    cam[0].begin(viewFront);
    
    // Color code. not using at the moment
    if(debug){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    backgroundFbo.begin();
    ofEnableAlphaBlending();
    for(int i=0;i<cms.size();i++){
        cms[i].draw();
    }
    backgroundFbo.end();
    
    }
    //No need to draw each element. Doing this now with one mesh for better performance
    /*
     
     for(auto letter:letters){
     letter->draw();
     }
     
    for(auto word:words){
        word->draw();
    }
    
    for(auto fragment:fragments){
        fragment->draw();
    }
    */
    
    // getting the lettermesh
    letterMesh.clear();
    for(auto letter:letters){
        letterMesh.append(letter->getUpdatedVboMesh());
    }
    font.getFontTexture().bind();
    letterMesh.draw();
    font.getFontTexture().unbind();
    
    // moving words mesh
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofVboMesh m;
    for(auto movingWord:movingWords){
        m.append(movingWord->getUpdatedVboMesh());
    }
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
   
    cam[0].end();
    
    /* ofEnableBlendMode(OF_BLENDMODE_ALPHA);
     secondScreenbackgroundFbo.begin();
     cam[1].begin();
     bigfont.getFontTexture().bind();
     m.draw();
     bigfont.getFontTexture().unbind();
     cam[1].end();
     secondScreenbackgroundFbo.end();
     */
    
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    cam[1].begin(viewBack);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    
    /* ofSetColor(255,0,0);
     for (int i=0;i<movingWords.size();i++){
     ofVec3f t;
     t.set(movingWords[i]->getDockPoint());
     ofDrawBox(t, 10);
     }*/
    
    cam[1].end();
    
}




// CAROUSSEL STUFF -> ANIMATION
void SceneManager::carousselEvent(CarousselEvent &e){
    if(e.message=="STOP"){
        if(e.id>0){
            Letter *l=cms[e.id].getLastElementPointer();
            if(l!=nullptr){
                cms[e.id-1].addMovement(l);
            }
        }
        
        if(e.id==0){
            Letter *l=cms[e.id].getLastElementPointer();
            auto it = std::find(letters.begin(), letters.end(), l);
            if (it != letters.end()) {
                int i= it - letters.begin();
                if(i>0)letters[i-1]->setBRemove(true);
            }
        }
        
    }
    
    
    if(e.message=="START"){
        if(e.id>0){
            //cms[e.id-1].addMovement(cms[e.id].getLastElementChar());
        }
    }
    
    
    if(e.message=="BUFFER EMPTY"){
        if(e.id==cms.size()-1){
            bIsReadyForData=true;
            
        }
    }
}







bool SceneManager::isInitialized(){
    return initialized;
}




void SceneManager::addDataFromBuffer(){
    
    if(messageBuffer.size()==0){
        bIsReadyForData=true;
        return;
    }
    
    
    message m=messageBuffer[0];
    messageBuffer.erase(messageBuffer.begin());
    
    
    User * u=getUserByUsername(m.username);
    if(u==nullptr){
        u=new User();
        u->setup();
        u->setUserName(m.username);
        cout<<"new user "<<u->getUserName()<<endl;

    }else{
        cout<<"add to user "<<u->getUserName()<<endl;
    }
    
    Fragment * f=new Fragment();
    f->setup();
    f->setFragmentId(m.uuid);
    f->setUserPointer(u);
    vector<string> split;
    split = ofSplitString(m.text, " ");
    
    for (auto word : split){
        Word * w=new Word();
        w->setup(wordcounter);
        w->setData(word);
        int lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(10000,50000));
        w->setLifeTime(lifeTime);
        w->setFragmentPointer(f);
        w->setUserPointer(u);
        
      /*  float r=ofRandom(0,1);
        if(r<0.2 && word!=" ")w->setIsSuggestion(true);*/
        
        for (auto ss : word){
            char c = ss;
            Letter * l =new Letter();
            l->setFont(&font);
            l->setData(c);
            l->setWordId(wordcounter);
            l->setWordPointer(w);
            l->setFragmentPointer(f);
            l->setUserPointer(u);
            letters.push_back(l);
            cms[cms.size()-1].addMovement(letters[letters.size()-1]);
            w->registerLetter(l);
            f->registerLetter(l);
            u->registerLetter(l);
        }
        
        // ADD SPACE
        Letter * l =new Letter();
        l->setFont(&font);
        l->setData(' ');
        l->setWordId(wordcounter);
        l->setWordPointer(w);
        l->setFragmentPointer(f);
        l->setUserPointer(u);
        
        letters.push_back(l);
        cms[cms.size()-1].addMovement(letters[letters.size()-1]);
        
        w->registerLetter(l);
        f->registerLetter(l);
        u->registerLetter(l);
        
        words.push_back(w);
        
        f->registerWord(w);
        u->registerWord(w);
        
        wordcounter++; // debug id
        
    }
    fragments.push_back(f);
    u->registerFragment(f);
    
    users.push_back(u);
    
}


void SceneManager::addData(string _s, int _fragmentId){
    Fragment * f=new Fragment();
    f->setup();
    f->setFragmentId(_fragmentId);
    vector<string> split;
    split = ofSplitString(_s, " ");
    //cout<<_s<<split.size()<<endl;
    
    for (auto word : split){
        Word * w=new Word();
        w->setup(wordcounter);
        w->setData(word);
        int lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(10000,50000));
        w->setLifeTime(lifeTime);
        w->setFragmentPointer(f);
        
        float r=ofRandom(0,1);
        if(r<0.2 && word!=" ")w->setIsSuggestion(true);
        
        
        for (auto ss : word){
            char c = ss;
            Letter * l =new Letter();
            l->setFont(&font);
            l->setData(c);
            l->setWordId(wordcounter);
            l->setWordPointer(w);
            l->setFragmentPointer(f);
            letters.push_back(l);
            cms[cms.size()-1].addMovement(letters[letters.size()-1]);
            w->registerLetter(l);
            f->registerLetter(l);
        }
        
        // ADD SPACE
        Letter * l =new Letter();
        l->setFont(&font);
        l->setData(' ');
        l->setWordId(wordcounter);
        l->setWordPointer(w);
        l->setFragmentPointer(f);
        
        letters.push_back(l);
        cms[cms.size()-1].addMovement(letters[letters.size()-1]);
        w->registerLetter(l);
        f->registerLetter(l);
        words.push_back(w);
        
        f->registerWord(w);
        wordcounter++; // debug id
        
    }
    fragments.push_back(f);
}



/*
void SceneManager::addWord(string _s){
    Word *w;
    w->setup(words.size());
    w->setData(_s);
    words.push_back(w);
}
*/





void SceneManager::addMovingWord(Word *_w){
   
    _w->setIsDrawn(false);
    MovingWords *mw=new MovingWords();
    mw->setup();
    mw->setLifeSpan(ofRandom(70000,30000));
    
    /*
    if(movingWordPositions.size()>0){
        int i=int(ofRandom(movingWordPositions.size()));
        mw->setTarget(movingWordPositions[i]);
        movingWordPositions.erase(movingWordPositions.begin()+i);
    }*/
    
    // mw->myColor=_w->getBackgroundColor();
    mw->setFont(&bigfont);
    mw->setData(_w->getMyData());
    
    mw->getUserName();
    
    //Send info to soundmanager -> hacky
    SoundM->user1vowelcount.set(mw->getSyllablescount());
    SoundM->user1sylcont1.set(mw->getVowelcount());
    
    //set position an initial speed
    mw->setStartPosition(_w->getPosition());
    mw->setInitVelocity(_w->getVelocity());
    mw->startMoving();
    movingWords.push_back(mw);
    
}






void SceneManager::makeMovingWordByFragmentId(int _id, int _wordIndex){
    Fragment *f=getFragmentById(_id);
    //cout<<f->getNumWords()<<endl;
    Word *w =f->getWordByIndex(_wordIndex);
    //cout<<w->getIndex()<<endl;
    if(w!=nullptr){
        addMovingWord(w);
    }
}


Fragment* SceneManager::getFragmentById(int _id){
    for(auto fragment:fragments){
        if (_id==fragment->getFragmentId()){
            return fragment;
            break;
        }
    }
    return nullptr;
}



void SceneManager::makeRandomMovingWord(){
    int n=int(ofRandom(0,fragments.size()));
    // cout<<fragmentid<<endl;
    Fragment *f=fragments[n]; //getFragmentById(fragmentid);
    cout<<f->getFragmentId()<<endl;
    int wI=int(ofRandom(f->getNumWords()));
    cout<<"Word index "<<wI;
    Word *w =f->getWordByIndex(wI);
    cout<<"is on screen"<<w->checkIsOnScreen()<<endl;
    if(w!=nullptr && w->checkIsOnScreen() && !w->getIsLocked()){
        w->myColor=ofColor(0,0,0);
        w->lock(true);
        addMovingWord(w);
        cout<<"making moving word"<<endl;
    }else {
        cout<<"another try"<<endl;
        makeRandomMovingWord();
    }
}


bool SceneManager::tryMakeMovingWordByFragmentId(int _id, int _wordIndex){
    bool canDo=false;
    Fragment *f=getFragmentById(_id);
    if(f!=nullptr){
        //  cout<<f->getFragmentId()<<endl;
        Word *w =f->getWordByIndex(_wordIndex);
        if(w!=nullptr && w->checkIsOnScreen()){
            w->myColor=ofColor(0,0,0);
            addMovingWord(w);
            //cout<<"making moving word from actionbuffer"<<endl;
            canDo=true;
        }else {
            
        }
    }
    return canDo;
}





User * SceneManager::getUserByUsername(string _name){
    
    for(auto user:users){
        if (_name==user->getUserName()){
            return user;
            break;
        }
    }
    return nullptr;
    
    
}




Word * SceneManager::getWordByFragmentId(int _id, int _wordIndex){
    bool canDo=false;
    Fragment *f=getFragmentById(_id);
    if(f!=nullptr){
        Word *w =f->getWordByIndex(_wordIndex);
        if(w!=nullptr && w->checkIsOnScreen()){
            canDo=true;
            return w;
        }else {
            return nullptr;
        }
    }else{
        return nullptr;
    }
}





void SceneManager::setDebug(bool _debug){
    debug=_debug;
    for(int i=0;i<cms.size();i++){
        cms[i].setDebugDraw(_debug);
    }
    
}


bool SceneManager::shouldRemoveMovingWord(MovingWords *mv){
    if(!mv->checkIsAlive()) return true;
    bool bRemove = false;
    
    // get the rectangle of the OF world
    ofRectangle rec = ofGetCurrentViewport();
    
    /*    if(rec.inside(mv->getPosition()) == false) {
     mv->setIsAlive(false);
     bRemove = true;
     }*/ //not working
    return bRemove;
}


bool SceneManager::shouldRemoveLetter(Letter *l){
    return l->getBRemove();
    
}





void SceneManager::addMessage(message _m){
    messageBuffer.push_back(_m);
    // cout<<"Message Buffer Size: "<<messageBuffer.size()<<endl;
    
}


void SceneManager::addAction(action _a){
    actionBuffer.push_back(_a);
    // cout<<"Action Buffer Size: "<<actionBuffer.size()<<endl;
    
}



