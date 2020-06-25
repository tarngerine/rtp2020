#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "screenshot.hpp"

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
		
  ofImage img1;
  ofImage img2;
  ofImage img3;
  ofImage img4;
  ofImage img5;
  ofImage img6;
  ofImage img7;
  ofImage img8;
  
  ofSpherePrimitive sphere;
  ofEasyCam cam;
  ofTexture texture;
  ofLight light;
  ofFbo fbo;
  ofMesh mesh;
  
  screenshotUtil screenshot;
  
  ofColor safeImgColor(ofImage & img, int x, int y);
  void dilate( ofImage & imgSrc, ofImage & imgDest);
  void subtract( ofImage & img, ofImage & sub);
  void transparent(ofImage & src,ofImage & dest);
  void colorize( ofImage & imgSrc, ofImage & imgDest);

  void warp(ofImage & imgSrc, ofImage & imgDest, bool flip);
  
  float freq;
  float amp;
  ofxPanel gui;
  ofxFloatSlider freq1;
  ofxFloatSlider freq2;
  ofxFloatSlider amp1;
  ofxFloatSlider amp2;
  
  bool orbify;
  bool shouldUpdate;
};
