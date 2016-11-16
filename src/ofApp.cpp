#include "ofApp.h"
#include "SceneManager.hpp"
#include "SoundManager.hpp"


//--------------------------------------------------------------
void ofApp::setup(){
    
    
    STM->initialize();
    SoundM->initialize();
    
    IOmanager.setup();

    
    ofBackground(0);
     ofSetVerticalSync(true);
    ofSetFrameRate(60);

    ofBuffer buffer = ofBufferFromFile("heartofdarkness 3.txt");
    for (auto line : buffer.getLines()){
        data.push_back(line);
    }
    
    

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
 
    IOmanager.update();
    
    STM->update();
  if(bSound)SoundM->update();

   // std::stringstream strm;
    //strm << "fps: " << ofGetFrameRate();
    //ofSetWindowTitle(strm.str());

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    STM->draw();
    if(bSound)SoundM->draw();
    
    if(bDebug)	{
        ofDrawBitmapString("Framerate", 0,20);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 100,20);
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
       // STM->setDebug(STM->getD);
    }
    
    
    
    
    if(key=='r'){
    
        for(auto movingWord:STM->movingWords){
            
            
            ofVec3f t;
            t.set(ofGetWidth()/4+ofRandom(-2000,2000),ofGetHeight()/2+ofRandom(-2000,2000),ofRandom(1000,5000));

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
        
        
        
        for (auto line : data){
            
             STM->addData(line,fragmentId);
            fragmentId++;
                 }
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
