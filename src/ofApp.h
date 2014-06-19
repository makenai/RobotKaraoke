#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "KaraokePlayer.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{
    
    ofLight light;
    ofxAssimpModelLoader model;
    KaraokePlayer karaokePlayer;
    ofImage cdgScreen;
    
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
