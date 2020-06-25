#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


  ofEnableDepthTest();
  ofDisableArbTex();
  ofEnableAlphaBlending();
  
//  ofEnableLighting();
//  ofSetSmoothLighting(true);
//  light.enable();
//  light.setPosition(ofVec3f(100,100,200));
//  light.lookAt(ofVec3f(0,0,0));
  
  ofSetSphereResolution(24);
  sphere.setRadius(ofGetWidth()*2/8);

  img1.load("basil.png");
  img1.resize(800,800);
  img2.allocate(img1.getWidth(),img1.getHeight(),OF_IMAGE_COLOR_ALPHA); img3.allocate(img2.getWidth(),img2.getHeight(),OF_IMAGE_COLOR_ALPHA);
   img4.allocate(img2.getWidth(),img2.getHeight(),OF_IMAGE_COLOR_ALPHA);
  img5.allocate(img1.getWidth(),img1.getHeight(),OF_IMAGE_COLOR_ALPHA);
  
  
  
  
  // Hack to not see the discs
  cam.rotateDeg(-45,ofVec3f(1.,0.,0.));
  
  gui.setup();
  gui.add(freq1.setup("freq1", 6.1, 0, 20));
  gui.add(amp1.setup("amp1", 0.2, 0, .5));
  gui.add(freq2.setup("freq2", 0.00295, 0, .01));
  gui.add(amp2.setup("amp2", 0.1, 0, 1));

  int pad = 180;
  fbo.allocate(img1.getWidth() - pad*2, img1.getHeight());

  shouldUpdate = true;
}

//--------------------------------------------------------------
void ofApp::update(){
  if(shouldUpdate) {

    colorize(img1, img2);
    warp(img2, img3, true);
    warp(img3, img4, false);
    transparent(img4, img5);
    
    fbo.begin();
      ofClear(0, 0, 0);
      img5.draw(-180, 0);
    fbo.end();

    shouldUpdate = false;
  }
  sphere.rotateDeg(1,ofVec3f(0.,1.,0.));
}

//--------------------------------------------------------------
void ofApp::draw(){
  
  
  if (!orbify) {

    ofEnableDepthTest();
    ofDisableArbTex();
    ofEnableAlphaBlending();
    ofBackground(ofColor(0));
    cam.begin();
    fbo.getTexture().bind();
    sphere.draw();
    fbo.getTexture().unbind();
    cam.end();
  } else {
    ofDisableAlphaBlending();
    ofDisableDepthTest();
    ofEnableArbTex();
    ofBackground(ofColor(0));
    int w = img1.getWidth()/2;
    int h = img1.getHeight()/2;
    img1.draw(0, 0, w,h);
    img2.draw(w,0, w,h);
    img3.draw(0,h, w,h);
    img4.draw(w,h, w,h);
    gui.draw();
  }
  
  screenshot.run();
  
}


void ofApp::warp (ofImage & imgSrc, ofImage & imgDest, bool flip ) {
    float t = ofGetElapsedTimef();
      ofVec2f center = ofVec2f(imgSrc.getWidth()/2,imgSrc.getWidth()/2);
    for (int i = 0; i < imgSrc.getWidth(); i++) {
      for (int j = 0; j < imgSrc.getHeight(); j++) {
        float dist = ofVec2f(i,j).distance( center);
        float angle = ofMap(dist, 0, imgSrc.getWidth()/2, 0, 135.0);
        
        
        
        
        
        freq = freq1;
      
        float f_i = float(i)/imgSrc.getWidth();
        float f_j = float(j)/imgSrc.getWidth();
        
        // https://www.iquilezles.org/www/articles/warp/warp.htm
        ofVec2f p1 = ofVec2f(ofNoise(f_i*freq,f_j*freq), ofNoise(f_i*freq,f_j*freq)) * imgSrc.getWidth() * amp1;
        
        freq = ofMap(float(mouseX)/ofGetWidth(), 0.,1., 0.,.002);
        amp = ofMap(float(mouseY)/ofGetHeight(), 0.,1., .3,.7);
        
        freq=freq2;
        amp=amp2;
        f_i = (p1.x + f_i) * freq;
        f_j = (p1.y + f_j) * freq;
        ofVec2f p2 = ofVec2f(ofNoise(f_i+.3,f_j+.3), ofNoise(f_i,f_j)) * imgSrc.getWidth() * amp;
        
        if (flip) {
          p2 *= -1;
        }
        ofVec2f rot = ofVec2f(i,j) + p2;
        
        
        rot = rot.rotate(angle, center);
        
        
        
        ofColor color = ofColor(0);
        color = safeImgColor(imgSrc, rot.x, rot.y);
        imgDest.setColor(i,j,color);
        
//        rot *= ofVec2f((cos(t)+1)/2,(sin(t)+1)/2);
        //      if (rot.x > img1.getWidth() || rot.y > img2.getHeight() || rot.x < 0 || rot.y < 0) {
        //        color = ofColor(0);
        //      } else {
        //        color = img1.getColor(rot.x, rot.y);
        //      }
      }
    }
    imgDest.update();

}

void ofApp::colorize( ofImage & imgSrc, ofImage & imgDest){
    for (int i = 0; i < imgSrc.getWidth(); i++) {
      for (int j = 0; j < imgSrc.getHeight(); j++) {
        ofColor color = imgSrc.getColor(i, j);
        int a = color.a;
        int b = color.getBrightness();
        if (b == 0) {
          imgDest.setColor(i,j,ofColor(0,0,0,0));
        } else {
          
          color.setHsb(b, 255, 255);
          imgDest.setColor(i,j,color);
        }
        
      }
    }
  imgDest.update();
}


void ofApp::transparent(ofImage & src, ofImage & dest) {
  for (int i = 0; i < src.getWidth(); i++) {
    for (int j = 0; j < src.getHeight(); j++) {
      ofColor clr = src.getColor(i,j);
      if (clr.getBrightness() == 0) {
        dest.setColor(i,j,ofColor(0,0,0,0));
      } else {
        dest.setColor(i,j,ofColor(clr.r,clr.g,clr.b,255));
      }
    }
  }
  dest.update();
}

void ofApp::subtract(ofImage & img, ofImage & sub) {
  for (int i = 0; i < img.getWidth(); i++) {
    for (int j = 0; j < img.getHeight(); j++) {
      if (sub.getColor(i,j).getBrightness() > 127 ) {
        img.setColor(i,j,ofColor(0));
      } 
      
    }
  }
  img.update();
}

void ofApp::dilate( ofImage & imgSrc, ofImage & imgDest){
    
    // assumptions!
    // img1 / img2 same w/h
    // both grayscale / binary images
    
    for (int i = 0; i < imgSrc.getWidth(); i++){
        for (int j = 0; j < imgSrc.getHeight(); j++){
            
            // neighbors
            // edges
            
          int dist = 5;
            int i_m_1 = ofClamp(i-dist, 0, imgSrc.getWidth()-dist);
            int i_p_1 = ofClamp(i+dist, 0, imgSrc.getWidth()-dist);
            int j_m_1 = ofClamp(j-dist, 0, imgSrc.getHeight()-dist);
            int j_p_1 = ofClamp(j+dist, 0, imgSrc.getHeight()-dist);
            
            // neighbor values
            
            ofColor n_ = imgSrc.getColor(i,j_p_1);
            ofColor ne = imgSrc.getColor(i_p_1,j_p_1);
            ofColor e_ = imgSrc.getColor(i_p_1,j);
            ofColor se = imgSrc.getColor(i_p_1,j_m_1);
            ofColor s_ = imgSrc.getColor(i,j_m_1);
            ofColor sw = imgSrc.getColor(i_m_1,j_m_1);
            ofColor w_ = imgSrc.getColor(i_m_1,j);
            ofColor nw = imgSrc.getColor(i_m_1,j_p_1);
            
            if (  n_.getBrightness() > 127 ||
                  ne.getBrightness() > 127 ||
                e_.getBrightness() > 127 ||
                se.getBrightness() > 127 ||
                s_.getBrightness() > 127 ||
                sw.getBrightness() > 127 ||
                w_.getBrightness() > 127 ||
                nw.getBrightness() > 127 ){
                imgDest.setColor(i,j, ofColor(255));
            } else {
                imgDest.setColor(i,j, ofColor(0));
            }
            
            
            
        }
    }
    
    imgDest.update();
    
    
}

ofColor ofApp::safeImgColor(ofImage & img, int x, int y){
  ofColor color = ofColor(0);
  if (x < img.getWidth() && y < img.getHeight() && x > 0 && y > 0) {
    color = img.getColor(x, y);
  }
  return color;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == '3') {
    orbify = !orbify;
  }
  shouldUpdate = true;
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
  shouldUpdate = true;
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
