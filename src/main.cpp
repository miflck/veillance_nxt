#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

 //   ofSetupOpenGL(2560,800,OF_WINDOW);
    
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());
    
    
    
    
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window,2560,800,OF_WINDOW);
    ofRunApp(new ofApp());
    
    

}
