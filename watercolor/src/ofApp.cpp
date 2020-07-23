#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofEnableAlphaBlending();
  shader.load("", "shader.frag");
  dry.load("", "dry.frag");
  wet.load("", "wet.frag");
  shader2.load("", "shader2.frag");
  fbo1.allocate(ofGetWidth(),ofGetHeight());
  fbo1.begin();
    ofClear(255,255,255,255);
  fbo1.end();
 
  // need to allocate GL_RGBA32F_ARB to have enough bit precision for subtle alphas
  fbo2.allocate(ofGetWidth(),ofGetHeight(), GL_RGBA32F_ARB);
  fbo2.begin();
    ofClear(255,255,255,255);
  fbo2.end();
  canvas.allocate(ofGetWidth(),ofGetHeight(), GL_RGBA32F_ARB);
  canvas.begin();
    ofClear(255,255,255,255);
  canvas.end();
  
  // instantiate wetness matrix
  // as you draw it'll increase wetness
  // wetness wil gradually reduce as it "bleeds" via shader
  // 0 0 0
  // 0 0 0
  // 0 0 0
  wetness.allocate(ofGetWidth(),ofGetHeight(), GL_RGBA);
  wetness.begin();
    ofClear(0,0,0,255);
  wetness.end();
   wetnessp.allocate(ofGetWidth(),ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofApp::update(){
  if (ofGetFrameNum()%60) {
    shader.load("", "shader.frag");
    wet.load("", "wet.frag");
    dry.load("", "dry.frag");
    shader2.load("", "shader2.frag");
  }
  brush.clear();

  for(int i=0;i<=8;i++) {
    float prg = ofMap(i,0,8,0,M_PI*2);
    brush.addVertex(100*cos(prg), 100*sin(prg));
  }
  
  float offset = 80;
  float t = ofGetElapsedTimef();
  float noiseX = mouse.x + t;
  float noiseY = mouse.y + t;
  float recurse = 4;

  for(int depth=0;depth<recurse;depth++) {
    int pts = brush.size();
    for(int i=pts-1;i>0;i--) {
      // get middle() of points and offset by noise
      ofPoint mid = ofVec2f(brush[i]).middle(ofVec2f(brush[(i-1+pts)%pts]));
      mid.x += (ofNoise(mid.x * noiseX) - .5) * offset;
      mid.y += (ofNoise(mid.y * noiseY) - .5) * offset;
      brush.insertVertex(mid, i);
    }
  }
  
  if (isDrawing) {
    brush = brush.getSmoothed(3);

    if (abs(velocity.x) < 2 && abs(velocity.y) < 2) {
      stampSize = MIN(stampSize + .01, 1.5);
    } else {
      stampSize = MAX(stampSize - .01, 1.);
    }
    
    stamp.clear();
    for(int i=0; i<brush.size();i++) {
      stamp.lineTo(brush[i]);
    }
    stamp.close();
  }
  
  // reduce wetness
  
//  wetness.readToPixels(wetnessp);
//  for(int y=0;y<wetnessp.getHeight();y++) {
//    for(int x=0;x<wetnessp.getWidth();x++) {
//      wetnessp.setColor(x, y, ofColor(MAX((wetnessp.getColor(x,y).getBrightness() - 1), 0)));
//    }
//  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // dry wetness
  wetness.begin();
    dry.begin();
      dry.setUniformTexture("wetness", wetness, 1);
      dry.setUniform1f("w", ofGetWidth());
      ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    dry.end();
  wetness.end();
  
  ofBackground(0);
  // Brush preview
  fbo1.begin();
    ofClear(0);
    ofSetColor(255,255,0);
    ofPushMatrix();
    ofTranslate(mouse.x,mouse.y);
    brush.draw();
    ofPopMatrix();
  fbo1.end();

  if (isDrawing) {
    // Draw newest stamp in to determine wetness
    fbo2.begin();
      ofClear(0,0,0,0);
      ofPushMatrix();
      ofTranslate(mouse);
      ofScale(stampSize);
    // not enough bit precision for such a low alpha
    stamp.setFillColor(ofColor(0,0,0,40));
      stamp.draw();
      ofPopMatrix();
    fbo2.end();
    

    // composite to canvas
    canvas.begin();
      ofSetColor(255);
      fbo2.draw(0,0);
    canvas.end();
    
//    // add to wetness matrix
//    ofPixels pxl;
//    fbo2.readToPixels(pxl, 0);
//    for(int y=0;y<pxl.getHeight();y++) {
//      for(int x=0;x<pxl.getWidth();x++) {
//        ofColor clr = pxl.getColor(x, y);
//        if (clr.a > 0) {
//          // add 5 frames of wetness
//          ofColor clr = wetnessp.getColor(x, y);
//          // max out at 255, dont loop
//          wetnessp.setColor(x, y, ofColor(MIN((clr.getBrightness() + 5), 255)));
//        }
//      }
//    }

    wetness.begin();
      wet.begin();
        wet.setUniformTexture("stamp", fbo2, 1);
        wet.setUniformTexture("wetness", wetness, 2);
        wet.setUniform1f("w", ofGetWidth());
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
      wet.end();
    wetness.end();
  }
  
  ofSetColor(255);

  fbo2.begin();
    ofClear(0,0,0,0);
    shader.begin();
    shader.setUniformTexture("canvas", canvas, 1);
    shader.setUniformTexture("wetness", wetness, 2);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    shader.end();
  fbo2.end();

  fbo2.draw(0,0);
  fbo1.draw(0,0);
  
  // debug preview wetness
  
  fbo2.begin();
    ofClear(0,0,0,0);
    shader2.begin();
    shader2.setUniformTexture("wetness", wetness, 1);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    shader2.end();
  fbo2.end();
  fbo2.readToPixels(wetnessp);
  fbo2.draw(400,400);
  for(int y=0;y<20;y++) {
    for(int x=0;x<20;x++) {
      string str = ofToString((float)wetnessp.getColor(x, y).r);
      ofDrawBitmapString(str, x*15., y*15.);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  mouse.x = x;
  mouse.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  velocity = ofVec2f(x - mouse.x, y - mouse.y);
  mouse.x = x;
  mouse.y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  isDrawing = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  isDrawing = false;
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
