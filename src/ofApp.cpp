#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
    stream.setup();
    //stream.setData(data);
    stream.setFont(&font);
    
    cm.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    stream.update();
    cm.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    stream.draw();
    cm.draw();

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
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key=='c'){
        cm.cicle();
    
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
