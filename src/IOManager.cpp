//
//  WordManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#include "IOManager.hpp"

#include "StreamManager.hpp"

IOManager::IOManager(){
    
    
    
}


void IOManager::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);

    ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
    options.host = "localhost";// "echo.websocket.org";
    options.port=8080;
    options.channel="/entry";
    client.connect(options);
    client.addListener(this);
    ofSetLogLevel(OF_LOG_ERROR);
    
    pause=true;


}

void IOManager::update(){
    
    cout<<stringbuff.size()<<endl;
    
    if ( stringbuff.size() > 0 ){
    STM->addData(stringbuff[0],ofRandom(1000));
            stringbuff.erase(stringbuff.begin());
    }
    
    
    /*if ( buff.size() != 0 ){
        mutex.lock();
        
        int size = buff.size();
        
        string * incoming = new string[size ];
        memcpy(incoming, buff.getData(), buff.size());
        cout<<incoming<<endl;
        mutex.unlock();
    }*/

    
    
}

void IOManager::draw(){
   
}


//--------------------------------------------------------------
void IOManager::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void IOManager::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void IOManager::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void IOManager::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void IOManager::onMessage( ofxLibwebsockets::Event& args ){
    
    if(!pause){
    //cout<<"got message "<<args.json<<endl;
    
    
    mutex.lock();
    
    
    
    if ( !args.json.isNull() ){
            if(args.json["Type"]=="User"){
           // cout<<args.json["Text"]<<endl;
           string data= args.json["Text"].asString();
               // data.erase(std::remove_if(data.begin(), data.end(), " \" "), data.end());

                
            int id= args.json["Id"].asInt();
           cout<<"Data "<<data<<" Id "<<id<<endl;
            //STM->addData(data,id);
                
            stringbuff.push_back(data);


            
            
        }
       
    }
    mutex.unlock();
    }

    
}

//--------------------------------------------------------------
void IOManager::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}


void IOManager::setPause(bool _p){
    pause=_p;

}

bool IOManager::getPause() {
    return pause;
}


