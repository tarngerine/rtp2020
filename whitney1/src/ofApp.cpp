#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();
  gui.add(param1.setup("param 1", .5, 0, 1));
  gui.add(param2.setup("param 2", .5, 0, 1));
  gui.add(param3.setup("param 3", .5, 0, 1));
  gui.add(param4.setup("param 4", .5, 0, 1));
//  gui.add(param5.setup("param 5", 1, .001, 1));
//  gui.add(param6.setup("param 6", 1, .001, 1));
//  gui.add(param7.setup("param 7", 1, .001, 1));
//  gui.add(param8.setup("param 8", 1, .001, 1));
  hideGui = false;
  v = 0;
  w = ofGetWidth();
  
  l.setFilled(false);
  l.setStrokeWidth(6);
  ofEnableAntiAliasing();
  ofEnableSmoothing();
  
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  if (hideGui) { gui.draw();}
  ofDrawBitmapString(v, ofGetWidth()-20, 20);
  ofSetBackgroundColor(17, 25, 27);
  ofSetColor(255, 255, 255);
  float t = ofGetElapsedTimef();
  l.clear();
  
  // Use arrow keys to navigate across versions, first version shown is case 0, scroll down to see it!
  switch(v) {
    case 4: {
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
    case 3: {
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
    case 2: {
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
    case 1: {
      // Setup masks
      
      mask.allocate(w, w, GL_RGBA);
      content.allocate(w, w, GL_RGBA);
      
      // Draw mask
      mask.begin();
      ofClear(0,0,0,0);
      ofSetColor(255);
      ofPushMatrix();
      float pad = 3;
      ofTranslate(w/4,w/8-pad);
      ofDrawRectangle(0, 0, w/2, w/4+pad+pad);
      ofPopMatrix();
      mask.end();
      
      // Draw contents
      content.begin();
      ofClear(0,0,0,0);
      ofSetColor(255);
      ofPushMatrix();
      ofTranslate(w/2, w/2);
      ofTranslate(0,-w/4);
      slideCirc();
      ofTranslate(-w/2,0);
      slideCirc();

      ofPopMatrix();
      content.end();
      content.getTexture().setAlphaMask(mask.getTexture());
      
      for (int i = 0; i < 5; i++) {
        ofPushMatrix();
        ofTranslate(w/2, w/2);
        ofRotateDeg(360.*(float)i/5.);
        ofRotateDeg(10*t);
        content.setAnchorPercent(.5, .5);
        content.draw(0, 0);
        ofPopMatrix();
      }
      
      break;
    }
      
    case 0: {
      // Setup masks
      mask.allocate(w, w, GL_RGBA);
      content.allocate(w, w, GL_RGBA);
      
      // Draw mask
      mask.begin();
      ofClear(0,0,0,0);
      ofSetColor(255);
      ofPushMatrix();
      float pad = 3;
      ofTranslate(w/4,w/8-pad);
      ofDrawRectangle(0, 0, w/2, w/4+pad+pad);
      ofPopMatrix();
      mask.end();
      
      // Draw contents
      content.begin();
      ofClear(0,0,0,0);
      ofSetColor(255);
      ofPushMatrix();
      ofTranslate(w/2, w/2);
      ofTranslate(0,-w/4);
      slideCirc();
      ofTranslate(-w/2,0);
      slideCirc();

      ofPopMatrix();
      content.end();
      content.getTexture().setAlphaMask(mask.getTexture());
      
      for (int i = 0; i < 5; i++) {
        ofPushMatrix();
        ofTranslate(w/2, w/2);
        ofRotateDeg(360.*(float)i/5.);
        ofRotateDeg(10*t);
        content.setAnchorPercent(.5, .5);
        content.draw(0, 0);
        ofPopMatrix();
      }
      
      break;
    }
  }
}

void ofApp::slideCirc() {
  l.newSubPath();
  l.clear();
  int ct = 36;
  float r = w/8;
  for (int i = 0; i < ct; i++) {
    float ctf = (float)ct;
    float prg = (float)i/(ctf-2.); // double up on first point, and considering i < ct means ct - 1 - 1
    float angle = TWO_PI*prg + (PI/2.); // start from bottom by rotating 90deg
    float slide = ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, r*4);
    float x = r * -cos(angle) + prg*slide;
    float y = r * sin(angle);
    
    if (v == 0) {
      x += ofMap(param1,0,1,-50,50)*100*sin(angle*param2*TWO_PI)*sin(angle*param4*TWO_PI);
      y += ofMap(param3,0,1,-50,50)*100*cos(angle*param4*TWO_PI)*cos(angle*param4*TWO_PI);
    }
    l.curveTo(x,y);
//    ofDrawCircle(x, y, 3);
  }
  
  l.draw();
  //  grab the line, resample it and draw with circles:
  ofPolyline line = l.getOutline()[0];
  line = line.getResampledBySpacing(2.5);
  for (int i = 0; i < line.size(); i++){
    ofDrawCircle(line[i], 2.5);
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
