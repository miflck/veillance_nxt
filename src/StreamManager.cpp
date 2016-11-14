//
//  StreamManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#include "StreamManager.hpp"


//int viewportwidth=1920;
int viewportwidth=1280; //WXGA
//int viewportwidth=1920/2; //WXGA

//int viewportwidth=770;



StreamManager* StreamManager::instance = 0;

StreamManager* StreamManager::getInstance() {
    if (!instance) {
        instance = new StreamManager();
    }
    return instance;
}


StreamManager::StreamManager(){
}


void StreamManager::initialize() {
    
    initialized=true;
    cout<<"init StreamManager"<<endl;
    
  /*  font.load("FoundersGroteskMonoRegular.ttf", 10);
    bigfont.load("FoundersGroteskMonoRegular.ttf", 60);
    */
    font.load("FoundersGroteskMonoBold.ttf", 10);
    bigfont.load("FoundersGroteskMonoBold.ttf", 60);
    
    bkg.load("bkg_3.png");
    
    
    
   // float minspeed=2;
    float minspeed=1000;

    float speed;
    int h=20;
   // int w=10;
    int w=20;

    
    
  
    
    int lines=floor(ofGetHeight()/h);
    cout<<"lines"<<lines<<endl;
    for(int i = 0; i < lines; i++){
        CarousselManager cm;
        float p=ABS((ofGetHeight()/2)-((i*h)));
        float dl= ofMap(p*(p/4),0,ofGetHeight()/2*(ofGetHeight()/2/4),1,100); 
        float dW=w+dl;
        // s=v*t
        // s/v=t
        //v=s/t
        float time=w/minspeed;
        float dv=dW/time;
        float speed=dv;//(w/minspeed)*dW;
        float r=ofRandom(0,50);
        cm.setup(ofVec2f(0,(i*h)),viewportwidth,ofGetHeight(),dW,h);
        cm.maxspeed=speed;//minspeed*dl;
        cm.setId(i);
        cms.push_back(cm);
    }
    ofAddListener(CarousselEvent::events, this, &StreamManager::carousselEvent);
    
    ofEnableAlphaBlending();

    
    
    viewFront.x = 0;
    viewFront.y = 0;
    viewFront.width = ofGetWidth()/2;
    viewFront.height = ofGetHeight();

    
    viewBack.x = ofGetWidth()/2;
    viewBack.y = 0;
    viewBack.width = ofGetWidth()/2;
    viewBack.height = ofGetHeight();
    
    /*
    for(int i=0; i<2; i++) {
        cam[i].resetTransform();
        cam[i].setFov(60);
        cam[i].clearParent();
        }

    */
    
    
    
    
    
    cam[0].setVFlip(true);
    cam[0].setFov(60);

   
    // cam[0].setNearClip(10);

//    cam[0].setPosition(viewportwidth/2, ofGetHeight()/2, 500);
    float d=cam[0].getImagePlaneDistance(viewFront);

    cam[0].setPosition(viewportwidth/2, ofGetHeight()/2, d);

    
    cout<<d<<endl;
    
  //  cam[0].lookAt(ofVec3f(0,0,0));
    cam[1].setVFlip(true);
    cam[1].setNearClip(10);
   // cam[1].setPosition(viewportwidth/2, ofGetHeight()/2, 200);
    cam[1].setPosition(viewportwidth/2, ofGetHeight()/2, d-200);

    cam[1].pan(180);
    
    
   backgroundFbo.allocate(viewportwidth, ofGetHeight(),GL_RGBA);
    backgroundFbo.begin();
    ofClear(255,255,255, 0);
    backgroundFbo.end();
  

}




void StreamManager::update(){
    if(bUpdate){
        for(int i=0;i<cms.size();i++){
            cms[i].update();
        }
        
        
        
    
        
        
        for (int i=0;i<fragments.size();i++){
            if(fragments[i]->getBRemove()){
                cout<<"-- Remove Fragment--"<<fragments[i]->getFragmentId()<<endl;
                delete (fragments[i]);
                fragments.erase(fragments.begin()+i);
            }
        }
        
        for (int i=0;i<words.size();i++){
            if(words[i]->getBRemove()){
                delete (words[i]);
                words.erase(words.begin()+i);
            }
        }
        
        for (int i=0;i<letters.size();i++){
            if(shouldRemoveLetter(letters[i])){
                delete (letters[i]);
                letters.erase(letters.begin()+i);
            }
        }
        
        
        for(auto word:words){
           word->update();
        }
        
        for(auto movingWord:movingWords){
            movingWord->update();
          
        }

        for(auto letter:letters){
            letter->update();
        }
        
        
        // check if we want to remove the words
        for (int i=0;i<movingWords.size();i++){
            if(shouldRemoveMovingWord(movingWords[i])){
                delete (movingWords[i]);
                movingWords.erase(movingWords.begin()+i);
            }
        }
        
        
       
        
        
        
        
        
        
    }
    
    
    
   /* float alpha = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
    backgroundFbo.begin();
    /*
    for(auto letter:letters){
        ofSetColor(255,0,0);
        bkg.draw(letter->getPosition().x,letter->getPosition().y);
    }*/
    
  /*  ofSetColor(255,255,255, alpha);
    ofDrawRectangle(0,0,400,400);
    backgroundFbo.end();
    */
    
    
    
    
    backgroundFbo.begin();
    ofSetColor(0,0,0,1);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    ofEnableAlphaBlending();
   // ofDrawRectangle(0, 0, backgroundFbo.getWidth(), backgroundFbo.getHeight());
   ofDisableBlendMode();
   // ofClear(0,0,0,100);


    backgroundFbo.end();

    
 
 
}

void StreamManager::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

   backgroundFbo.draw(0,0);

    
    if(bDraw){
      //  ofBackground(0); // this matters

        
        cam[0].begin(viewFront);
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);

        
        backgroundFbo.begin();
        ofEnableAlphaBlending();

        for(int i=0;i<cms.size();i++){
            cms[i].draw();
        }
        backgroundFbo.end();

       // cam[1].begin();
    


       
        
      
        for(auto word:words){
          // word->draw();
        }
        
        
        for(auto fragment:fragments){
         //      fragment->draw();
        }
      
        
        
        drawMesh.clear();
        for(auto letter:letters){
           // ofVboMesh ms=letter->getUpdatedVboMesh();
            drawMesh.append(letter->getUpdatedVboMesh());
        }
        

        
        font.getFontTexture().bind();
        drawMesh.draw();
        font.getFontTexture().unbind();
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofVboMesh m;
        for(auto movingWord:movingWords){
            // movingWord->draw();
            m.append(movingWord->getUpdatedVboMesh());
        }
        bigfont.getFontTexture().bind();
        m.draw();
        bigfont.getFontTexture().unbind();
        
        cam[0].end();
   


        //drawMesh.drawInstanced(OF_MESH_WIREFRAME,5);
        
        for(auto letter:letters){
           letter->draw();
        }
        
        
       // cam[1].end();


       /* ofVboMesh m;
        for(auto movingWord:movingWords){
            // movingWord->draw();
            m.append(movingWord->getUpdatedVboMesh());
        }
        
        bigfont.getFontTexture().bind();
        m.draw();
        bigfont.getFontTexture().unbind();
        
       
        for(auto movingWord:movingWords){
           // movingWord->draw();
        }
        
        */
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);

        cam[1].begin(viewBack);
        bigfont.getFontTexture().bind();
        m.draw();
        bigfont.getFontTexture().unbind();
        cam[1].end();
        
        
        


    }

}





void StreamManager::carousselEvent(CarousselEvent &e){
    if(e.message=="STOP"){
        if(e.id>0){
            Letter *l=cms[e.id].getLastElementPointer();
            if(l!=nullptr){
                cms[e.id-1].addMovement(l);
            }
        }
        
        if(e.id==0){
            
            Letter *l=cms[e.id].getLastElementPointer();
            if(l!=nullptr){
                l->setBRemove(true);
            }
            
        
        }
        
        
        
        
    }
    
    
    if(e.message=="START"){
        if(e.id>0){
            //  cms[e.id-1].addMovement(cms[e.id].getLastElementChar());
        }
    }
}







bool StreamManager::isInitialized(){
    return initialized;
}


void StreamManager::addData(string _s, int _fragmentId){
    
    
    Fragment * f=new Fragment();
    f->setFragmentId(_fragmentId);
     vector<string> split;
     split = ofSplitString(_s, " ");
    cout<<_s<<split.size()<<endl;
  
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
             addLetter(l);
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

        addLetter(l);
        cms[cms.size()-1].addMovement(letters[letters.size()-1]);
        w->registerLetter(l);
        f->registerLetter(l);
        words.push_back(w);
        
        f->registerWord(w);
        wordcounter++; // debug id
     
     }
    fragments.push_back(f);
    
    /*
    
    Word * w=new Word();
    w->setup(wordcounter);
    w->setData(_s);
    int lifeTime=ofGetElapsedTimeMillis()+int(ofRandom(10000,50000));
    w->setLifeTime(lifeTime);
    
    float r=ofRandom(0,1);
    if(r<0.2 && _s!=" ")w->setIsSuggestion(true);
    
    for (auto ss : _s){
        char c = ss;
         Letter * l =new Letter();
        l->setFont(&font);
         l->setData(c);
        l->setWordId(wordcounter);
        l->setWordPointer(w);
         addLetter(l);
        cms[cms.size()-1].addMovement(letters[letters.size()-1]);
        w->addLetterPointer(l);
    }
    
    
    words.push_back(w);
    cout<<"words size "<<words.size()<<" letters Size "<<letters.size()<<endl;
    wordcounter++; // debug id*/
}


void StreamManager::addWord(string _s){
    Word *w;
    w->setup(words.size());
    w->setData(_s);
    words.push_back(w);
}


void StreamManager::addLetter(Letter *  _l){
    letters.push_back(_l);
}




void StreamManager::setDebug(bool _debug){
    debug=_debug;
    for(int i=0;i<cms.size();i++){
        cms[i].setDebugDraw(_debug);
    }

}


void StreamManager::addMovingWord(Word *_w){
    
    _w->setIsDrawn(false);
    
    MovingWords *mw=new MovingWords();
    mw->setup();
   // mw->myColor=_w->getBackgroundColor();
    mw->setFont(&bigfont);
    mw->setData(_w->getMyData());
    cout<<"startpos from word"<<_w->getPosition()<<endl;

    mw->setStartPosition(_w->getPosition());
    mw->setInitVelocity(_w->getVelocity());
    mw->startMoving();
    movingWords.push_back(mw);

}


bool StreamManager::shouldRemoveMovingWord(MovingWords *mv){
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


bool StreamManager::shouldRemoveLetter(Letter *l){
    return l->getBRemove();

}




void StreamManager::makeMovingWordByFragmentId(int _id, int _wordIndex){
    Fragment *f=getFragmentById(_id);
    cout<<f->getNumWords()<<endl;
    Word *w =f->getWordByIndex(_wordIndex);
    cout<<w->getIndex()<<endl;
    if(w!=nullptr){
    addMovingWord(w);
    }
    
}


Fragment* StreamManager::getFragmentById(int _id){
    for(auto fragment:fragments){
        if (_id==fragment->getFragmentId()){
            return fragment;
            break;
        }
    }
    return nullptr;
}



void StreamManager::makeRandomMovingWord(){
    int n=int(ofRandom(0,fragments.size()));
   // cout<<fragmentid<<endl;
    Fragment *f=fragments[n]; //getFragmentById(fragmentid);
    cout<<f->getFragmentId()<<endl;
    int wI=int(ofRandom(f->getNumWords()));
    cout<<"Word index "<<wI;
    Word *w =f->getWordByIndex(wI);
    cout<<"is on screen"<<w->checkIsOnScreen()<<endl;
    if(w!=nullptr && w->checkIsOnScreen()){
        addMovingWord(w);
        cout<<"making moving word"<<endl;
    }else {
        cout<<"another try"<<endl;

        makeRandomMovingWord();
    }
}


/*
void StreamManager::addWord(string _s){
    Word w;
    w.setup(words.size());
    w.setData(_s);
    words.push_back(w);
}

*/