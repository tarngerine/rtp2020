#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//  ofGLFWWindowSettings settings;
//  settings.stencilBits = 8;
//  settings.setSize(800, 800);
//
//  auto window = ofCreateWindow(settings);
//  auto app = make_shared<ofApp>();
	ofSetupOpenGL(800,800,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
//	ofRunApp(window, app);
  ofRunApp(new ofApp());
  return ofRunMainLoop();

}
