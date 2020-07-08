#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofEnableAlphaBlending();

  dir.listDir();

  steps.push_back(ofPoint(0,1));
  steps.push_back(ofPoint(1,1));
  steps.push_back(ofPoint(1,0));
  steps.push_back(ofPoint(1,-1));
  steps.push_back(ofPoint(0,-1));
  steps.push_back(ofPoint(-1,-1));
  steps.push_back(ofPoint(-1,0));
  steps.push_back(ofPoint(-1,1));
  
  componentImg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
  img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofApp::update(){
  img.load(dir.getPath(idx));
  
  // find white pixels for current image
  for (int i=0; i<img.getWidth(); i++) {
      for (int j=0; j<img.getHeight(); j++) {
        // TODO: is in existing components? if so, skip

        if (img.getColor(i, j) == ofColor(255)) {
          vector <ofPoint> pts = stepOut(ofPoint(i,j));
          pts.push_back(ofPoint(i,j));
          
          // add to components
          components.push_back(pts);
        }
      }
  }
  for (int i=0; i<img.getWidth(); i++) {
    for (int j=0; j<img.getHeight(); j++) {
      componentImg.setColor(i,j, ofColor(255,255,255, 0));
    }
  }
  for(int i=0; i<components.size(); i++) {
    vector <ofPoint> pts = components[i];
    for(int j=0; j<pts.size(); j++) {
      componentImg.setColor(pts[j].x, pts[j].y, ofColor(255,255,255,255));
    }
  }
}

vector <ofPoint> ofApp::stepOut(ofPoint pt) {
  vector <ofPoint> pts;
  
  ofPoint newpt;
  ofColor newclr;
  for(int i = 0; i < steps.size(); i++ ) {
    newpt = pt + steps[i];
      // if in bounds
      if (newpt.x < img.getWidth() &&
          newpt.x >= 0 &&
          newpt.y < img.getHeight() &&
          newpt.y >= 0) {
        // get pixel
        newclr = img.getColor((int)newpt.x, (int)newpt.y);
        // if white, add to vector
        if (newclr == ofColor(255)) {
          pts.push_back(newpt);
        }
      }
  }

  // recurse on newly found points
  for(int i=0; i<pts.size(); i++) {
    vector <ofPoint> recursedpts = stepOut(pts[i]);
    pts.insert(pts.end(), recursedpts.begin(), recursedpts.end());
  }
  
  return pts;
}

//--------------------------------------------------------------
void ofApp::draw(){
  img.draw(0,0);
  componentImg.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == OF_KEY_RIGHT) {
    idx = (idx + 1) % dir.size();
  } else if (key == OF_KEY_LEFT) {
    idx = (idx - 1) % dir.size();
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
