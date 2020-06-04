#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void slideCirc();

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
		
  ofxPanel gui;
  ofxFloatSlider param1;
  ofxFloatSlider param2;
  ofxFloatSlider param3;
  ofxFloatSlider param4;
//  ofxFloatSlider param5;
//  ofxFloatSlider param6;
//  ofxFloatSlider param7;
//  ofxFloatSlider param8;
  bool hideGui;
  ofFbo mask;
  ofFbo content;
  
  int v;
  int w;
  
  ofPath l;
};
