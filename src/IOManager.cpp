//
//  WordManager.cpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 18.10.16.
//
//

#include "IOManager.hpp"

#include "SceneManager.hpp"

IOManager::IOManager(){
    
    
    
}


void IOManager::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
    options.host = "localhost";
    options.port=8080;
    options.channel="/entry";
    client.connect(options);
    client.addListener(this);
    ofSetLogLevel(OF_LOG_ERROR);
    
    pause=true;
    
}

void IOManager::update(){
    
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
        
        
        mutex.lock();
        
        
        if ( !args.json.isNull() ){
            
            if(args.json["Type"]=="User"){
                message m;
                m.name=args.json["Name"].asString();
                m.type=args.json["Type"].asString();
                m.text=args.json["Text"].asString();
                m.uuid=args.json["Id"].asInt();
                STM->addMessage(m);
            }
            
            if(args.json["Words"]!=" "){
                action a;
                a.uuid=args.json["Id"].asInt();
                a.startwordcounter=args.json["Words"][0].asInt();
                a.endwordcounter=args.json["Words"][1].asInt();
                STM->addAction(a);
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


