//
//  ThreadedBufferDeleter.hpp
//  Veillance
//
//  Created by Flückiger Michael on 05.12.16.
//
//

#ifndef helpers_hpp
#define helpers_hpp

#include <stdio.h>
#include "ofMain.h"


struct message {
    int uuid;
    string username;
    string type;
    string text;
    int wordcount;

};


struct priority {
    int uuid;
    string username;
    string type;
    string text;
    int wordcount;
};



struct action {
    int uuid;
    int startwordcounter;
    int endwordcounter;
    string name;
    string type;
    string text;
};


struct dns {
    int uuid;
    string username;
    string type;
    string text;    
};


struct clusterpoint {
    ofVec3f position;
};




#endif /* ThreadedBufferDeleter_hpp */
