#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
   // ofSetVerticalSync(true);
    //ofSetFrameRate(60);
    font.load("Constantia.ttf", 30);
    
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
   // stream.setup();
    //stream.setData(data);
   // stream.setFont(&font);
    
    
    float minspeed=2;
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
        
        float dl= ofMap(p*(p/2),0,ofGetHeight()/2*(ofGetHeight()/2/2),1,100); //-> int = smooth bewegung, float stockt??
        float dW=w+dl;
        
       // s=v*t
       // s/v=t
        //v=s/t
        
        float time=w/minspeed;
        
        float dv=dW/time;
        
        
        float speed=dv;//(w/minspeed)*dW;

       // minspeed+
        
       // cm.setup(ofVec2f(0,(i*h)),ofRandom(7*dl,10*dl),h);
        float r=ofRandom(0,50);
        cm.setup(ofVec2f(0,(i*h)),dW,h);

        cm.maxspeed=speed;//minspeed*dl;
        
        
        
        cm.setId(i);
        cms.push_back(cm);
    }
    
    
    
    // cm.setup(ofVec2f(0,10));
    
    ofAddListener(CarousselEvent::events, this, &ofApp::carousselEvent);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
   // stream.update();
   // cm.update();
    if(bUpdate){
    for(int i=0;i<cms.size();i++){
        cms[i].update();
    }
    }
    
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    
}

//--------------------------------------------------------------
void ofApp::draw(){
   // stream.draw();
    //cm.draw();
    
    if(bDraw){
    for(int i=0;i<cms.size();i++){
        cms[i].draw();
    }}
    
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
        //        cm.cicle();
        cms[cms.size()-1].addMovement('c');
        
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key=='c'){
        //        cm.cicle();
     //   cms[cms.size()-1].addMovement('c');
        
        
    }
    
    if(key=='c'){
        //        cm.cicle();
        cms[cms.size()-1].addMovement('c');
        
        
    }
    
    
  
    if(key=='u'){
        bUpdate=!bUpdate;
    }
    
    if(key=='d'){
        bDraw=!bDraw;
    }
    
    
    if(key=='w'){
        //        cm.cicle();
        
       // string text=" hello world";
        
        for (auto line : data){
            for (auto ss : line){
                char sss = ss;
                cms[cms.size()-1].addMovement(sss);
            }
        }

        
      /*  for (auto ss : text){
            char sss = ss;
             cms[cms.size()-1].addMovement(sss);
        }*/

        
        
       
        
        
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
        
        
        //cout << "Caroussel Event: "+e.message <<" from "<<e.id<<endl;
        if(e.id>0){
            cms[e.id-1].addMovement(cms[e.id].getLastElementChar());
            //cout << "Caroussel Event: "+e.message <<" from "<<e.id<<endl;
          //  cout<<cms[e.id].getLastElementChar()<<endl;


        }}
}

