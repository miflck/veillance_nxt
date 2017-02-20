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


extern ofParameter<float> suggestionTrigger;


//Typography
extern int   CCwidth;
extern int CCheight;
extern int bigfontsize;

// User
extern bool bSimUser;
extern int maxForegroundSound;

//burst
extern int burstInterval;
extern int minBurstMovingWords;
extern int burstAmmount;
extern bool doBurst;


//Background
extern ofParameter<int> fadetime;
extern ofParameter<int> fadeAlpha;
extern ofParameter<int> fboAlpha;



// List
extern map<string,int> badwords;





extern ofParameter<int> clusterFadetime;
extern ofParameter<int> clusterFadeAlpha;


extern ofParameter<int> maxWordsInBuffer;


extern ofParameter<float> speedfactor;


extern ofParameter<float> fgmaxScalefact;


extern ofParameter<float> backgroundcolorlerp;




extern ofParameter<float> rollfact;
extern ofParameter<float> panfact;
extern ofParameter<float> tiltfact;

extern ofParameter<float> movingwordSpeedFact;

extern ofParameter<bool>  background;

extern ofParameter<bool>  slowpop;







#endif /* globals_hpp */
