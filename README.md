## Install

Get openFrameworks v0.9.3

Addons needed:

ofxLibwebsockets https://github.com/robotconscience/ofxLibwebsockets

ofxTonic https://github.com/jeonghopark/ofxTonic/tree/a292ea983b4f22f0e2e33c3b4d19b54ada7daf28

and also ofxGUI and ofxXmlSettings that comes with openFrameworks

beware: 
- sound is still very hacky implemented. 
- suggestions are not very good yet. testserver sends too many and just a loop of the same ones. but if a suggestion is set, i lock the word and the black space that it is leaving. that means that a suggestion can only be made once per word. that also means, that we run out of suggestions even there are coming in a lot and it is getting sort of boring.
    -> if you dont change something on the stream at the backend, we should revert this for friday to random selection on my side like we had it with previous versions...

## Keycodes
* h toggle sound gui
* H toggle sound
* p toggle listen/pause of serverstream
* f pull random word out of background
* s toggle fullscreen
* d toggle infos on framerate and buffersize
* D toggle user colorcode
* r set new targets for moving words
* w add input from file. not properly user/soundcoded
* c cycle through color modes: default, white, usercolor
* m stop the foregroundsoundcalculations -> i dont know how performance hungry that will be, so you can stop it an see if that helps in case...