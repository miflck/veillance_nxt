//
//  globals.hpp
//  Veillance
//
//  Created by Flückiger Michael on 16.01.17.
//
//

#ifndef globals_hpp
#define globals_hpp

#include <stdio.h>
#include "ofMain.h"


extern int width;
extern int viewportwidth;
extern int viewportheight;
extern int entrypoints;
extern int linesPerPoint;

//Typography
extern int   CCwidth;
extern int CCheight;
extern int bigfontsize;

// User
extern bool bSimUser;

extern int maxForegroundSound;



//Background
extern ofParameter<int> fadetime;
extern ofParameter<int> fadeAlpha;
extern ofParameter<int> fboAlpha;




extern ofParameter<int> clusterFadetime;
extern ofParameter<int> clusterFadeAlpha;


extern ofParameter<int> maxWordsInBuffer;


extern ofParameter<float> speedfactor;



#endif /* globals_hpp */
