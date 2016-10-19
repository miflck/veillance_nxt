#include "ofApp.h"
#include "StreamManager.hpp"


//--------------------------------------------------------------
void ofApp::setup(){
    
    
    STM->initialize();

    
    ofBackground(0);
     ofSetVerticalSync(true);
    ofSetFrameRate(60);
    font.load("FoundersGroteskMonoRegular.ttf", 10);
    bigfont.load("FoundersGroteskMonoRegular.ttf", 50);

    
    dot.load("dot.png");
    
    ofBuffer buffer = ofBufferFromFile("heartofdarkness.txt");
    for (auto line : buffer.getLines()){
        data.push_back(line);
    }
    
    
    
    wm.setup();
    
    mw.setup();
    mw.setFont(&bigfont);
    mw.setData("hallo");
    mw.startMoving();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
 
    STM->update();
    
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    
    wm.update();
    mw.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // stream.draw();
    
    ofSetColor(255);
   /* ofVboMesh m;
    for(int i=0;i<letters.size();i++){
        ofVboMesh ms=letters[i]->getOriginalVboMesh();
        m.append(ms);
    }
    font.getFontTexture().bind();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
   // m.draw();
    mw.draw();
 

    font.getFontTexture().unbind();
    ofPopMatrix();
       */
    
    
    
    STM->draw();

    
    wm.draw();
    
    ofPushMatrix();
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    // m.draw();
   // mw.draw();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    /*if(key=='a'){
        Word w;
        string s=words[0];
        w.setup();
        w.setFont(&font);
        w.setData(s);
        w.setPosition(ofVec3f(ofGetWidth(),ofGetHeight(),0));
        stream.addWord(w);
        words.erase(words.begin());
    }*/
    
    
   
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key=='c'){
      /*  Letter * l =new Letter();
        l->setData('c');
        l->setFont(&font);

        addLetter(l);*/
       // cms[cms.size()-1].addMovement(letters[letters.size()-1]);
        
        
        STM->addData("hello");
        
        
    }
    
    
    
    if(key=='u'){
        bUpdate=!bUpdate;
    }
    
    if(key=='d'){
        bDraw=!bDraw;
    }
    
    
    if(key=='w'){
        
        
        for (auto line : data){
            STM->addData(line);
        }
//        cout<<"new leterbuffer size"<<letterbuffer.size();

        
        
        /*
        for(auto text :data){
            vector<string> split;
            split = ofSplitString(text, " ");
            for (auto w:split){
                wm.addWord(w);
            }
        }
        
        
        
        
        
        
        for (auto line : data){
            for (auto ss : line){
                char sss = ss;
                Letter * l =new Letter();
                l->setData(sss);
                l->setFont(&font);

                addLetter(l);
//                cms[cms.size()-1].addMovement(&l);
                cms[cms.size()-1].addMovement(letters[letters.size()-1]);

            }
        }
        cout<<"new leterbuffer size"<<letterbuffer.size();
         */
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



void ofApp::addLetter(Letter *  _l){
    letters.push_back(_l);
}


bool ofApp::shouldAddFromLetterBuffer(){
    bool add=false;
    if(letterbuffer.size()>0)add=true;
    return add;
}

void ofApp::addLetterBuffer(Letter  _l){
    letterbuffer.push_back(_l);
}

/*
 void ofApp::addLetterFromBuffer(){
 if(!cms[0].bIsMoving){
 Letter l=letterbuffer[0];
 letters.push_back(l);
 cout<<l.getData()<<endl;
 cms[cms.size()-1].addMovement(l.getData());
 letterbuffer.erase(letterbuffer.begin());
 }
 
 
 }*/
