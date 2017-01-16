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


//Background
extern ofParameter<int> fadetime;
extern ofParameter<int> fadeAlpha;

#endif /* globals_hpp */
