//
//  LetterEvent.hpp
//  TypeStudy_02
//
//  Created by Flückiger Michael on 11.10.16.
//
//

#ifndef LetterEvent_hpp
#define LetterEvent_hpp

#include <stdio.h>


#include "ofMain.h"
//#include "Letter.hpp"
class Letter;

class LetterEvent : public ofEventArgs {
    
public:
    
    Letter * letter;
    string   message;
    
    LetterEvent() {
       letter = NULL;
    }
    
    static ofEvent <LetterEvent> events;
};



#endif /* LetterEvent_hpp */
