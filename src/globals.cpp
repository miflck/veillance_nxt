//
//  globals.cpp
//  Veillance
//
//  Created by Flückiger Michael on 16.01.17.
//
//

#include "globals.hpp"
float gutterwidth=75;
int width=3840;
int viewportwidth =  width/4;
int viewportheight = 1080;
int entrypoints =  5;
int linesPerPoint = 7;

 ofParameter<float> suggestionTrigger=0.95;


int CCwidth=15;
int CCheight=22;
int bigfontsize=60;


 bool bSimUser=false;

bool useBursts=false;
int burstInterval = 1000;
int minBurstMovingWords=50;
int burstAmmount=50;
bool doBurst=false;


 map<string,int> badwords;


ofParameter<int> fadetime;
ofParameter<int> fadeAlpha;
ofParameter<int> fboAlpha;


ofParameter<int> clusterFadetime;
ofParameter<int> clusterFadeAlpha;


ofParameter<int> maxWordsInBuffer;
 ofParameter<float> speedfactor;


ofParameter<float> rollfact;
ofParameter<float> panfact;
ofParameter<float> tiltfact;

ofParameter<float> movingwordSpeedFact;





int maxForegroundSound=15;

ofParameter<float> fgmaxScalefact=2.5;


ofParameter<float>backgroundcolorlerp=2000;

ofParameter<bool> background=false;

 ofParameter<bool>  slowpop=false;

