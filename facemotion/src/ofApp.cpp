#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofEnableAlphaBlending();
  grabber.listDevices();
  grabber.setDeviceID(1);
  grabber.initGrabber(ofGetWidth(), ofGetHeight());
  gray.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
  bg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
  fg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
  prevfg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
  difffg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
}

//--------------------------------------------------------------
void ofApp::update(){
  grabber.update();
  if (grabber.isFrameNew()) {
    convertColor(grabber,gray,CV_RGB2GRAY);
    gray.update();
    
    if (isRecordBg) {
      bg.setFromPixels(gray.getPixels());
      bg.update();
      isRecordBg = false;
    }
    
    absdiff(gray, bg, fg);
    fg.update();
    threshold(fg,32);
    absdiff(prevfg, fg, difffg);
    difffg.update();
    prevfg.setFromPixels(fg.getPixels());

    finder.setSortBySize(true);
    finder.findContours(fg);
    ofPolyline line = finder.getPolyline(0);
    if (line.size() > 0) {
      ofPoint top = line[0];
      for (int i=1;i<line.size();i++) {
        if (line[i].y < top.y) {
          top = line[i];
        }
      }
      top.x = line.getCentroid2D().x;
      top.y -= 40 + 20*sin(ofGetElapsedTimef()*4);
      
      velocity = pt - top; // prev pt

      // dont store trail if slow
      if (abs(velocity.x) > 5 || abs(velocity.y) > 5 ) {
        trail.addVertex(top);
      } else if (trail.size() > 0) {
        trail.getVertices().erase(trail.getVertices().begin());
      }
      pt = top;
    }

    if (trail.size() > 20) {
      trail.getVertices().erase(trail.getVertices().begin());
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(80);
  grabber.draw(0,0);
  ofSetColor(255);
//  gray.draw(ofGetWidth(),0);
//  fg.draw(0,ofGetHeight());
//  difffg.draw(ofGetWidth(),ofGetHeight());
  if (finder.size()) {
    finder.getPolyline(0).draw();
  }
  
  // point
  ofSetColor(0,0,255);
  ofPushMatrix();
  ofTranslate(pt);
  ofRotateRad(-atan2(velocity.x, velocity.y) + M_PI/2);
  ofScale(ofMap(hypot(velocity.x,velocity.y), 0, 100, 1, 3), 1);
//  ofSetColor(0,0,ofMap(hypot(velocity.x,velocity.y), 0, 100, , 255));
  ofDrawCircle(0,0,24);
  ofPopMatrix();
  
  return;
  // trail
  
  for (int i=0; i<trail.size();i++) {
    ofSetColor(0,0,255,127);
    ofDrawCircle(trail.getVertices()[i], 10);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key=='r') {
    isRecordBg = true;
  }
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
