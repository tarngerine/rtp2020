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
  
  
  // set all pixels to a matrix of 0 and 1
  matrixbool = vector<vector<int>>(img.getWidth(), vector<int>(img.getHeight(), 0) );
  // track matrix of component IDs
  matrixcomponents = vector<vector<int>>(img.getWidth(), vector<int>(img.getHeight(), 0) );
  int componentId = 1;
  for (int i=0; i<img.getWidth(); i++) {
    for (int j=0; j<img.getHeight(); j++) {
      if (img.getColor(i,j) == ofColor(255)) {
        matrixbool[i][j] = 1;
        matrixcomponents[i][j] = componentId++;
      }
    }
  }

  int w = matrixcomponents.size();
  int h = matrixcomponents[0].size();
  for (int x=0; x<w; x++) {
    for (int y=0; y<h; y++) {
      // if is white pixel
      if (matrixcomponents[x][y] > 0) {
        // step out and change the neighbors who are >0 to the lowest id around
        int curidx = leastAround(x,y,matrixcomponents);
        matrixcomponents[x][y] = curidx;
        
        // top
        if (y+1 < h &&
            matrixcomponents[x][y+1] > 0) {
          matrixcomponents[x][y+1] = curidx;
        }
        // top right
        if (y+1 < h &&
            x+1 < w &&
            matrixcomponents[x+1][y+1] > 0) {
          matrixcomponents[x+1][y+1] = curidx;
        }
        // right
        if (x+1 < w &&
            matrixcomponents[x+1][y] > 0) {
          matrixcomponents[x+1][y] = curidx;
        }
        // bottom right
        if (y-1 >= 0 &&
            x+1 < w &&
            matrixcomponents[x+1][y-1] > 0) {
          matrixcomponents[x+1][y-1] = curidx;
        }
        // bottom
        if (y-1 >= 0 &&
            matrixcomponents[x][y-1] > 0) {
          matrixcomponents[x][y-1] = curidx;
        }
        // bottom left
        if (y-1 >= 0 &&
            x-1 >= 0 &&
            matrixcomponents[x-1][y-1] > 0) {
          matrixcomponents[x-1][y-1] = curidx;
        }
        // left
        if (x-1 >= 0 &&
            matrixcomponents[x-1][y] > 0) {
          matrixcomponents[x-1][y] = curidx;
        }
        // top left
        
        if (y+1 < h &&
            x-1 >= 0 &&
            matrixcomponents[x-1][y+1] > 0) {
          matrixcomponents[x-1][y+1] = curidx;
        }
      }
    }
  }
}

// get the lowest component index in 8 directions
int ofApp::leastAround(int x,int y, vector<vector<int>> & matrix) {
  int lowest = matrix[x][y];
  
  int w = matrix.size();
  int h = matrix[0].size();
  // top
  if (y+1 < h &&
      matrix[x][y+1] > 0) {
    lowest = min(lowest,matrix[x][y+1]);
  }
  // top right
  if (y+1 < h &&
      x+1 < w &&
      matrix[x+1][y+1] > 0) {
    lowest = min(lowest,matrix[x+1][y+1]);
  }
  // right
  if (x+1 < w &&
      matrix[x+1][y] > 0) {
    lowest = min(lowest,matrix[x+1][y]);
  }
  // bottom right
  if (y-1 >= 0 &&
      x+1 < w &&
      matrix[x+1][y-1] > 0) {
    lowest = min(lowest,matrix[x+1][y-1]);
  }
  // bottom
  if (y-1 >= 0 &&
      matrix[x][y-1] > 0) {
    lowest = min(lowest,matrix[x][y-1]);
  }
  // bottom left
  if (y-1 >= 0 &&
      x-1 >= 0 &&
      matrix[x-1][y-1] > 0) {
    lowest = min(lowest,matrix[x-1][y-1]);
  }
  // left
  if (x-1 >= 0 &&
      matrix[x-1][y] > 0) {
    lowest = min(lowest,matrix[x-1][y]);
  }
  // top left
  
  if (y+1 < h &&
      x-1 >= 0 &&
      matrix[x-1][y+1] > 0) {
    lowest = min(lowest,matrix[x-1][y+1]);
  }
  return lowest;
}

//--------------------------------------------------------------
void ofApp::draw(){
  img.draw(0,0);
  vector <int> uniqIds;
  vector <ofPoint> uniqIdFirstPoint;
  ofSetColor(ofColor(255,0,0));
  int w = matrixcomponents.size();
  int h = matrixcomponents[0].size();
  for (int x=0; x<w; x++) {
    for (int y=0; y<h; y++) {
      int curidx = matrixcomponents[x][y];
      if (curidx > 0) {
        
        if (find(uniqIds.begin(),uniqIds.end(),curidx) == uniqIds.end()) {
          uniqIds.push_back(curidx);
          uniqIdFirstPoint.push_back(ofPoint(x,y));
        }
      }
    }
  }
  ofSetColor(ofColor(255));
  ofDrawBitmapString(to_string(uniqIds.size()) + " components found", 0, 20);
  // generate colors
  map<int,ofColor> colors;
  ofSeedRandom(0);
  for(int i=0;i<uniqIds.size();i++) {
    colors[uniqIds[i]] = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
  }
  for(int i=0;i<uniqIdFirstPoint.size();i++) {
    ofSetColor(colors[uniqIds[i]]);
    ofDrawBitmapString(to_string(i), uniqIdFirstPoint[i].x, uniqIdFirstPoint[i].y);
  }
  ofSetColor(ofColor(255));
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
