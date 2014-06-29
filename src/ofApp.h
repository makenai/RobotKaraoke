#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "KaraokePlayer.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAssimpNISyncModelLoader.h"
#include "ofxAssimpNISync.h"

class ofApp : public ofBaseApp{
    
    ofLight light;

    ofSoundStream soundStream;
    ofxOpenNI openNIDevice;
    ofxAssimpNISync assimpNISync;
    ofxAssimpNISyncModelLoader model;
//    ofxAssimpModelLoader model;
    KaraokePlayer karaokePlayer;
    ofImage cdgScreen;
    vector <float> audioBuffer;
    
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
        void audioReceived(float *input, int bufferSize, int nChannels);
        void audioOut(float *output, int bufferSize, int nChannels);
};
