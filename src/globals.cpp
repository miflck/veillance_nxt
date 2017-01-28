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


ofParameter<int> fadetime;
ofParameter<int> fadeAlpha;
ofParameter<int> fboAlpha;


ofParameter<int> clusterFadetime;
ofParameter<int> clusterFadeAlpha;


ofParameter<int> maxWordsInBuffer;
 ofParameter<float> speedfactor;

int maxForegroundSound=20;

ofParameter<float> fgmaxScalefact=2.5;