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
    
    
     width = settings.getValue("screensettings:width", 3840);
     viewportwidth = settings.getValue("screensettings:viewportwidth", 3840);

     viewportheight = settings.getValue("screensettings:height", 1080);
    
     entrypoints = settings.getValue("rendering:entrypoints", 5);
     linesPerPoint = settings.getValue("rendering:numlines", 7);
    
    
    
    
    
    


    
    
    ofSetWindowShape(width,viewportheight);
    ofSetWindowPosition(10, 10);

    
    STM->initialize();
    SoundM->initialize();
    
  
    
    
    ofBackground(0);
    ofSetVerticalSync(true);
   // ofSetFrameRate(60);
    
       
    ofxGuiSetDefaultWidth(500);
    
    gui.setup("GUI","gui.xml");
    gui.setPosition(viewportwidth,0);



    fadetime.set("fadetime",15,1,60);
    fadeAlpha.set("fadealpha",5,0,100);
    fboAlpha.set("FBO_Alpha",180,0,255);

    gui.add(fadetime);
    gui.add(fadeAlpha);
    gui.add(fboAlpha);

    

    clusterFadetime.set("clusterfadetime ",15,1,100);
    clusterFadeAlpha.set("clusterfadealpha ",5,0,100);
    
    gui.add(clusterFadetime);
    gui.add(clusterFadeAlpha);

    
    maxWordsInBuffer.set("maxWordsInBuffer ",5000,500,10000);

    gui.add(maxWordsInBuffer);

    
    speedfactor.set("speedfactor ",1,0.1,20);
    gui.add(speedfactor);
    
    
    suggestionTrigger.set("suggestionTrigger ",0.95,0.1,1);
    gui.add(suggestionTrigger);
    
    
    
    gui.loadFromFile("gui.xml");
    
       // badwords["hello"]=1;
    
    
    
    string filename = ofToDataPath("badwords_2.txt");
    ifstream f(filename.c_str(),ios::in);
    string line;
    while (getline(f,line)) {
        //lines.push_back(ofxTrimStringRight(line));
        vector<string> items = ofSplitString(line, " ");
        for (int i=0; i<items.size(); i++) {
            badwords[ofToUpper(items[i])]++;
        }
    }
    f.close();

    for (const auto& words : badwords )
        cout << words.first << endl;
    
    
    string filename2 = ofToDataPath("goodwords.txt");
    ifstream f2(filename2.c_str(),ios::in);
    string line2;
    while (getline(f2,line2)) {
        //lines.push_back(ofxTrimStringRight(line));
        vector<string> items = ofSplitString(line2, " ");
        for (int i=0; i<items.size(); i++) {
            goodwords[ofToUpper(items[i])]++;
        }
    }
    f2.close();
    cout << "------------ Good -------------" << endl;

    for (const auto& words2 : goodwords )
        cout << words2.first << endl;
    

    
    
    //auto it = my_map.find("x");
  //  if (it != my_map.end()) std::cout << "x: " << it->second << "\n";
    
   /*
    map<string,int>::iterator it = badwords.find("Trump");
    
    if (it != badwords.end())
        cout << it->first << " founded!" <<endl;
    else
        cout << "city not found" << endl;
*/
}

//--------------------------------------------------------------
void ofApp::update(){
    IOmanager.update();
    STM->update();
    if(!muteSound){
        SoundM->update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    if(bDraw){
        STM->draw();
    }
    
    
    
   SoundM->draw();
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
    
    
    
    
    if( !bHide ){
        gui.draw();
    }

    
    
}


//--------------------------------------------------------------
void ofApp::toggleGui(){
    bHide = !bHide;
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key=='q'){
        SoundM->deleteAllDeletedSounds();
        //SoundM->addForegroundSound();
    }
    
    
    
    
    if(key=='b'){
        STM->makeRandomBurst(100);        //SoundM->addForegroundSound();
    }
    
    if(key=='h'){
      toggleGui();
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
        //STM->bSoundStuff=!STM->bSoundStuff;
        muteSound=!muteSound;
    }

    
    if(key=='s'){
        ofToggleFullscreen();
    }
    
    
    
    if(key=='u'){
       // bUpdate=!bUpdate;
        STM->bGetMostUser=!STM->bGetMostUser;
    }
    
    if(key=='d'){
        // bDraw=!bDraw;
        // STM->setDebug(false);
        bDebug=!bDebug;
    }
    
    if(key=='D'){
        // bDraw=!bDraw;
        bDraw=!bDraw;
        // STM->setDebug(bDraw);
    }
    
    
    if(key=='l'){
        // bDraw=!bDraw;
        //bDraw=!bDraw;
         STM->debug=!STM->debug;
    }
    
    if(key=='e'){
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
    
    
    if(key=='x'){
        // bDraw=!bDraw;
        STM->toggleDrawTrails();
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
