#pragma once

#include "ofMain.h"
#include "SceneManager.hpp"

#include "IOManager.hpp"


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
    
    
 

    
    ofTrueTypeFont  font;
    ofTrueTypeFont  bigfont;

    
    vector<string> data; //declare a vector of strings to store data
    
    
    IOManager IOmanager;
    
    
    
    
    
    bool bUpdate=true;
    bool bDraw=true;
  
    //debug
    int fragmentId;    
		
};
