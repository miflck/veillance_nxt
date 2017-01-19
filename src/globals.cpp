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

int CCwidth=15;
int CCheight=22;
int bigfontsize=60;


 bool bSimUser=true;


ofParameter<int> fadetime;
ofParameter<int> fadeAlpha;
ofParameter<int> fboAlpha;


ofParameter<int> clusterFadetime;
ofParameter<int> clusterFadeAlpha;


ofParameter<int> maxWordsInBuffer;
 ofParameter<float> speedfactor;
