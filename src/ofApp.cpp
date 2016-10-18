#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
     ofSetVerticalSync(true);
    ofSetFrameRate(60);
    font.load("Anonymous.ttf", 10);
    
    ofBuffer buffer = ofBufferFromFile("heartofdarkness.txt");
    for (auto line : buffer.getLines()){
        data.push_back(line);
    }
    
    for(int i = 0; i < data.size(); i++){
        vector<string> split;
        split = ofSplitString(data[i], " ");
        for (int k=0;k<split.size();k++){
            words.push_back(split[k]);
        }
    }
    
    float minspeed=4;
    float speed;
    
    
    int h=20;
    int w=10;
    
    //   h=50;
    //   w=50;
    
    
    
    
    int lines=floor(ofGetHeight()/h);
    cout<<"lines"<<lines<<ofGetHeight()/h<<endl;
    for(int i = 0; i < lines; i++){
        CarousselManager cm;
        float p=ABS((ofGetHeight()/2)-((i*h)));
        // double dl= int(ofMap(p*(p/2),0,ofGetHeight()/2*(ofGetHeight()/2/2),1,15)); //-> int = smooth bewegung, float stockt??
        float dl= ofMap(p*(p/4),0,ofGetHeight()/2*(ofGetHeight()/2/4),1,100); //-> int = smooth bewegung, float stockt??
        float dW=w+dl;
        // s=v*t
        // s/v=t
        //v=s/t
        float time=w/minspeed;
        float dv=dW/time;
        float speed=dv;//(w/minspeed)*dW;
        float r=ofRandom(0,50);
        cm.setup(ofVec2f(0,(i*h)),dW,h);
        cm.maxspeed=speed;//minspeed*dl;
        cm.setId(i);
        cms.push_back(cm);
    }
    
    ofAddListener(CarousselEvent::events, this, &ofApp::carousselEvent);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(bUpdate){
        for(int i=0;i<cms.size();i++){
            cms[i].update();
        }
    }
  //  cout<<letters.size()<<endl;
    
    
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // stream.draw();
    if(bDraw){
        for(int i=0;i<cms.size();i++){
            cms[i].draw();
        }
    }
    
    
    ofSetColor(255);
    ofVboMesh m;
    for(int i=0;i<letters.size();i++){
        ofVboMesh ms=letters[i]->getOriginalVboMesh();
        m.append(ms);
    }
    font.getFontTexture().bind();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
   // m.draw();
    
    font.getFontTexture().unbind();

    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='a'){
        Word w;
        string s=words[0];
        w.setup();
        w.setFont(&font);
        w.setData(s);
        w.setPosition(ofVec3f(ofGetWidth(),ofGetHeight(),0));
        stream.addWord(w);
        words.erase(words.begin());
    }
    
    
    if(key=='C'){
        //cms[cms.size()-1].addMovement('c');
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key=='c'){
        Letter * l =new Letter();
        l->setData('c');
        l->setFont(&font);

        addLetter(l);
        cms[cms.size()-1].addMovement(letters[letters.size()-1]);
    }
    
    
    
    if(key=='u'){
        bUpdate=!bUpdate;
    }
    
    if(key=='d'){
        bDraw=!bDraw;
    }
    
    
    if(key=='w'){
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

void ofApp::carousselEvent(CarousselEvent &e){
    
    if(e.message=="STOP"){
        
        
        if(e.id>0){
            Letter *l=cms[e.id].getLastElementPointer();
            
            if(l!=nullptr){
                cms[e.id-1].addMovement(l);
            }
            //cout << "Caroussel Event: "+e.message <<" from "<<e.id<<endl;
            //  cout<<cms[e.id].getLastElementChar()<<endl;
            
            
        }}
    
    
    if(e.message=="START"){
        
        
        //cout << "Caroussel Event: "+e.message <<" from "<<e.id<<endl;
        if(e.id>0){
            //  cms[e.id-1].addMovement(cms[e.id].getLastElementChar());
            //cout << "Caroussel Event: "+e.message <<" from "<<e.id<<endl;
            //  cout<<cms[e.id].getLastElementChar()<<endl;
            
            
        }}
    
    
    
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
