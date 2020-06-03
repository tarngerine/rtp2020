#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();
  gui.add(param1.setup("param 1", 1, .001, 1));
  gui.add(param2.setup("param 2", 1, .001, 1));
  hideGui = false;
  v = 0;
  w = ofGetWidth();
  
  l.setFilled(false);
  l.setStrokeWidth(1);

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
  l.clear();
  switch(v) {
    case 3: {
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
    case 2: {
      int ct = 36;
      for (int i = 0; i < ct; i++) {
        float r = 300;
        float prg = (float)i/((float)ct-1.f); // double up on first point
        float angle = TWO_PI*prg + PI/2.;
        float slide = fmod(ofGetElapsedTimef(), 2.f) * 400;
        float x = 400 + r * -cos(angle) + prg*slide;
        float y = 400 + r * sin(angle);
        l.lineTo(x,y);
        ofDrawCircle(x, y, 5);
      }

      l.close();
      l.draw();
      break;
    }
    case 1: {
      int ct = 36;
      float r = 100;
      
      
      for (int j = 0; j < 5; j++) {
        float dupAngle = TWO_PI/5. * (float)j;
        float dupOffsetX = w/2 + 200 * cos(dupAngle);
        float dupOffsetY = w/2 + 200 * sin(dupAngle);
//        ofPushMatrix();
//        ofTranslate(0,200);
//        ofRotateRad(param1*dupAngle*-1.f);
//        ofTranslate(w/2, w/2);
        
        for (int i = 0; i < ct; i++) {
          float prg = (float)i/((float)ct-1.f); // double up on first point
          float angle = TWO_PI*prg + PI/2.;
          float slide = fmod(ofGetElapsedTimef(), 2.f) * r*2;
          float x = r * -cos(angle) + prg*slide + dupOffsetX;
          float y = r * sin(angle) + dupOffsetY;
          l.lineTo(x,y);
          ofDrawCircle(x, y, 5);
        }
        l.newSubPath();
        l.draw();
//        ofPopMatrix();
      }
      
//      ofPopMatrix();
      break;
    }
    case 0: {
      int ct = 36;
      float r = 100;
      ofFbo mask;
      ofFbo content;
      
      // Draw mask
      mask.begin();
      ofPushMatrix();
      ofTranslate(w/2,w/4);
      ofDrawRectangle(0, 0, w/4, w/4);
      ofPopMatrix();
      mask.end();
      
      // Draw contents
      content.begin();
      ofPushMatrix();
      ofTranslate(w/2, w/2);
      ofTranslate(0,-w/4);
      for (int i = 0; i < ct; i++) {
        float prg = (float)i/((float)ct-1.f); // double up on first point
        float angle = TWO_PI*prg + PI/2.;
        float slide = fmod(ofGetElapsedTimef(), 2.f) * r*2;
        float x = r * -cos(angle) + prg*slide;
        float y = r * sin(angle);
        l.lineTo(x,y);
        ofDrawCircle(x, y, 5);
      }
      l.draw();
      ofPopMatrix();
      content.end();
      
      // Apply mask?
      content.getTexture().setAlphaMask(mask.getTexture());
      break;
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'g') { hideGui = !hideGui; }
  if(key == 57358) { v++; }
  if(key == 57356) { v--; }
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
