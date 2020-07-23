#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  grabber.setDeviceID(1);
  grabber.setup(640,640);
  img.allocate(640,640, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
  grabber.update();
  
  for(int y=0; i<grabber.getHeight(); i++) {
    
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  grabber.draw(0,0);
  img.draw(grabber.getWidth(),0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
