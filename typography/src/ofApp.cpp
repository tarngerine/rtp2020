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
    colors.push_back(ofColor(ofRandom(255),ofRandom(255),ofRandom(255)));
  }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  mesh.clearVertices();
  string s = "唐";
  ofBackground(0);
//  font.drawString(s,20,100);
  ofSetColor(255);
  float scale = 10;
  float sw = font.stringWidth(s) * scale;
  float sh = font.stringHeight(s) * scale;
  float prg = ofMap(sin(ofGetElapsedTimef()),-1,1,0,1);
  
  vector < ofPath > paths = font.getStringAsPoints(s);

  ofPushMatrix();
  ofTranslate((ofGetWidth()-sw)/2, (ofGetHeight()+sh/2)/2);
  ofScale(scale);

  for (int i = 0; i < paths.size(); i++){ // One path per char
    paths[i].setPolyWindingMode(OF_POLY_WINDING_ODD);
    vector <ofPolyline> polylines = paths[i].getOutline();
    
    switch(v) {
      case 0: {
        ofMesh m;
        m.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for (int j = 0; j < polylines.size(); j++){
          for (int k = 0; k < polylines[j].size(); k++){
            ofPoint p1 = polylines[j][k];
            ofPoint p2;
            if (k+1 == polylines[j].size()) {
              p2 = polylines[j][0];
            } else {
              p2 = polylines[j][k+1];
            }
            ofPoint diff = p2 - p1;
            ofPoint normal = diff.getNormalized().rotate(-90, ofPoint(0,0,1));
//            m.addVertex(p1);
//            ofDrawCircle(p1+normal*20, 1);
//            ofDrawCircle(p2+normal*20, 1);
//            m.addVertex(p1+normal*3);
//            m.addVertex(p2+normal*3);
//            m.addVertex(p2);
//            m.addVertex(p1);
//
//            m.addColor(colors[0]);
//            m.addColor(ofColor(colors[0],0));
//            m.addColor(ofColor(colors[0],0));
//            m.addColor(colors[0]);
//            m.addColor(colors[0]);

            glBegin(GL_QUADS);
            float r = (float)colors[k].r/255.;
            float g = (float)colors[k].g/255.;
            float b = (float)colors[k].b/255.;
            glColor4f(r, g, b, 1);
            glVertex2f(p1.x, p1.y);
            glColor4f(r, g, b, 0);
            glVertex2f((p1+normal*3).x,(p1+normal*3).y);
            glColor4f(r, g, b, 0);
            glVertex2f((p2+normal*3).x,(p2+normal*3).y);
            glColor4f(r, g, b, 1);
            glVertex2f(p2.x, p2.y);
            glEnd();
          }
        }
        m.draw();
        break;
      }
      case 1: {
        for (int j = 0; j < polylines.size(); j++){
          ofPolyline line = polylines[j].getResampledBySpacing(1);
          for (int k = 0; k < line.size(); k++){
            int offset = prg * (float)line.size();
            int k2 = (k + offset)%line.size();
            mesh.addVertex(line.getPointAtIndexInterpolated(k2));
          }
        }
        mesh.draw();
        break;
      }
    }
    
  }
  if (v == 1) {
//      mesh.draw();
  }
  
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'r') {
    mesh.clearColors();
    for(int i=0; i<1000; i++) {
      mesh.addColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
    }
  }
  if(key == OF_KEY_RIGHT) {
    v++;
  }
  if(key == OF_KEY_LEFT) {
    v--;
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