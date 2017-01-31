#include "ofMain.h"
#include "ofAppRunner.h"

#include "ofApp.h"

//========================================================================
int main( ){

 //   ofSetupOpenGL(2560,800,OF_WINDOW);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());
    
    
    // This is for MultiFullscreen.
    // The Resolution is for 2 wXGA Projectors.
    //ofSetupOpenGL(&window,2560,800,OF_WINDOW);

    // This would be for fullHD
    //ofSetupOpenGL(&window,3840,1080,OF_WINDOW);

    
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window,10,10,OF_WINDOW);
    ofRunApp(new ofApp());
    
    

}
