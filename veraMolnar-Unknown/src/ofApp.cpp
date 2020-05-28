#include "ofApp.h"
#include "ofxShivaVGRenderer.h"

//--------------------------------------------------------------
void ofApp::setup(){

//  ofSetCurrentRenderer(shared_ptr<ofxShivaVGRenderer>(new ofxShivaVGRenderer));
  attempt = 3;
  
  gui.setup();
  gui.add(noiseFactor1.setup("noise factor 1", 92.5, 0, 100));
  gui.add(noiseFactor2.setup("noise factor 2", 59, 0, 100));
  gui.add(color.setup("color lerp", 0, 0, 1));
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
  float colorLerp = (cos(ofGetElapsedTimef()/8) + 1) /2;
  float rotLerp = ofGetElapsedTimef()/4;
  ofColor beige = ofColor(248, 244, 238);
  ofColor darkBlue = ofColor(10,14,43);
  ofColor lightBlue = ofColor(229,229,233);
  ofBackground(ofColor(0).lerp(beige, colorLerp));
  ofSetColor(0);
  ofDrawBitmapString(attempt, 10, 22);

  // Interruptions (2013)
  int ct = 5;
  int dim = 675/ct;
  ofPushMatrix();
  ofTranslate(dim*3/4, dim*5/4);
  ofRotateDeg(ofNoise(noiseFactor1) * 2 - 7);
  
  if (attempt >= 3) {
    ofSetColor(229,229,233);
    ofSetColor(darkBlue.lerp(lightBlue, colorLerp));
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofBeginShape();
    for (int i = 0; i < ct; i++) {
      for (int j = 0; j < ct; j++) {
        float rot = ofNoise(i*rotLerp, j*rotLerp) * 20 - 10;
        
        ofVec2f topleft = ofVec2f(-dim/2,-dim/2);
        ofVec2f bottomleft = ofVec2f(-dim/2,dim/2);
        ofVec2f bottomright = ofVec2f(dim/2,dim/2);
        ofVec2f topright = ofVec2f(dim/2,-dim/2);
        topleft.rotate(rot);
        bottomleft.rotate(rot);
        bottomright.rotate(rot);
        topright.rotate(rot);
        
        ofVec2f translation = ofVec2f(i*dim, j*dim);
        topleft += translation;
        bottomleft += translation;
        bottomright += translation;
        topright += translation;
        
        ofVertex(topleft.x, topleft.y);
        ofVertex(bottomleft.x, bottomleft.y);
        ofVertex(bottomright.x, bottomright.y);
        ofVertex(topright.x, topright.y);
        ofNextContour(true);
      }
    }
    ofEndShape(true);
  }
  
  // Intersected shapes
  ofSetPolyMode(OF_POLY_WINDING_ABS_GEQ_TWO);

  ofSetColor(ofColor(248, 244, 238).lerp(ofColor(10,14,43), colorLerp));
  ofBeginShape();
  for (int i = 0; i < ct; i++) {
    for (int j = 0; j < ct; j++) {
      switch (attempt) {
        case 0:
          ofRotateDeg(ofNoise(0) * 30);
          ofDrawRectangle(i, j, dim, dim);
          break;
        case 1:
          ofTranslate(i*dim, j*dim);
          ofRotateDeg(ofNoise(0) * 5 + 15);
          ofDrawRectangle(i, j, dim, dim);
          break;
        case 2:
          ofPushMatrix(); // Needed because the translates would pile on otherwise
          ofTranslate(i*dim, j*dim);
          ofRotateDeg(ofNoise(i, j) * 5);
          ofDrawRectangle(0, 0, dim, dim);
          ofPopMatrix();
          break;
        case 3:
          float rot = ofNoise(i*rotLerp, j*rotLerp) * 20 - 10;
          
          ofVec2f topleft = ofVec2f(-dim/2,-dim/2);
          ofVec2f bottomleft = ofVec2f(-dim/2,dim/2);
          ofVec2f bottomright = ofVec2f(dim/2,dim/2);
          ofVec2f topright = ofVec2f(dim/2,-dim/2);
          topleft.rotate(rot);
          bottomleft.rotate(rot);
          bottomright.rotate(rot);
          topright.rotate(rot);
          
          ofVec2f translation = ofVec2f(i*dim, j*dim);
          topleft += translation;
          bottomleft += translation;
          bottomright += translation;
          topright += translation;
          
          ofVertex(topleft.x, topleft.y);
          ofVertex(bottomleft.x, bottomleft.y);
          ofVertex(bottomright.x, bottomright.y);
          ofVertex(topright.x, topright.y);
          ofNextContour(true);
          break;
      }
    }
  }
  ofEndShape(true);
  ofPopMatrix();
  if (guiDraw) {
    gui.draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch (key) {
    case 57358: // right arrow
      attempt++;
      break;
    case 57356: // left arrow
      attempt--;
      break;
    case 'h':
      guiDraw = !guiDraw;
      break;
    case 't':
      thicc = !thicc;
      break;
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
