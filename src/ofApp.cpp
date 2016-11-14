#include "ofApp.h"
#include "StreamManager.hpp"


//--------------------------------------------------------------
void ofApp::setup(){
    
    
    STM->initialize();
    
    IOmanager.setup();

    
    ofBackground(0);
     ofSetVerticalSync(true);
    ofSetFrameRate(60);

    ofBuffer buffer = ofBufferFromFile("heartofdarkness 2.txt");
    for (auto line : buffer.getLines()){
        data.push_back(line);
    }
    
    

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
 
    IOmanager.update();
    
    STM->update();
    
   // std::stringstream strm;
    //strm << "fps: " << ofGetFrameRate();
    //ofSetWindowTitle(strm.str());

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // stream.draw();
    
    ofSetColor(255);
    
    
    STM->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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
    
    
    
    if(key=='u'){
        bUpdate=!bUpdate;
    }
    
    if(key=='d'){
       // bDraw=!bDraw;
        STM->setDebug(false);
    }
    
    if(key=='D'){
        // bDraw=!bDraw;
        STM->setDebug(true);
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
