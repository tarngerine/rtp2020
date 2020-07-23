#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  grabber.listDevices();
  grabber.setDeviceID(1);
  grabber.setup(480,480);
}

//--------------------------------------------------------------
void ofApp::update(){
  grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
//  grabber.draw(0,0);
  
  for(int y = 0; y < grabber.getHeight(); y+=5) {
    ofPolyline l;

    for(int x = 0; x < grabber.getHeight(); x++) {
      float b = grabber.getPixels().getColor(x,y).getBrightness();
      l.addVertex(x, y + ofMap(b, 0, 255, 0, mouseX));
    }
    
    l = l.getSmoothed(mouseY);
    l.draw();
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
