#pragma once

#include "ofMain.h"
#include <string>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
  ofDirectory dir = ofDirectory("");
  ofImage img;
  ofImage componentImg;
  int idx = 0;
  vector <vector<ofPoint>> components;
  vector <ofPoint> steps;
  
  vector <ofPoint> stepOut(ofPoint pt);
  vector <vector<int>> matrixbool;
  vector <vector<int>> matrixcomponents;
  
  void stepOut(int x,int y, vector<vector<int>> & matrix);
  int leastAround(int x,int y, vector<vector<int>> & matrix);
};
