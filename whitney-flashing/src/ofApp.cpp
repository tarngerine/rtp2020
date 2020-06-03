#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();
  gui.add(param1.setup("param 1", 1, .001, 1));
  gui.add(param2.setup("param 2", 1, .001, 1));
  hideGui = false;
  v = 0;
  
//  l.setFilled(false);
//  l.setStrokeWidth(1);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  if (!hideGui) { gui.draw();}
  ofDrawBitmapString(v, ofGetWidth()-20, 20);
  ofSetColor(255, 255, 255);
  float t = ofGetElapsedTimef();
//  l.clear();
  switch(v) {
    case 1: {
      for (int i = 0; i < 80; i++) {
        float spd = ofMap(i, 0, 80, 0, 4);
        float x1 = ofMap(sin(t*param1*spd), -1, 1, 100, ofGetWidth() - 100);
        float y1 = ofMap(cos(t*param2*spd), -1, 1, 100, ofGetWidth() - 100);
        float x2 = ofMap(cos(t*param1*spd), -1, 1, 100, ofGetWidth() - 100);
        float y2 = ofMap(sin(t*param2*spd), -1, 1, 100, ofGetWidth() - 100);
        ofDrawLine(x1, y1, x2, y2);
      }
      break;
          
    }
    case 0: {
      int ct = 36;
      for (int i = 0; i < ct; i++) {
        float r = 300;
        float prg = (float)i/((float)ct-1.f); // double up on first point
        float angle = TWO_PI*prg + PI/2.;
        float slide = fmod(ofGetElapsedTimef(), 2.f) * 400;
        float x = 400 + r * -cos(angle);
        float y = 400 + r * sin(angle);
        l.lineTo(x,y);
        ofDrawCircle(x, y, 5);
      }
    }
  }
  l.close();
  l.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'g') { hideGui = !hideGui; }
  if(key == 'j') { v++; }
  if(key == 'k') { v--; }
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
