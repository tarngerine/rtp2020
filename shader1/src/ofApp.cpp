#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  shader.load("", "shader.frag");
  grabber.listDevices();
  grabber.setDeviceID(1);
  grabber.setup(ofGetWidth(), ofGetHeight());
  fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
  grabber.update();
  if (ofGetFrameNum()%60) shader.load("", "shader.frag");
  
}

//--------------------------------------------------------------
void ofApp::draw(){
  fbo.begin();
  ofClear(255.);
  ofSetLineWidth(10);
  ofSetColor(0);
  line.draw();
  fbo.end();
  
  ofSetColor(255);
  shader.begin();
  shader.setUniform1f("time", ofGetElapsedTimef());
  shader.setUniform2f("mouse", mouseX, mouseY);
  shader.setUniformTexture("img", grabber, 0);
  shader.setUniformTexture("line", fbo, 1);
  ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
  shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  line.clear();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  line.addVertex(x,y);
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
