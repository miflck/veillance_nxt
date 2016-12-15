#include "ofApp.h"
#include "SceneManager.hpp"
#include "SoundManager.hpp"


//--------------------------------------------------------------
void ofApp::setup(){
    
    settings.loadFile("settings.xml");
    string host = settings.getValue("serversettings:host","localhost");
    int port = settings.getValue("serversettings:port", 8080);
    string channel = settings.getValue("serversettings:channel", "/entry");
    
    IOmanager.setup();
    IOmanager.setHost(host);
    IOmanager.setPort(port);
    IOmanager.setChannel(channel);
    IOmanager.setupConnection();
    
    
    int width = settings.getValue("screensettings:width", 3840);
    int viewportwidth = settings.getValue("screensettings:viewportwidth", 3840);

    int height = settings.getValue("screensettings:height", 1080);
    
    int entrypoints = settings.getValue("rendering:entrypoints", 5);
    int linesPerPoint = settings.getValue("rendering:numlines", 7);


    
    
    ofSetWindowShape(width,height);
    ofSetWindowPosition(10, 10);

    
    STM->initialize(viewportwidth,height,entrypoints,linesPerPoint);
    SoundM->initialize();
    
  
    
    
    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofBuffer buffer = ofBufferFromFile("heartofdarkness.txt");
    for (auto line : buffer.getLines()){
        data.push_back(line);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    IOmanager.update();
    STM->update();
    if(bSound)SoundM->update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    STM->draw();
    if(bSound)SoundM->draw();
    if(bDebug)	{
    ofDisableBlendMode();
        int spacer=20;
        int spaceroffset=20;
    ofSetColor(255);
        ofDrawBitmapString("Framerate", 0,spacer);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 110,spacer);
        spacer+=spaceroffset;
        
        ofDrawBitmapString("Messagebuffer", 0,spacer);
        ofDrawBitmapString(STM->messageBuffer.size(), 110,spacer);
        spacer+=spaceroffset;
        
        ofDrawBitmapString("Prioritybuffer", 0,spacer);
        ofDrawBitmapString(STM->priorityMessageBuffer.size(), 200,spacer);
        spacer+=spaceroffset;


        int wordsInMessageBuffer;
        for(int i=0;i<STM->messageBuffer.size();i++){
            wordsInMessageBuffer+=STM->messageBuffer[i].wordcount;
        }
        
        ofDrawBitmapString("Words in Messagebuffer", 0,spacer);
        ofDrawBitmapString(STM->messageBuffer.size(), 200,spacer);
        spacer+=spaceroffset;
        

        ofDrawBitmapString("Actionbuffer", 0,spacer);
        ofDrawBitmapString(STM->actionBuffer.size(), 110,spacer);
        spacer+=spaceroffset;

        
       ofDrawBitmapString("Letterbuffer", 0,spacer);
        ofDrawBitmapString(STM->lettermap.size(), 110,spacer);
        spacer+=spaceroffset;

        
        ofDrawBitmapString("LettersOnScreen", 0,spacer);
        ofDrawBitmapString(STM->letters.size(), 120,spacer);
        spacer+=spaceroffset;

        
        ofDrawBitmapString("Stackbuffer", 0,spacer);
        ofDrawBitmapString(STM->stackmanagertotalbuffer, 140,spacer);
        spacer+=spaceroffset;

        ofDrawBitmapString("Total Words in Buffer", 0,spacer);
        ofDrawBitmapString(STM->totalWordsInBuffer, 200,spacer);
        
      
        
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key=='h'){
        SoundM->toggleGui();
    }
    
    
    if(key=='H'){
        bSound=!bSound;
    }
    
    
    if(key=='c'){
       STM->drawMode=(STM->drawMode+1)%3;
    }
    
    
    if(key=='p'){
        IOmanager.setPause(!IOmanager.getPause());
    }
    
    
    
    if(key=='F'){
        STM->makeMovingWordByFragmentId(0,0);
        
    }
    
    
    if(key=='f'){
        STM->makeRandomMovingWord();
        
    }
    
    
    if(key=='m'){
        STM->bSoundStuff=!STM->bSoundStuff;
        
    }

    
    if(key=='s'){
        ofToggleFullscreen();
    }
    
    
    
    if(key=='u'){
        bUpdate=!bUpdate;
    }
    
    if(key=='d'){
        // bDraw=!bDraw;
        // STM->setDebug(false);
        bDebug=!bDebug;
    }
    
    if(key=='D'){
        // bDraw=!bDraw;
        bDraw=!bDraw;
         STM->setDebug(bDraw);
    }
    
    
    if(key=='e'){
        // bDraw=!bDraw;
        STM->explode();
    }
    
    
    if(key=='E'){
        // bDraw=!bDraw;
        STM->reset();
    }
    
    
    
    if(key=='r'){
        
        for(auto movingWord:STM->movingWords){
            ofVec3f t;
            t.set(ofGetWidth()/4+ofRandom(-1000,1000),ofGetHeight()/2+ofRandom(-1000,1000),ofRandom(3000,5000));
            movingWord->setTarget(t);
            movingWord->startMoving();
        }
    }
    
    
    if(key=='R'){
        ofVec3f t;
        t.set(ofGetWidth()/4,ofGetHeight()/2,3000);
        STM->movingWords[0]->setTarget(t);
        for (int i=1;i<STM->movingWords.size();i++){
            t.set(STM->movingWords[i-1]->getDockPoint());
            STM->movingWords[i]->setTarget(t);
            STM->movingWords[i]->startMoving();
        }
    }
    
    
    
    if(key=='w'){
        STM->addDNS("hello");
       // for (auto line : data){
          //  STM->addData(line,fragmentId);
            fragmentId++;
       // }
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
