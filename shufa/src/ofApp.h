#pragma once

#include "ofMain.h"
#include "ofxTablet.h"

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
  ofFbo fbo1;
  ofFbo fbo2;
  ofFbo canvas;
  ofPolyline brush;
  ofPolyline line1;
  ofPolyline trail;
  ofPolyline trailResampled;
  vector<float> trailPressure;
  vector<float> trailColor;
  vector<float> trailSpeed;
  vector<float> trailSize;
  ofVec2f mouse = ofVec2f(0,0);
  ofPath stamp;
  bool isDrawing;
  ofVec2f velocity = ofVec2f(0,0);
  float stampSize = 1.;

  ofPixels wetnessp;
  ofImage wetnessImg;
  ofFbo wetness;
  ofShader shader;
  ofShader dry;
  ofShader wet;
  ofShader shader2;
  ofShader dialate;
  vector<int> wetness1d;
  
  void tabletMoved(TabletData &data);
  bool usingTablet = false;
  float pressure = 1;
  float speed = 1;
  
  vector<float> alphaResampled;
  
  void initCanvas();
  bool showTut = true;
};
