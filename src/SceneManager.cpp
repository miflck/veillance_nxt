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


void SceneManager::initializeCaroussel(){
    
    
    //make sure not two following points have same speed;
    for (int i=0;i<numEntrypoints;i++){
        float s=ofRandom(minspeed,maxspeed);
        /*if(i>0 && s==speeds[i-1]){
         int d=int(ofRandom(speeds[i-1]-1,maxspeed-s));
         if(d==0)d=int(ofRandom(1,maxspeed-s));
         s+=d;
         
         }*/
        cout<<"s"<<s<<endl;
        speeds.push_back(s);
    }
    
    int linesPerManager=numLines;
    int numManager=floor(ofGetHeight()/(linesPerManager*CCheight));
    int managerheight=linesPerManager*CCheight;
    cout<<"numManager "<<numEntrypoints<<endl;
    for(int i = 0; i < numEntrypoints; i++){
        
        CarousselStackManager * sm = new CarousselStackManager();
        sm->minspeed=speeds[i];
        
        ofVec2f position;
        position.set(-viewportwidth,(i*managerheight));
        float p=ABS((managerheight/2)-((i*CCheight)));
        
        sm->setup(i,position,viewportwidth,managerheight);
        csm.push_back(sm);
        
        registerStackManagerReady(csm[csm.size()-1]);
        
    }




}


void SceneManager::initialize(int width, int height, int _entrypoints , int _linesPerPoint) {
    
    initialized=true;
    cout<<"init SceneManager"<<endl;
    
    
    CCwidth=15;
    CCheight=20;
    minspeed=ofRandom(1,3);
    
    

    
    
    font.load("FoundersGroteskMonoBold.ttf", CCwidth);
    bigfont.load("FoundersGroteskMonoBold.ttf", 60);
    
    viewportwidth=width;
    viewportheight=height;
    // CAROUSSEL
    //These are the animationcontrollers of the background. Each one controlls a Line
    
    
    numEntrypoints=_entrypoints;
    numLines=_linesPerPoint;
    minspeed=2;
    maxspeed=5;

    
    initializeCaroussel();
    
    
    
    
    
    
    
    
    // Event listener for the Carousselevents. Tells the Scenemanager when to feed the buffer or move one line up etc
    ofAddListener(CarousselEvent::events, this, &SceneManager::carousselEvent);
    
    
    // CAMERA AND VIEWPORTS
    
    //Viewports
    viewFront.x = 0;
    viewFront.y = 0;
    viewFront.width = viewportwidth;
    viewFront.height = ofGetHeight();
    
    viewBack.x = ofGetWidth()/2;
    viewBack.y = 0;
    viewBack.width = viewportwidth;
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
    
    
    backgroundcolor=ofColor(0);
    color1=ofColor(0);
    color2=ofColor(0);
    
    blur.setup(viewportwidth,viewportheight);

    
    png.load("png-01.png");
}




void SceneManager::update(){
    
    // check if a stackmanager has capacity to add new message
    if(stackManagerBuffer.size()>0 && messageBuffer.size()>0){
        CarousselStackManager * sm=stackManagerBuffer[0];
        stackManagerBuffer.erase(stackManagerBuffer.begin());
        addMessageFromBuffer(sm);
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
    
    for(auto word:words){
        word->update();
    }
    
    for(auto fragment:fragments){
        fragment->update();
    }
    
    
    for(auto user:users){
        user->update();
    }

  
    // UPDATE CAROUSSEL
    for(int i=0;i<csm.size();i++){
        csm[i]->update();
    }
    
  
  
    
    
    
    //UPDATE
 
    

    
    
    // ADD BLACK SQUARE TO BACKGROUNDCOLOR
    backgroundFbo.begin();
    ofSetColor(0,0,0,1);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    ofEnableAlphaBlending();
   //if(ofGetFrameNum()%100==0) ofDrawRectangle(0, 0, backgroundFbo.getWidth(), backgroundFbo.getHeight());
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

void SceneManager::checkRemove(){
    // REMOVE STUFF FROM SCREEN AND MEMORY -> Wrap that up?
    
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
    
    
    
  /*  int size=letters.size();
    for (int i=0;i<size;i++){
        if(letters[i]->getBRemove()){
            cout<<"delete "<<letters[i]<<endl;
            
            letters[i]->myWordPointer->unregisterLetter(letters[i]);
            letters[i]->myFragmentPointer->unregisterLetter(letters[i]);
            letters[i]->myUserPointer->unregisterLetter(letters[i]);
            
            delete (letters[i]);
            letters.erase(letters.begin()+i);
            
            
            
        }
    }*/
    
    int size=letters.size();
    for (int i=letters.size()-1;i>=0;i--){
        if(letters[i]->getBRemove()){
           // cout<<"delete "<<letters[i]<<endl;
            
     /*       letters[i]->myWordPointer->unregisterLetter(letters[i]);
            letters[i]->myFragmentPointer->unregisterLetter(letters[i]);
            letters[i]->myUserPointer->unregisterLetter(letters[i]);*/
            
            delete (letters[i]);
            letters.erase(letters.begin()+i);
            
            
            
        }
    }

    




}

void SceneManager::draw(){
   // ofColor bg=backgroundcolor;
   // bg.setBrightness(50);
    //ofBackground(bg);
    
   
    backgroundFbo.begin();
    ofSetColor(backgroundcolor);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    ofEnableAlphaBlending();
   // ofDrawRectangle(0, 0, backgroundFbo.getWidth(), backgroundFbo.getHeight());
    ofDisableBlendMode();
    backgroundFbo.end();

    for(int i=0;i<csm.size();i++){
        csm[i]->draw();
    }
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // background
    if(debug) backgroundFbo.draw(0,0);
    secondScreenbackgroundFbo.draw(viewportwidth,0);
    
    cam[0].begin(viewFront);
    
    
    //backgroundFbo.begin();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    /*ofColor c = ofColor(0);
    if(!bIsExploding){
     c=cms[cms.size()-1].containers[cms[cms.size()-1].containers.size()-1].getBackgroundColor();
    c.setBrightness(200);
    }
    color1.lerp(c,0.01);
    ofSetColor(color1);
   
    
    
    png.draw(viewportwidth-1800, viewportheight-1300,3000,3000);
    
    
     c=cms[cms.size()-1].containers[0].getBackgroundColor();
    c.setBrightness(200);

    color2.lerp(c,0.01);
        ofSetColor(color2);
    */
        //png.draw(-1000, viewportheight-1000,2000,2000);

    
    
    
    if(!bIsExploding){
        
        ofColor c;
        float  h=ofMap(messageBuffer.size(), 0, 500, 0, 255);
        
        float  s=ofMap(messageBuffer.size(), 0, 500, 0, 255);
        float  b=ofMap(messageBuffer.size(), 0, 500, 0, 255);

        
        c.setHsb(0, 255, b);

        
        //backgroundcolor.lerp(c,d);
        
        backgroundcolor.lerp(c,0.02);
        
    //User * u=getUserWithMostLetters();
    /*if(u!=nullptr) {
        ofColor c=u->getBackgroundColor();
        c.setBrightness(160);
        //if(ofGetFrameNum()%10==0)backgroundcolor.lerp(c,0.02);
        backgroundcolor.lerp(c,0.01);
        
        // cout<<backgroundcolor<<endl;
        //backgroundcolor=u->getBackgroundColor();
        
    }*/
    }else{
     backgroundcolor.lerp(ofColor(0),0.01);
    
    }
    

    ofSetColor(backgroundcolor);
    
    //png.draw(-2000, -2000,4000,4000);
    
    

  //  backgroundFbo.end();
    

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
       // cout<<letter->getData()<<" "<<letter->myWordPointer->getIndex()<<" "<<letter->myWordPointer->myFragmentPointer->getFragmentId()<<endl;
       // letter->myWordPointer->myFragmentPointer->getFragmentId();
        letterMesh.append(letter->getUpdatedVboMesh());
    }
    font.getFontTexture().bind();
    letterMesh.draw();
    font.getFontTexture().unbind();
    
    ofPushStyle();
    // moving words mesh
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofVboMesh m;
    for(auto movingWord:movingWords){
        m.append(movingWord->getUpdatedVboMesh());
    }
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
   
    ofPopStyle();
    
   /* for(auto cs:csm){
        cs->draw();
    }*/
    
    
    
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
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    cam[1].begin(viewBack);
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);

   /* for(auto mw:movingWords){
        ofVec3f p=mw->getPosition();
        ofSetColor(mw->myColor,5);
        
        png.draw(p.x-1000, p.y-1000,p.z,2000,2000);
    }*/
    

    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    ofPopStyle();
    /* ofSetColor(255,0,0);
     for (int i=0;i<movingWords.size();i++){
     ofVec3f t;
     t.set(movingWords[i]->getDockPoint());
     ofDrawBox(t, 10);
     }*/
    
    cam[1].end();
    
    
    
    
    checkRemove();

    
    
    
}




// CAROUSSEL STUFF -> ANIMATION
void SceneManager::carousselEvent(CarousselEvent &e){
   /*
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
        
    }*/
    
    /*
    
    if(e.message=="EXPLODE"){
       reset();
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
    }*/
    
    
    
}







bool SceneManager::isInitialized(){
    return initialized;
}




// one of the Stack managers is ready. add message from buffer
void SceneManager::addMessageFromBuffer(CarousselStackManager * _s){
   /* if(messageBuffer.size()==0){
        bIsReadyForData=true;
        return;
    }*/
    
    message m=messageBuffer[0];
    _s->addMessage(m);
    messageBuffer.erase(messageBuffer.begin());
}




// Old adding method. not used. doing it now word by word from stackmanager!
void SceneManager::addDataFromBuffer(CarousselStackManager * _s){
    
    CarousselStackManager * sm =_s;
    
    /*if(messageBuffer.size()==0){
        bIsReadyForData=true;
        return;
    }*/
    
    bool isUserNew=false;
    message m=messageBuffer[0];
    messageBuffer.erase(messageBuffer.begin());

    User * u=getUserByUsername(m.username);
    if(u==nullptr){
        u=new User();
        u->setup();
        u->setUserName(m.username);
        int id=users.size();
        u->setUserId(id);
        cout<<"new user "<<u->getUserName()<<" id "<<id<<endl;
        isUserNew=true;
        
    }else{

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
        
        
        for (auto ss : word){
            char c = ss;
            Letter * l =new Letter();
            l->setFont(&font);
            l->setData(c);
            l->setWordId(wordcounter);
            l->setWordPointer(w);
            l->setFragmentPointer(f);
            l->setUserPointer(u);
            
            lettermap[l]=l;
            sm->addMovement(lettermap[l]);
            
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
        
        lettermap[l]=l;
        sm->addMovement(lettermap[l]);
        
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
    
    //only push new users
    if(isUserNew){
        users.push_back(u);
    }
    
    //cout<<" num letters "<<letters.size()<<endl;
}





//------------------- Add word to system -----------------------------------
void SceneManager::addWordFromManager(CarousselStackManager *_s, message _m){
    
    CarousselStackManager * sm =_s;
    // cout<<sm->cms.size()<<endl;
    
    /*  if(messageBuffer.size()==0){
     bIsReadyForData=true;
     return;
     }*/
    
    
    
    bool isUserNew=false;
    bool isFragmentNew=false;

    message m=_m;
    
    User * u=getUserByUsername(m.username);
    if(u==nullptr){
        u=new User();
        u->setup();
        u->setUserName(m.username);
        int id=users.size();
        u->setUserId(id);
        cout<<"new user "<<u->getUserName()<<" id "<<id<<endl;
        isUserNew=true;
        
    }else{
    }
    
     Fragment *f=getFragmentById(m.uuid);
    if(f==nullptr){
        f=new Fragment();
        f->setup();
        f->setFragmentId(m.uuid);
        u->registerFragment(f);
        f->setUserPointer(u);
        isFragmentNew=true;
        cout<<" ********* new Fragment "<<endl;
        }

    
    //cout<<"user "<<u->getUserName()<<" "<<f->getFragmentId()<<endl;
    int wIndex=f->getNumWords();
    
    string myword=_m.text;
        Word * w=new Word();
        w->setup(wIndex);
        w->setData(myword);
        int lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(10000,50000));
        w->setLifeTime(lifeTime);
        w->setFragmentPointer(f);
        w->setUserPointer(u);
    
        for (auto ss : myword){
            char c = ss;
            Letter * l =new Letter();
            l->setFont(&font);
            l->setData(c);
            l->setup();

            l->setWordId(wIndex);
            l->setWordPointer(w);
            l->setFragmentPointer(f);
            l->setUserPointer(u);
            
            lettermap[l]=l;
            sm->addMovement(lettermap[l]);
            
            w->registerLetter(l);
            f->registerLetter(l);
            u->registerLetter(l);
        }
        
        // ADD SPACE
        Letter * l2 =new Letter();
        l2->setFont(&font);
    l2->setup();

        l2->setData(' ');
        l2->setWordId(wIndex);
        l2->setWordPointer(w);
        l2->setFragmentPointer(f);
        l2->setUserPointer(u);
        
        lettermap[l2]=l2;
        sm->addMovement(lettermap[l2]);
    
        w->registerLetter(l2);
        f->registerLetter(l2);
        u->registerLetter(l2);
        
        words.push_back(w);
        
        f->registerWord(w);
        u->registerWord(w);
        
       // wordcounter++; // debug id
   
    
     if(isFragmentNew){
         fragments.push_back(f);
         u->registerFragment(f);
     }
    
    //only push new users
    if(isUserNew){
        users.push_back(u);
    }
    
}




/*
void SceneManager::addData(string _s, int _fragmentId){
    
    
    bool isUserNew=false;
    vector<string> split;
    split = ofSplitString(_s, " ");
    
    User * u=getUserByUsername(split[0]);
    if(u==nullptr){
        u=new User();
        u->setup();
        u->setUserName(split[0]);
        int id=users.size();
        u->setUserId(id);
        cout<<"new user "<<u->getUserName()<<" id "<<id<<endl;
        isUserNew=true;
        
    }else{
        cout<<"add to user "<<u->getUserName()<<" id "<<u->getUserId()<<endl;
    }
    
    Fragment * f=new Fragment();
    f->setup();
    f->setFragmentId(_fragmentId);
    f->setUserPointer(u);
    
    for (auto word : split){
        Word * w=new Word();
        w->setup(wordcounter);
        w->setData(word);
        int lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(10000,50000));
        w->setLifeTime(lifeTime);
        w->setFragmentPointer(f);
        w->setUserPointer(u);

        
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
    
    //only push new users
    if(isUserNew){
        users.push_back(u);
    }

   }

*/



void SceneManager::addMovingWord(Word *_w){
   
    _w->setIsDrawn(false);
    MovingWords *mw=new MovingWords();
    mw->setup();
    mw->myColor=ofColor(_w->getBackgroundColor(),180);
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
    
    User *u= _w->getUserPointer();
    u->registerMovingWord(mw);
    mw->setUserPointer(u);
    
       /*
    string n=u->getUserName();
    int i=getUserIndexByUsername(n);
 
    
    switch (i) {
        case 0:
            //Send info to soundmanager -> hacky
            SoundM->user1vowelcount.set(mw->getSyllablescount());
            SoundM->user1sylcont1.set(mw->getVowelcount());
            break;
            
        case 1:
            //Send info to soundmanager -> hacky
            SoundM->user2vowelcount.set(mw->getSyllablescount());
            SoundM->user2sylcont1.set(mw->getVowelcount());
            break;
            
        case 2:
            //Send info to soundmanager -> hacky
            SoundM->user3vowelcount.set(mw->getSyllablescount());
            SoundM->user3sylcont1.set(mw->getVowelcount());
            break;
            
        default:
            break;
    }
    
    */
   

    
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
    int n=int(ofRandom(0,fragments.size()-1));
    // cout<<fragmentid<<endl;
    Fragment *f=fragments[n]; //getFragmentById(fragmentid);
   // cout<<f->getFragmentId()<<endl;
    int wI=int(ofRandom(f->getNumWords()));
    //cout<<"Word index "<<wI;
    Word *w =f->getWordByIndex(wI);
    //cout<<"is on screen"<<w->checkIsOnScreen()<<endl;
    if(w!=nullptr && w->checkIsOnScreen() && !w->getIsLocked()){
        w->myColor=ofColor(0,0,0);
        w->lock(true);
        addMovingWord(w);
       // cout<<"making moving word"<<endl;
    }else {
      //  cout<<"another try"<<endl;
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

int SceneManager:: getUserIndexByUsername(string _name){
    
    for(int i=0;i<users.size();i++){
        if (_name==users[i]->getUserName()){
            return i;
            break;
        }
    }
    return -1;

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
 /*   for(int i=0;i<cms.size();i++){
        cms[i].setDebugDraw(_debug);
    }*/
    
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




// Add message to buffer;
void SceneManager::addMessage(message _m){
    messageBuffer.push_back(_m);
    // cout<<"Message Buffer Size: "<<messageBuffer.size()<<endl;
    
}


void SceneManager::addAction(action _a){
    actionBuffer.push_back(_a);
    // cout<<"Action Buffer Size: "<<actionBuffer.size()<<endl;
    
}


User * SceneManager::getUserWithMostLetters(){
    int num=0;
    User * u =nullptr;
    for (int i=0;i<users.size();i++){
        int n=users[i]->getNumLetters();
       // cout<<n<<endl;
        if(n>num){
            u=users[i];
            num=n;
        }
       
    }

    return u;
}


void SceneManager::explode(){
    bIsExploding=true;
    // UPDATE CAROUSSEL
  /*  for(int i=0;i<cms.size();i++){
        cms[i].explode();
    }
   */
    
    for(int i=0;i<csm.size();i++){
        csm[i]->explode();
    }
    
    for(int i=0;i<words.size();i++){
        words[i]->explode();
    }

}

void SceneManager::reset(){
    cout<<"reset"<<endl;

    
    messageBuffer.clear();
    actionBuffer.clear();
    

  
    for (int i =0; i< users.size();i++)
    {
        delete (users[i]);
    }
    users.clear();
    
    for (int i =0; i< movingWords.size();i++)
    {
        delete (movingWords[i]);
    }
    movingWords.clear();
    
    for (int i =0; i< fragments.size();i++)
    {
        delete (fragments[i]);
    }
    fragments.clear();
    for (int i =0; i< words.size();i++)
    {
        delete (words[i]);
    }
      words.clear();
    
    for (int i =0; i< letters.size();i++)
    {
        delete (letters[i]);
    }
    letters.clear();
    
    cms.clear();
    
    for (int i =0; i< csm.size();i++)
    {
        delete (csm[i]);
    }
    
    csm.clear();
    csm.clear();
    
    initializeCaroussel();
    
    bIsExploding=false;


}


void SceneManager::registerStackManagerReady(CarousselStackManager *_s){
    CarousselStackManager * s=_s;
    stackManagerBuffer.push_back(s);

}

void SceneManager::unregisterLetter(Letter *l){
    
  //  cout<<"unregister in SceneManager "<<l <<endl;
    /*for(int i=0;i<csm.size();i++){
        csm[i]->unregisterLetter(l);
    }*/
    l->myWordPointer->unregisterLetter(l);
   l->myFragmentPointer->unregisterLetter(l);
 l->myUserPointer->unregisterLetter(l);
    
   

}

