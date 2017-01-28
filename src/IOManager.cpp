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

    for(int i=0;i<10;i++){
        string u="user ";
        u+=ofToString(i);
        fakeuser.push_back(u);
    }
    
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
    //cout<<"message "<<args.json<<endl;
    if(!pause){
        
        
        mutex.lock();
        
        
        if ( !args.json.isNull() ){
            
            if(args.json["Type"]=="HTTP"){
               // cout<<"mcounter "<<messagecounter<<endl;
                string username=args.json["Name"].asString();
               
                if(messagecounter>7){
                username =fakeuser[fakecounter];
                fakecounter++;
                if(fakecounter>fakeuser.size()-1)fakecounter=0;
                }
                
                string s=args.json["Text"].asString();
                int maxLength=500;
                
                // DEBUG? SPLIT MESSAGE IN TO SEVERAL
                for (unsigned i = 0; i < s.length(); i += maxLength) {
                    message m;
                    m.username=username;
                    m.type=args.json["Type"].asString();
                    m.text=s.substr(i, maxLength);
                    //id not working? 
                    m.uuid=args.json["Id"].asInt();
                    int count=0;
                   count= std::distance(std::istream_iterator<std::string>(std::istringstream(m.text) >> std::ws),std::istream_iterator<std::string>());
                    cout<<"i "<<i<<" "<<count<<endl;

                    m.wordcount=count;
                    
                    if( STM->getUserByUsername(username)==nullptr &&i<6*maxLength){
                        cout<<"++++++++++++++++ PRIORITY +++++++++++++++++++"<<endl;
                        STM->addPriorityMessage(m);
                    }else{
                        STM->addMessage(m);
                    }

                    messagecounter++;
                }
            }
            
          /*  if(args.json["Words"]!=" "){
                action a;
                a.uuid=args.json["Id"].asInt();
                a.startwordcounter=args.json["Words"][0].asInt();
                a.endwordcounter=args.json["Words"][1].asInt();
                //STM->addAction(a);
            }
            */
            
            if(args.json["Type"]=="DNS"){
                dns d;
                string username=args.json["Name"].asString();
                
                User * u=STM->getUserByUsername(username);
                ofColor c;
                if(u!=nullptr){
                   c=u->getBackgroundColor();
                }else{
                    c=ofColor(255,255,255);
                }
                
                string s=args.json["Text"].asString();
                d.type=args.json["Type"].asString();
                d.username=username;
                d.text=s;
                d.uuid=args.json["Id"].asInt();
                d.color=c;;
                STM->addDNSEntity(d);

                
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



void IOManager::setHost(string _host){
    host=_host;
}

void IOManager::setPort(int _port){
    port=_port;
}

void IOManager::setChannel(string _channel){
    channel=_channel;
}

void IOManager::setupConnection(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
    options.host = host;
    options.port=port;
    options.channel=channel;
    client.connect(options);
    client.addListener(this);
    ofSetLogLevel(OF_LOG_ERROR);
    
    pause=false;

    
}



