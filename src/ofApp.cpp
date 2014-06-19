#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //karaokePlayer.open("/Users/pawels/Documents/OpenFrameworks/apps/myApps/robotKaraoke/data/Queen");
    //karaokePlayer.play();
    
    model.loadModel("/Users/pawels/Documents/OpenFrameworks/apps/myApps/robotKaraoke/data/models/ED-209/ED-209.dae");
    light.enable();
    ofEnableDepthTest();
    cout << model.getAnimationCount() << endl;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // ofSoundUpdate();
    // karaokePlayer.update();
    
    //cdgScreen.setFromPixels(karaokePlayer.pixels(), CDG_WIDTH, CDG_HEIGHT, OF_IMAGE_COLOR_ALPHA);
    //cdgScreen.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofBackground(255, 255, 255);

    ofSetColor(255,255,255,255);
    //cdgScreen.draw(10,10);

    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.75 , 0);
    model.drawFaces();
    
    
    int r = ofMap(mouseX, 0, 1024, 0, 255);
    int b = ofMap(mouseY, 0, 768, 0, 255);
    ofSetColor( r, 0, b );
    ofCircle(mouseX, mouseY, 25);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    int angle = ofMap(x, 0, 1024, 0, 720);
    model.setRotation(0, angle, 0, 1, 0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}