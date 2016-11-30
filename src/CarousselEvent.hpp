//
//  CarousselEvent.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 12.10.16.
//
//

#ifndef CarousselEvent_hpp
#define CarousselEvent_hpp

#include <stdio.h>



#include "ofMain.h"
//#include "Letter.hpp"
//class Letter;

class CarousselEvent : public ofEventArgs {
    
public:
    string   message;
    int   id;
    int stackId;
    int lineId;
    CarousselEvent() {
    }
    static ofEvent <CarousselEvent> events;
};



#endif /* CarousselEvent_hpp */
