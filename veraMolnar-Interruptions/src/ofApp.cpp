#include "ofApp.h"
#include "ofxShivaVGRenderer.h"

//--------------------------------------------------------------
void ofApp::setup(){

//  ofSetCurrentRenderer(shared_ptr<ofxShivaVGRenderer>(new ofxShivaVGRenderer));
  attempt = 12;
  
  gui.setup();
  gui.add(noiseFactor1.setup("noise factor 1", 92.5, 0, 100));
  gui.add(noiseFactor2.setup("noise factor 2", 59, 0, 100));

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw attempt
  ofBackground(255);
  ofSetColor(0);
  ofDrawBitmapString(attempt, 10, 22);

  // Interruptions (2013)
  int ct = 32;
  int dim = 768/ct;
  ofPushMatrix();
  ofTranslate(16,4);
  
  int thiccness = dim - 4;
  // Thicc
  if (thicc) {
    ofSetLineWidth(thiccness);
  } else {
    ofSetLineWidth(1);
  }
  
  for (int i = 0; i < ct; i++) {
    for (int j = 0; j < (ct + 1); j++) {
      switch (attempt) {
        case 0:
          ofDrawLine(i, j, i * dim, j * dim);
          break;
        case 1:
          ofDrawLine(i * dim, j * dim, (i + 1) * dim, (j + 1) * dim);
          break;
        case 2:
          ofDrawLine(i * dim, j * dim + 16, (i + 1) * dim, j * dim + 16);
          break;
        case 3:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i * .01, j * .01) < .9) {
            ofRotateDeg(ofRandom(90));
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 4:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i * .01, j * .01) < .9) {
            ofRotateDeg(ofNoise(i, j) * 90);
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 5:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i * .01, j * .01) > .6) {
            ofRotateDeg(ofNoise(i, j) * 90);
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 6:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i, j) > .6) {
            ofRotateDeg(ofNoise(i, j) * 90);
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 7:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i, j) > .9) {
            ofRotateDeg(ofNoise(i, j) * 90);
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 8:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i, j) > .9) {
            ofRotateDeg(ofNoise(i*10, j*10) * 90);
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 9:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i, j) > .9) {
            ofRotateDeg(ofNoise(i*10, j*10) * 180 - 90);
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 10:
          ofPushMatrix();
          ofTranslate(i * dim, j * dim);
          if (ofNoise(i, j) > .9) {
            ofRotateDeg(pow(ofNoise(i*10, j*10), 2) * 180 - 90);
          }
          ofDrawLine(0,dim/2,dim,dim/2);
          ofPopMatrix();
          break;
        case 11:
          ofPushMatrix();
          ofTranslate(i * dim + dim/2, j * dim + dim/2);
          if (ofNoise(i*noiseFactor1, j*noiseFactor1) > .9) {
            ofRotateDeg(sin(ofNoise(i*noiseFactor2, j*noiseFactor2)) * 180 - 90);
          }
          ofDrawLine(-dim/2,0,dim/2,0);
          ofPopMatrix();
          break;
        case 12:
          ofPushMatrix();
          ofTranslate(i * dim + dim/2, j * dim + dim/2);
          if (ofNoise(i*noiseFactor1, j*noiseFactor1) > .9) {
            ofRotateDeg(sin(ofNoise(i*noiseFactor2, j*noiseFactor2)) * 180 - 90);
          }
          ofDrawLine(-dim/2,0,dim/2,0);
          if (thicc) {
            ofDrawCircle(-dim/2, 0, thiccness/2);
            ofDrawCircle(dim/2, 0, thiccness/2);
          }
          ofPopMatrix();
          break;
      }
    }
  }
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
