#pragma once

#include "ofMain.h"
#include "Letter.hpp"
#include "MovingWords.hpp"
#include "WordManager.hpp"
#include "StreamManager.hpp"

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
    
    vector<string> words;
    
    bool bUpdate=true;
    bool bDraw=true;
    
    vector<Letter *>letters;
    void addLetter(Letter * _l);
    
    vector<Letter>letterbuffer;
    void addLetterBuffer(Letter _l);

    bool shouldAddFromLetterBuffer();
    void addLetterFromBuffer();

    ofImage dot;

    MovingWords mw;
    WordManager wm;

    //debug
    int fragmentId;    
		
};
