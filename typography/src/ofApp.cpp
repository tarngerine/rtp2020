#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofTrueTypeFontSettings settings("Lantinghei TC Heavy", 40);
  settings.antialiased = true;
  settings.dpi = 72;
  settings.addRanges(ofAlphabet::Chinese);
  settings.contours = true;
  font.load(settings);
  
  mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  
  ofSeedRandom(1);
  
  for(int i=0; i<1000; i++) {
    mesh.addColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
  }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  string s = "唐";
  ofBackground(0);
//  font.drawString(s,20,100);
  ofSetColor(255);
  float scale = 10;
  float sw = font.stringWidth(s) * scale;
  float sh = font.stringHeight(s) * scale;
  
  vector < ofPath > paths = font.getStringAsPoints(s);

  ofPushMatrix();
  ofTranslate((ofGetWidth()-sw)/2, (ofGetHeight()+sh/2)/2);
  ofScale(scale);

  for (int i = 0; i < paths.size(); i++){
    paths[i].setPolyWindingMode(OF_POLY_WINDING_ODD);
    vector <ofPolyline> polylines = paths[i].getOutline();

    for (int j = 0; j < polylines.size(); j++){
      for (int k = 0; k < polylines[j].size(); k++){
        mesh.addVertex(polylines[j][k]);
      }
    }
  }
  mesh.draw();
  
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'r') {
    mesh.clear();
    mesh.clearColors();
    for(int i=0; i<1000; i++) {
      mesh.addColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
    }
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
