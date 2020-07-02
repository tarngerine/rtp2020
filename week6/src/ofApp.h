#pragma once

#include "ofMain.h"

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
  int mode(vector <float> &array);
  vector <ofImage> loadImages(string dir, int w, int h);
  void processImages(bool isHSB, vector <ofImage> &images, int w, int h, ofImage &result1, ofImage &result2, ofImage &result3, ofImage &result4, bool processFour);
  
  void everyFrame(bool isHSB, vector <ofImage> &images, int w, int h, ofImage &result1);

  ofColor repColor(ofImage &image);
		
  ofImage derp;
  
  ofImage result1_1;
  ofImage result1_2;
  ofImage result1_3;
  ofImage result1_4;
  
  ofImage result2_1;
  ofImage result2_2;
  ofImage result2_3;
  ofImage result2_4;
  bool bgon;
  float scale;
  int ww;
  int hh;
};
