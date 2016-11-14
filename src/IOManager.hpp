//
//  IOManager.hpp

//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#ifndef IOManager_hpp
#define IOManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxLibwebsockets.h"



class IOManager {
    
public:
    IOManager();
    void setup();
    void update();
    void draw();
    
    ofxLibwebsockets::Client client;
    // websocket methods
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );

    ofBuffer buff;
    ofMutex  mutex;
    
    
    vector<string> stringbuff;
    
    
    
    bool getPause();
    void setPause(bool p);
    
    bool pause;
};
#endif
