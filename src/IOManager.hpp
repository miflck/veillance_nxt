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

    ofMutex  mutex;
    
    vector<string>fakeuser;
    
    
    string host;
    int port;
    string channel;
    
    
   void setHost(string _host);
    void setPort(int _port);
   void setChannel(string _channel);
    void setupConnection();

    
    
    
    bool getPause();
    void setPause(bool p);
    
    bool pause;
    
    int myid;
    
    //DEBUG
    int fakecounter=0;
    int messagecounter=0;
    
    void testMessage();
    
    bool isConnected=false;
    
    int reconnectionTimer;
    int reconnectionInterval;
    
};
#endif
