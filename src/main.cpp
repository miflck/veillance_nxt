#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(3840,1080,OF_WINDOW);			// <-------- setup the GL context

    ofSetupOpenGL(2560,800,OF_WINDOW);
   // ofSetupOpenGL(1920,1200,OF_WINDOW);
    
  //  ofSetupOpenGL(1540,540,OF_WINDOW);			// <-------- setup the GL context

    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
