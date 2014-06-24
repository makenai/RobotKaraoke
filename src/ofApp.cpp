#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(1);
    openNIDevice.start();
    
    //karaokePlayer.open("/Users/pawels/Documents/OpenFrameworks/apps/myApps/robotKaraoke/data/Queen");
    //karaokePlayer.play();
    
    model.loadModel("/Users/pawels/Documents/OpenFrameworks/examples/addons/assimpExample/bin/data/astroBoy_walk.dae");
    //model.loadModel("/Users/pawels/Documents/OpenFrameworks/apps/myApps/robotKaraoke/data/models/ED-209/ED-209.dae");
    //model.loadModel("/Users/pawels/Documents/OpenFrameworks/apps/myApps/robotKaraoke/data/models/H25_humanoid_robot/H25_humanoid_robot.dae");
    
    assimpNISync.setup( &model, &openNIDevice );
//    assimpNISync.listBoneNames();
    
    assimpNISync.syncBoneAndOpenNIJoint( 0, "head", 1, XN_SKEL_HEAD );
    assimpNISync.syncBoneAndOpenNIJoint( 1, "head", 1, XN_SKEL_HEAD );
    assimpNISync.syncBoneAndOpenNIJoint( 2, "head", 1, XN_SKEL_HEAD );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "head", 1, XN_SKEL_HEAD );
    assimpNISync.syncBoneAndOpenNIJoint( 0, "neck01", 1, XN_SKEL_NECK );
    assimpNISync.syncBoneAndOpenNIJoint( 2, "neck01", 1, XN_SKEL_NECK );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "neck01", 1, XN_SKEL_NECK );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "L_shoulder", 1, XN_SKEL_LEFT_SHOULDER );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "R_shoulder", 1, XN_SKEL_RIGHT_SHOULDER );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "L_elbow", 1, XN_SKEL_LEFT_ELBOW );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "R_elbow", 1, XN_SKEL_RIGHT_ELBOW );
    assimpNISync.syncBoneAndOpenNIJoint( 2, "L_wrist", 1, XN_SKEL_LEFT_WRIST );
    assimpNISync.syncBoneAndOpenNIJoint( 2, "R_wrist", 1, XN_SKEL_RIGHT_WRIST );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "L_hip", 1, XN_SKEL_LEFT_HIP );
    assimpNISync.syncBoneAndOpenNIJoint( 3, "R_hip", 1, XN_SKEL_RIGHT_HIP );
    
    light.enable();
    ofEnableDepthTest();
    soundStream.setup( this, 0, 1, 44100, 512, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    openNIDevice.update();
    //assimpNISync.update();
    
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
    openNIDevice.drawSkeletons();
    
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
    model.waggle();
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

void ofApp::audioReceived(float *input, int bufferSize, int nChannels) {
    
}