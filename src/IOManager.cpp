//
//  WordManager.cpp
//  TypeStudy_02
//
//  Created by Fl√ºckiger Michael on 18.10.16.
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
               
                if(messagecounter>7 && bSimUser){
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
                    
                    
                    
                    
                    if( STM->getUserByUsername(username)==nullptr &&i<4*maxLength){
                        cout<<"++++++++++++++++ PRIORITY +++++++++++++++++++"<<endl;
                        STM->addPriorityMessage(m);
                    }else if(STM->getUserByUsername(username)!=nullptr && STM->getUserByUsername(username)->getNumWordsOnScreen()<100 &&i<2*maxLength){
                        cout<<"+ PRIORITY  Not much words on screen++"<<endl;
                        STM->addPriorityMessage(m);
                    }
                    else{
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
                
               // User * u=STM->getUserByUsername(username);
               // STM->users.push_back(u);
                
                bool isUserNew=false;

                User * u=STM->getUserByUsername(username);
                if(u==nullptr){
                    int id=STM->users.size();
                    u=new User();
                    u->setup();
                    u->setUserName(username);
                    u->setUserId(id);
                    
                    cout<<"new user "<<u->getUserName()<<" id "<<id<<endl;
                    isUserNew=true;
                    
                }
                
                
                

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
                
                
                //only push new users
                if(isUserNew){
                   STM->users.push_back(u);
                }

                
            }
            
            
            
            
            
        }
        mutex.unlock();
    }
    
    
}


//--------------------------------------------------------------
void IOManager::testMessage(){

        
        
        mutex.lock();
        
        
        
                string username="192.168.2.100";
                
    
                
    string s="The Nellie, a cruising yawl, swung to her anchor without a flutter of the sails, and was at rest. The flood had made, the wind was nearly calm, and being bound down the river, the only thing for it was to come to and wait for the turn of the tide.The sea-reach of the Thames stretched before us like the beginning of an interminable waterway. In the offing the sea and the sky were welded together without a joint, and in the luminous space the tanned sails of the barges drifting up with the tide seemed to stand still in red clusters of canvas sharply peaked, with gleams of varnished sprits. A haze rested on the low shores that ran out to sea in vanishing flatness. The air was dark above Gravesend, and farther back still seemed condensed into a mournful gloom, brooding motionless over the biggest, and the greatest, town on earth.The Director of Companies was our captain and our host. We four affectionately watched his back as he stood in the bows looking to seaward. On the whole river there was nothing that looked half so nautical. He resembled a pilot, which to a seaman is trustworthiness personified. It was difficult to realize his work was not out there in the luminous estuary, but behind him, within the brooding gloom. Between us there was, as I have already said somewhere, the bond of the sea. Besides holding our hearts together through long periods of separation, it had the effect of making us tolerant of each others yarns—and even convictions. The Lawyer—the best of old fellows—had, because of his many years and many virtues, the only cushion on deck, and was lying on the only rug. The Accountant had brought out already a box of dominoes, and was toying architecturally with the bones. Marlow sat cross-legged right aft, leaning against the mizzen-mast. He had sunken cheeks, a yellow complexion, a straight back, an ascetic aspect, and, with his arms dropped, the palms of hands outwards, resembled an idol. The director, satisfied the anchor had good hold, made his way aft and sat down amongst us. We exchanged a few words lazily. Afterwards there was silence on board the yacht. For some reason or other we did not begin that game of dominoes. We felt meditative, and fit for nothing but placid staring. The day was ending in a serenity of still and exquisite brilliance. The water shone pacifically; the sky, without a speck, was a benign immensity of unstained light; the very mist on the Essex marsh was like a gauzy and radiant fabric, hung from the wooded rises inland, and draping the low shores in diaphanous folds. Only the gloom to the west, brooding over the upper reaches, became more sombre every minute, as if angered by the approach of the sun. And at last, in its curved and imperceptible fall, the sun sank low, and from glowing white changed to a dull red without rays and without heat, as if about to go out suddenly, stricken to death by the touch of that gloom brooding over a crowd of men.";
                int maxLength=500;
                
                // DEBUG? SPLIT MESSAGE IN TO SEVERAL
                for (unsigned i = 0; i < s.length(); i += maxLength) {
                    message m;
                    m.username=username;
                    m.type="HTTP";
                    m.text=s.substr(i, maxLength);
                    //id not working?
                    m.uuid=100;
                    int count=0;
                    count= std::distance(std::istream_iterator<std::string>(std::istringstream(m.text) >> std::ws),std::istream_iterator<std::string>());
                    cout<<"i "<<i<<" "<<count<<endl;
                    
                    m.wordcount=count;
                    
                    
                    
                    
                    if( STM->getUserByUsername(username)==nullptr &&i<4*maxLength){
                        cout<<"++++++++++++++++ PRIORITY +++++++++++++++++++"<<endl;
                        STM->addPriorityMessage(m);
                    }else if(STM->getUserByUsername(username)!=nullptr && STM->getUserByUsername(username)->getNumWordsOnScreen()<100 &&i<2*maxLength){
                        cout<<"+ PRIORITY  Not much words on screen++"<<endl;
                        STM->addPriorityMessage(m);
                    }
                    else{
                        STM->addMessage(m);
                    }
                    
                    messagecounter++;
                }
    
        
            
            
            
            
    
        mutex.unlock();
    
    
    
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
    
    
    options.reconnect = true;
    options.reconnectInterval = 4000;
    
    
    client.connect(options);
    client.addListener(this);
    ofSetLogLevel(OF_LOG_ERROR);
    
    pause=false;
    
    

    
}



