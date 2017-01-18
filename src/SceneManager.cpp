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
    for (int i=0;i<entrypoints;i++){
        float r=ofRandom(minspeed,maxspeed);
        
       float s= roundf(r*100)/100;
              cout<<"s"<<s<<endl;
        speeds.push_back(s);
    }
    
    int numManager=floor(ofGetHeight()/(linesPerPoint*CCheight));
     managerheight=linesPerPoint*CCheight;
    cout<<"numManager "<<entrypoints<<endl;
    for(int i = 0; i < entrypoints; i++){
        CarousselStackManager * sm = new CarousselStackManager();
        sm->minspeed=speeds[i];
        ofVec2f position;
        position.set(0,(i*managerheight));
        float p=ABS((managerheight/2)-((i*CCheight)));
        sm->setup(i,position,viewportwidth,managerheight);
        csm.push_back(sm);
        entrypointBackgrounds.push_back(&png);
        registerStackManagerReady(csm[csm.size()-1]);
}

    int wordsInMessageBuffer=0;
    for(int i=0;i<messageBuffer.size();i++){
        wordsInMessageBuffer+=messageBuffer[i].wordcount;
    }
    cout<<"messagebuffer "<<wordsInMessageBuffer<<endl;

    



}


void SceneManager::initialize() {
    
    png.load("png-01.png");

    
    initialized=true;
    cout<<"init SceneManager"<<endl;
    
    
    //CCwidth=15;
    //CCheight=20;
   // minspeed=ofRandom(1,3);
    
    

    
    
    font.load("FoundersGroteskMonoBold.ttf", CCwidth,true,true);
   // font.load("TwoPointH-128Medium.ttf", CCwidth,true,true);
    bigfont.load("FoundersGroteskMonoBold.ttf", bigfontsize,true, true);
   // bigfont.load("TwoPointH-128Medium.ttf", bigfontsize,true, true);

    

    
    
   // viewportwidth=width;
   // viewportheight=height;
    // CAROUSSEL
    //These are the animationcontrollers of the background. Each one controlls a Line
    
    
    minspeed=1.5;
    maxspeed=7;

    
    initializeCaroussel();
    
    
    
    //Vertical Caroussel
    int h=50;
    h=CCheight;
    ofVec2f position;
    position.set(3*viewportwidth+viewportwidth/2,-h);
    vC.setPosition(position);
    vC.setFont(&font);
    vC.setup(position, 200, viewportheight+2*h, 200, h);
    
    
    
    
    // Event listener for the Carousselevents. Tells the Scenemanager when to feed the buffer or move one line up etc
    ofAddListener(CarousselEvent::events, this, &SceneManager::carousselEvent);
    
    
    // CAMERA AND VIEWPORTS
    
    //Viewports
    viewFront.x = viewportwidth;
    viewFront.y = 0;
    viewFront.width = viewportwidth;
    viewFront.height = ofGetHeight();
    
    
    viewLeft.x = 0;
    viewLeft.y = 0;
    viewLeft.width = viewportwidth;
    viewLeft.height = ofGetHeight();
    
    viewRight.x = viewportwidth*2;
    viewRight.y = 0;
    viewRight.width = viewportwidth;
    viewRight.height = ofGetHeight();
    
    
    viewBack.x = viewportwidth*3;
    viewBack.y = 0;
    viewBack.width = viewportwidth;
    viewBack.height = ofGetHeight();
    
    // Camera
    cam[0].setVFlip(true);
    cam[0].setFov(60);
    float d=cam[0].getImagePlaneDistance(viewFront);

    cam[0].enableOrtho();
    cam[0].setPosition(-viewportwidth/2, ofGetHeight()/2, d);
    
    
    cam[1].setVFlip(true);
    cam[1].setNearClip(10);
    cam[1].enableOrtho();
    cam[1].setPosition(-viewportwidth/2, ofGetHeight()/2, d);
    
    cam[2].setVFlip(true);
    cam[2].setNearClip(10);
    cam[2].enableOrtho();
    cam[2].setPosition(-viewportwidth/2, ofGetHeight()/2, d);
    
    cam[3].setVFlip(true);
    cam[3].setNearClip(10);
    cam[3].enableOrtho();
    cam[3].setPosition(-viewportwidth/2, ofGetHeight()/2, d);

   // cam[3].pan(-90);
    
    
    cam[4].setVFlip(true);
    cam[4].setNearClip(10);
    cam[4].enableOrtho();

    cam[4].setPosition(-4.5*viewportwidth, ofGetHeight()/2, d);
    
    
    // BACKGROUNDCOLOR
    // Background FBO for Backgroundcolorstuff.
    backgroundFBO.allocate(width, ofGetHeight(),GL_RGBA);
//    backgroundFBO.allocate(viewportwidth, ofGetHeight(),GL_RGBA);

    backgroundFBO.begin();
    ofClear(25,255,255,0);
    backgroundFBO.end();
    
   
    
    backgroundFBO0.allocate(viewportwidth, ofGetHeight(),GL_RGBA);
    backgroundFBO0.begin();
    ofClear(0,0,0,0);
    backgroundFBO0.end();
   
    backgroundFBO1.allocate(viewportwidth, ofGetHeight(),GL_RGBA);
    backgroundFBO1.begin();
    ofClear(0,0,0,0);
    backgroundFBO1.end();
    
    backgroundFBO2.allocate(viewportwidth, ofGetHeight(),GL_RGBA);
    backgroundFBO2.begin();
    ofClear(0,0,0,0);
    backgroundFBO2.end();
    
    
    backgroundFBO3.allocate(viewportwidth, ofGetHeight(),GL_RGBA);
    backgroundFBO3.begin();
    ofClear(0,0,0,0);
    backgroundFBO3.end();
    
    ofEnableAlphaBlending();
    
    
    
    
    backgroundcolor=ofColor(0);
    color1=ofColor(0);
    color2=ofColor(0);
    

    clusterpointright.position.set(2*viewportwidth-300,ofGetHeight()/2,-500);
    clusterpointleft.position.set(-viewportwidth+300,ofGetHeight()/2,-500);

    
   
    
}




void SceneManager::update(){
    
    
    int wordsInMessageBuffer=0;
    for(int i=0;i<messageBuffer.size();i++){
        wordsInMessageBuffer+=messageBuffer[i].wordcount;
    }
    totalWordsInBuffer=stackmanagertotalbuffer+wordsInMessageBuffer;
    
    if(totalWordsInBuffer>maxWordsInBuffer && !bIsExploding)STM->explode();
    
    
    vC.update();
    
    if(bShouldReset==true)reset();
    
    
    if(priorityMessageBuffer.size()>0){
        if(stackManagerBuffer.size()>0){
            CarousselStackManager * sm=stackManagerBuffer[0];
            stackManagerBuffer.erase(stackManagerBuffer.begin());
            addMessageFromPriorityBuffer(sm);
        }else{
            
            addMessageFromPriorityBuffer(getStackmanagerWithSmallestBuffer());
        
        }
    }
    
    
    
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
    
    // Check if we have dns to add
    if(dnsBuffer.size()>0){
        for (int i=0;i<dnsBuffer.size();i++){
            dns d=dnsBuffer[i];
            addDNS(d.text);
            dnsBuffer.erase(dnsBuffer.begin()+i);
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

    stackmanagertotalbuffer=0;

    // UPDATE CAROUSSEL
    for(int i=0;i<csm.size();i++){
        csm[i]->update();
       // cout<<i<<" "<<stackmanagertotalbuffer<<" "<<csm[i]->getStringsize()<<endl;
        stackmanagertotalbuffer+=csm[i]->getStringsize();
    }
    
  
  
    
    
    //UPDATE
 
    

    if(bDrawTrails){

    
    // ADD BLACK SQUARE TO BACKGROUNDCOLOR
    backgroundFBO.begin();
    ofSetColor(0,0,0,fadeAlpha);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableAlphaBlending();
    if(ofGetFrameNum()%fadetime==0) ofDrawRectangle(0, 0, backgroundFBO.getWidth(), backgroundFBO.getHeight());
    backgroundFBO.end();
        
    
    
    backgroundFBO0.begin();
    ofEnableAlphaBlending();

    ofSetColor(0,0,0,100);
    ofDrawRectangle(0, 0, backgroundFBO0.getWidth(), backgroundFBO0.getHeight());
    backgroundFBO0.end();
    
    backgroundFBO1.begin();
    ofEnableAlphaBlending();

    ofSetColor(0,0,0,clusterFadeAlpha);
     if(ofGetFrameNum()%clusterFadetime==0)ofDrawRectangle(0, 0, backgroundFBO1.getWidth(), backgroundFBO1.getHeight());
    backgroundFBO1.end();
    
    backgroundFBO2.begin();
    ofEnableAlphaBlending();

    ofSetColor(0,0,0,clusterFadeAlpha);
     if(ofGetFrameNum()%clusterFadetime==0)ofDrawRectangle(0, 0, backgroundFBO2.getWidth(), backgroundFBO2.getHeight());
    backgroundFBO2.end();
    
    backgroundFBO3.begin();
    ofEnableAlphaBlending();

    ofSetColor(0,0,0,clusterFadeAlpha);
     if(ofGetFrameNum()%clusterFadetime==0)ofDrawRectangle(0, 0, backgroundFBO3.getWidth(), backgroundFBO3.getHeight());
    backgroundFBO3.end();
    
    
    
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //Sound-> hacked draft constrain to 100 Words
   /* if(users.size()>0){
        
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
    */
    
    
    
    
    
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

    
    //sinTheta+=0.02;
    
    
    float s=sin(sinTheta);
    float s2=cos(sinTheta);


    clusterpointleft.position.x-=s;
   // clusterpointleft.position.y+=s2;

  //  cout<<"sin "<<sinTheta<<clusterpointleft.position<<endl;



}

void SceneManager::draw(){
 
    vC.draw();
 

    for(int i=0;i<csm.size();i++){
        csm[i]->draw();
    }
    
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofColor usercolor;
    usercolor.setHsb(0,0,0);
    
    if(bGetMostUser){
    if(users.size()>0){
        User *u=getUserWithMostWordsInBuffer();
        if(u!=nullptr)
            usercolor=getUserWithMostWordsInBuffer()->getBackgroundColor();
    }
    if(!bIsExploding){
        ofColor c;
        float  h=ofMap(totalWordsInBuffer, 0, maxWordsInBuffer, 0, 255);
        float  s=ofMap(totalWordsInBuffer, 0, maxWordsInBuffer, 0, 255);
        float  b=ofMap(totalWordsInBuffer, 0, maxWordsInBuffer, 0, 255);
        c.setHsb(usercolor.getHue(), s, b);
        backgroundcolor.lerp(c,0.05);
    }else{
        backgroundcolor.lerp(ofColor(0),0.1);
        
    }
    ofSetColor(backgroundcolor,200);
    png.draw(0, -2000,4000,4000);
    png.draw(2000, -2000,4000,4000);


}
    
    
    
    /*
    
    STM->backgroundFBO0.begin();
    // ofSetColor(255,0,0);
    STM->cam[0].begin();
    
    letterMesh.clear();
    for(auto letter:letters){
        // cout<<letter->getData()<<" "<<letter->myWordPointer->getIndex()<<" "<<letter->myWordPointer->myFragmentPointer->getFragmentId()<<endl;
        // letter->myWordPointer->myFragmentPointer->getFragmentId();
        letterMesh.append(letter->getUpdatedVboMesh());
    }
    ofPushMatrix();
    ofTranslate(-viewportwidth,0);
    font.getFontTexture().bind();
    letterMesh.draw();
    font.getFontTexture().unbind();
    ofPopMatrix();
    STM->cam[0].end();
    STM->backgroundFBO0.end();
     */
    
    cam[0].begin(viewFront);


    //Entrypoint PNG
   
    /*
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,255);

ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255,0,0);
    
    int w=managerheight*4;
    for (int i=0;i<csm.size();i++){
        w=ofMap(csm[i]->getStringsize(),0,1200,managerheight*5,2000,true);
        ofColor c=csm[i]->getBackgroundColor();
       float a=ofMap(csm[i]->getStringsize(),0,100,0,80,true);

        ofSetColor(c,a);
        entrypointBackgrounds[i]->draw(csm[i]->getPosition().x+viewportwidth-w/2,csm[i]->getPosition().y+managerheight/1.5-w/2,w,w);
    }
    */
    

    

  
    
    
    // getting the lettermesh
    letterMesh.clear();
    for(auto letter:letters){
       // cout<<letter->getData()<<" "<<letter->myWordPointer->getIndex()<<" "<<letter->myWordPointer->myFragmentPointer->getFragmentId()<<endl;
       // letter->myWordPointer->myFragmentPointer->getFragmentId();
        letterMesh.append(letter->getUpdatedVboMesh());
    }
    ofPushMatrix();
    ofTranslate(1, 1);
    font.getFontTexture().bind();
    letterMesh.draw();
    font.getFontTexture().unbind();
    ofPopMatrix();
    

    
    
    
    ofVboMesh m;

    if(!bIsExploding){


    ofPushStyle();
    // moving words mesh
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(auto movingWord:movingWords){
        m.append(movingWord->getUpdatedVboMesh());
    }
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
   
    ofPopStyle();
    }
    
    
    

    
    
    //camFront.end();
    cam[0].end();
    
    
    

    
    
    if(bDrawTrails){
       backgroundFBO.begin();
        STM->cam[0].begin();
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofPushMatrix();
        ofTranslate(-viewportwidth/2-viewportwidth,0);
        bigfont.getFontTexture().bind();
        m.draw();
        bigfont.getFontTexture().unbind();
        
        ofSetColor(255,0,0);
        ofFill();
        ofDrawRectangle(clusterpointleft.position.x,clusterpointleft.position.y,50,50);

        
        ofPopMatrix();
        STM->cam[0].end();
        backgroundFBO.end();


        
        /*
        STM->backgroundFBO0.begin();
        // ofSetColor(255,0,0);
        STM->cam[0].begin();
        ofPushMatrix();
        ofTranslate(-viewportwidth,0);
        bigfont.getFontTexture().bind();
        m.draw();
        bigfont.getFontTexture().unbind();
        ofPopMatrix();
        STM->cam[0].end();
        STM->backgroundFBO0.end();
        
    
    STM->backgroundFBO1.begin();
    // ofSetColor(255,0,0);
    STM->cam[0].begin();
    ofPushMatrix();
    ofTranslate(-2*viewportwidth,0);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    ofPopMatrix();
    STM->cam[0].end();
    STM->backgroundFBO1.end();
    
    
    STM->backgroundFBO2.begin();
    // ofSetColor(255,0,0);
    STM->cam[0].begin();
    ofPushMatrix();
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    ofPopMatrix();
    STM->cam[0].end();
    STM->backgroundFBO2.end();
    
    
    STM->backgroundFBO3.begin();
    // ofSetColor(255,0,0);
    STM->cam[0].begin();
    ofPushMatrix();
     ofTranslate(viewportwidth,0);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(-3*viewportwidth,0);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    ofPopMatrix();
    
    
    STM->cam[0].end();
    STM->backgroundFBO3.end();
    */
    
    
    }

    
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
    /* ofSetColor(255,0,0);
     for (int i=0;i<movingWords.size();i++){
     ofVec3f t;
     t.set(movingWords[i]->getDockPoint());
     ofDrawBox(t, 10);
     }*/
    
    cam[1].end();
    
   /* camFront2.begin(viewRight);
    //cam[2].begin(viewRight);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
   // cam[2].end();
    camFront2.end();*/
    
    
   cam[2].begin(viewRight);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
     cam[2].end();
    
    cam[3].begin(viewLeft);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    cam[3].end();
    
    ofPushMatrix();

    cam[4].begin(viewBack);
    bigfont.getFontTexture().bind();
    m.draw();
    bigfont.getFontTexture().unbind();
    cam[4].end();
    ofPopMatrix();
    
    ofPopStyle();
    
    
    ofSetColor(255);
    ofEnableAlphaBlending();
    
   
    
   // if(!bIsExploding){
    
    if(bDrawTrails){
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(255,255,255,fboAlpha);
        backgroundFBO.draw(0,0);
        
        ofSetColor(255,255,255,255);

        ofEnableBlendMode(OF_BLENDMODE_ADD);

    backgroundFBO0.draw(viewportwidth,0);
    backgroundFBO1.draw(viewportwidth*2,0);
    backgroundFBO2.draw(0,0);
    backgroundFBO3.draw(viewportwidth*3,0);
    }
 //   }
    
    checkRemove();

    
    
}




// CAROUSSEL STUFF -> ANIMATION
void SceneManager::carousselEvent(CarousselEvent &e){
    
    
    if(e.message=="EXPLODE STOP"){
        explodestopcounter++;
        cout<<"explodestopcounter "<<explodestopcounter<<" "<<entrypoints*linesPerPoint<<" "<<bShouldReset<<endl;
        if(explodestopcounter==entrypoints*linesPerPoint){
           // reset();
            bShouldReset=true;
        }
    }
    
    
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
    message m=messageBuffer[0];
    _s->addMessage(m);
    messageBuffer.erase(messageBuffer.begin());
   std::random_shuffle ( messageBuffer.begin(), messageBuffer.end() );

}


// Overtake Messagebuffer for new User
void SceneManager::addMessageFromPriorityBuffer(CarousselStackManager * _s){
    message m=priorityMessageBuffer[0];
    _s->addMessage(m);
    priorityMessageBuffer.erase(priorityMessageBuffer.begin());
}



CarousselStackManager * SceneManager::getStackmanagerWithSmallestBuffer(){

    CarousselStackManager * sm = csm[0];
    for (int i=0;i<csm.size();i++){
        if(csm[i]->getStringsize()<sm->getStringsize()){
            sm=csm[i];
        }
    }
    return sm;
}



//------------------- Add word to system -----------------------------------
void SceneManager::addWordFromManager(CarousselStackManager *_s, message _m){
    
    CarousselStackManager * sm =_s;
    
    bool isUserNew=false;
    bool isFragmentNew=false;

    message m=_m;
    
    User * u=getUserByUsername(m.username);
    if(u==nullptr){
        int id=users.size();
        u=new User();
        u->setup();
        u->setUserName(m.username);
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
    
   // vC.addMovement(myword);

    
        Word * w=new Word();
        w->setup(wIndex);
        w->setData(myword);
    
    float r=ofRandom(1);
        if(r>0.95){
            w->setIsSuggestion(true);
        }
    
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
    
   
    
    float r=ofRandom(0,1);
    ofVec3f t;
    if(r>0.5){
      //  t=ofVec3f(viewportwidth+(2*viewportwidth/3),ofGetHeight()/2,0);
       // t=ofVec3f(2*viewportwidth-300,ofGetHeight()/2,0);
        t=clusterpointright.position;

    }else{
       // t=ofVec3f(-viewportwidth+300,ofGetHeight()/2,0);
        t=clusterpointleft.position;
        
        
    }
    
    mw->setTarget(t);
    mw->myColor=ofColor(_w->getBackgroundColor(),200);
    mw->setLifeSpan(ofRandom(15000,50000));
      //mw->setLifeSpan(1000);

    
    
  /*  if(movingWordPositions.size()>0){
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


// Add message to buffer;
void SceneManager::addPriorityMessage(message _m){
    priorityMessageBuffer.push_back(_m);
}


void SceneManager::addAction(action _a){
    actionBuffer.push_back(_a);
    // cout<<"Action Buffer Size: "<<actionBuffer.size()<<endl;
    
}


void SceneManager::addDNSEntity(dns _dns){
    dnsBuffer.push_back(_dns);
    
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


User * SceneManager::getUserWithMostWordsInBuffer(){
    
    //reset wordcount
    for (int i=0;i<users.size();i++){
        users[i]->setNumWordsInBuffer(0);
    }
    
    
    for(int i=0;i<priorityMessageBuffer.size();i++){
        User *u =getUserByUsername(priorityMessageBuffer[i].username);
        if(u!=nullptr)u->addNumWordsInBuffer(priorityMessageBuffer[i].wordcount);
    }
    
    
    for(int i=0;i<messageBuffer.size();i++){
        User *u =getUserByUsername(messageBuffer[i].username);
        if(u!=nullptr) u->addNumWordsInBuffer(messageBuffer[i].wordcount);
    }
    
    
    int num=0;
    User * u =nullptr;
    for (int i=0;i<users.size();i++){
        int n=users[i]->getNumWordsInBuffer();
        // cout<<n<<endl;
        if(n>num){
            u=users[i];
            num=n;
        }
        
    }
    //cout<<"user "<<u->getUserId()<<"has "<<num<<" words"<<endl;
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
        //words[i]->explode();
    }

}

void SceneManager::reset(){
    cout<<"reset"<<endl;
    bShouldReset=false;
    explodestopcounter=0;
    messageBuffer.clear();
    actionBuffer.clear();
    /*
    SoundM->user1wordcount.set(0);
    SoundM->user2wordcount.set(0);
    SoundM->user3wordcount.set(0);
     */
  
    stackManagerBuffer.clear();
    
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
    
    
    map<Letter *,Letter*>::iterator itr; // make the iterator, say it's going to iterate over a map<float, string>
    for( itr= lettermap.begin();itr!=lettermap.end();itr++){
        if((*itr).second){
            delete ((*itr).second);
        }
    }
    lettermap.clear();
    
    for (int i =0; i< letters.size();i++)
    {
        delete (letters[i]);
    }
    letters.clear();
    
    
    for (int i =0; i< csm.size();i++)
    {
        delete (csm[i]);
    }
    csm.clear();
    
    cout<<"num stack manager"<<csm.size()<<endl;
    
    stackManagerBuffer.clear();
    
    bIsExploding=false;

    
    initializeCaroussel();

    cout<<"num stack manager after"<<csm.size()<<endl;

    
    cout<<"USers "<<users.size()<<endl;


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


void SceneManager::drawTrails(bool _b){
    bDrawTrails=_b;
}

void SceneManager::toggleDrawTrails(){

    bDrawTrails=!bDrawTrails;
}


void SceneManager::addDNS(string _s){
    vC.addMovement(_s);

}
