#include "ofApp.h"
#include "ofxTablet.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofEnableAlphaBlending();
  ofxTablet::start();
  
  // Shaders
  shader.load("", "shader.frag");
  dry.load("", "dry.frag");
  wet.load("", "wet.frag");
  shader2.load("", "shader2.frag");
  dialate.load("", "shader2.frag");
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
  TabletData &data = ofxTablet::tabletData;
  pressure = data.pressure;
  // non tablet usage
  if (pressure == 0) pressure = 1;
  
  
  speed = ofMap(abs((velocity.x + velocity.y)/2.), 0, 50, 1, .05);
  
  if (ofGetFrameNum()%60) {
    shader.load("", "shader.frag");
    wet.load("", "wet.frag");
    dry.load("", "dry.frag");
    shader2.load("", "shader2.frag");
    dialate.load("", "dialate.frag");
  }
  brush.clear();

  for(int i=0;i<=8;i++) {
    float prg = ofMap(i,0,8,0,M_PI*2);
    brush.addVertex(50*cos(prg), 50*sin(prg));
  }
  
  float offset = 40;
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
      stampSize = MAX(stampSize - .01, .5);
    }
    
    stampSize *= speed * pressure;
    
    stamp.clear();
    for(int i=0; i<brush.size();i++) {
      stamp.lineTo(brush[i]);
    }
    stamp.close();
    
    if (abs(velocity.x + velocity.y)/2. > 1.) {
      trail.addVertex(mouse.x, mouse.y);
      trailPressure.push_back(stampSize);
    }
    if (trail.size() > 10) {
      trail.getVertices().erase(trail.getVertices().begin());
      trailPressure.erase(trailPressure.begin());
    }
    trailResampled = trail.getResampledBySpacing(5.);
  } else {
    trail.clear();
    trailResampled.clear();
    trailPressure.clear();
  }
  
  // dry wetness
  wetness.begin();
    dry.begin();
      dry.setUniformTexture("wetness", wetness, 1);
      dry.setUniform1f("w", ofGetWidth());
      ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    dry.end();
  wetness.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
  
  ofBackground(0);
  // Brush preview
//  fbo1.begin();
//    ofClear(0);
//    ofSetColor(255,255,0);
//    ofPushMatrix();
//    ofTranslate(mouse.x,mouse.y);
//    brush.draw();
//    ofPopMatrix();
//  fbo1.end();

  if (isDrawing) {
    float darkness = ofMap(pow(speed, 2), 0, 1, 10, 200);

    // Draw newest stamp in to determine wetness
    fbo2.begin();
      ofClear(0,0,0,0);
      ofPushMatrix();
      ofTranslate(mouse);
      ofScale(stampSize);
    // play with having a small version of the stamp inside the big one to simulate the brush lift effect of leaving a spot in the middle
    // play with gradiating outwards from center (dark-> light) instead of a flat color
    // play with having more than 1 stamp at once with lower opacity to have a more natural appearance
    
    // play with squash/stretch with velocity to help avoid "broken shapes" effect
    
    // play with squash/stretch depending on the direction you move your pen to allow for diff parts of a character

    
    // allow gou/hooks with a flick, map velocity to size where faster = smaller past a certain threshold
    
    
      stamp.setFillColor(ofColor(0, 0, 0, darkness));
      stamp.draw();
      ofPopMatrix();
    
    // Draw trail
    
      for(int i = 1; i < trailResampled.size(); i++) {
        ofPushMatrix();
          ofTranslate(trailResampled[i]);
          ofRotateDeg(i * 10);
        float closestSize = floor(ofMap(i, 0, trailResampled.size(), 0, trailPressure.size()));
          ofScale(trailPressure[closestSize]);
          stamp.draw();
        ofPopMatrix();
      }
    
      
    fbo2.end();
    

    // composite to canvas
    canvas.begin();
      ofSetColor(255);
      fbo2.draw(0,0);
    canvas.end();
    
    // add to wetness matrix
    wetness.begin();
      wet.begin();
        wet.setUniformTexture("stamp", fbo2, 1);
        wet.setUniformTexture("wetness", wetness, 2);
        wet.setUniform1f("w", ofGetWidth());
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
      wet.end();
    wetness.end();
  }
  
  
  // dialate wetness
  wetness.begin();
    dialate.begin();
      dialate.setUniformTexture("wetness", wetness, 1);
      dialate.setUniform1f("w", ofGetWidth());

      dialate.setUniform1f("rnd", (ofRandomf() + 1) / 2);

      dialate.setUniform1f("t", ofGetElapsedTimef());
      ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    dialate.end();
  wetness.end();
  
  ofSetColor(255);

  canvas.begin();
    
    shader.begin();
    shader.setUniformTexture("canvas", canvas, 1);
    shader.setUniformTexture("wetness", wetness, 2);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    shader.end();
  canvas.end();

  canvas.draw(0,0);
  
//  for (int i = 0; i < trailResampled.size(); i++) {
//    ofSetColor(0,0,255);
//    ofDrawCircle(trailResampled[i].x, trailResampled[i].y, 10);
//  }
//  trailResampled.draw();

//  fbo1.draw(0,0);
  
  // debug preview wetness
//
//  fbo2.begin();
//    ofClear(0,0,0,0);
//    shader2.begin();
//    shader2.setUniformTexture("wetness", wetness, 1);
//    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
//    shader2.end();
//  fbo2.end();
//  fbo2.readToPixels(wetnessp);
//  fbo2.draw(400,400);
//  ofSetColor(0,0,255);
//  for(int y=0;y<20;y++) {
//    for(int x=0;x<20;x++) {
//      string str = ofToString((float)wetnessp.getColor(x, y).r);
//      ofDrawBitmapString(str, x*15., y*15.);
//    }
//  }
//  ofSetColor(255);
  
  ofSetColor(0); ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'c') {
    wetness.begin();
    ofClear(0,0,0,255);
    wetness.end();
    canvas.begin();
    ofClear(255,255,255,255);
    canvas.end();
  }
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
