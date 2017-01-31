#pragma once
#include "ofMain.h"
#include "SceneManager.hpp"
#include "SoundManager.hpp"
#include "IOManager.hpp"
#include "ofxXmlSettings.h"
#include "globals.hpp"

#include "ofxGui.h"
#include <fstream>




class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    // Typography
    ofTrueTypeFont  font;
    ofTrueTypeFont  bigfont;

    
    
    // Server
    IOManager IOmanager;
    ofxXmlSettings settings;
    
  
    //debug
    int fragmentId;
    bool bSound=true;
    
    // Debug Data from file
    vector<string> data; //declare a vector of strings to store data
    bool bUpdate=true;
    bool bDraw=true;
    bool bDebug=false;
    bool muteSound=false;
    
    
    bool bHide=true;
    void toggleGui();
    ofxPanel gui;
    

		
};
