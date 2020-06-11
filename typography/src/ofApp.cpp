#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofTrueTypeFontSettings settings("Lantinghei TC Heavy", 40);
  settings.antialiased = true;
  settings.dpi = 72;
  settings.addRanges(ofAlphabet::Chinese);
//  settings.addRanges(ofAlphabet::Latin);
  settings.contours = true;
  font.load(settings);
  
//  mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
  mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
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
      polylines[j].draw();
//      ofTessellator tes;
//      tes.tessellateToMesh(polylines[j], OF_POLY_WINDING_NONZERO, mesh);
      for (int k = 0; k < polylines[j].size(); k++){
//        ofDrawCircle(polylines[j][k], .3);
        mesh.addVertex(polylines[j][k]);
//        float pct1 = ofMap((j+1)*(k+1), 0, (polylines.size()+1)*(polylines[j].size()+1), 0, 1);
//        float pct2 = ofMap((j+1)*(k+1), 0, (polylines.size()+1)*(polylines[j].size()+1), 1, 0);
//        mesh.addColor(ofColor(255 * pct1, 255 * pct2, 255 * pct1*pct2));
        mesh.addColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
      }
      mesh.draw();
    }
  }

  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
