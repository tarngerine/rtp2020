#include "ofApp.h"

vector <ofImage> ofApp::loadImages(string dir, int w, int h) {
  vector <ofImage> images;
  ofDirectory directory;
    directory.listDir(dir);
  for(int i = 0; i < directory.size(); i++) {
    ofImage img;
    images.push_back(img);
    images.back().load(directory.getPath(i));
    images.back().resize(w,h);
  }
  return images;
}

//--------------------------------------------------------------
void ofApp::setup(){
  ww = 480;
  hh = 270;
  scale = .5;
  
  ofEnableAlphaBlending();
  int w = ww;
  int h2 = hh;
//  int h = 360;
  int h = h2;
  
//  string dir1 = "0630cam";
//  string dir1 = "o3";
    string dir1 = "owcam";
//  string dir2 = "0630";
//  string dir2 = "o3screen";
  string dir2 = "owscreen";
  
  vector <ofImage> set1 = loadImages(dir1, w, h);
  
  processImages(false, set1, w, h, result1_1, result1_2, result1_3, result1_4, true);
    
  vector <ofImage> set2 = loadImages(dir2, int(w*scale*2), int(h2*scale*2));
  processImages(false, set2, int(w*scale*2), int(h2*scale*2), result2_1, result2_2, result2_3, result2_4, false);

  everyFrame(true, set2, w, h, result2_2);
}


void ofApp::everyFrame(bool isHSB, vector <ofImage> &images, int w, int h, ofImage &result1) {
  
  float ratio = float(w)/float(h);
  // create an result image size based on the number of images, 1 pixel for every image
  int y = int(floor(sqrt(images.size()/ratio)));
  int x = int(floor(ratio*y));
  result1.allocate(x,y,OF_IMAGE_COLOR);
  
  // todo: scale up so 1 image = 4 pixels?
  
  
//  for (int k = 0; k<images.size(); k++) {
//
//    // iterate thru every pixel (i,j)
//    // for every image (k)
//    int i = k % x;
//    int j = int(floor(k/x));
//
//    // find a representative pixel (average, mode, max, min
//    ofImage img = images[k];
//    ofColor rep = repColor(img);
//
//    // write that representative pixel to current pixel
//    result1.setColor(i,j,rep);
//  }
  
  int k = 0;
  for (int i = 0; i<result1.getWidth();i++) {
    for (int j = 0; j<result1.getHeight();j++) {
      
      ofColor rep;
      if (k >= images.size()) {
        rep = ofColor(0);
      } else {
        ofImage img = images[k];
             rep = repColor(img);
      }
      
        
      // write that representative pixel to current pixel
      result1.setColor(i,j,rep);
      k++;
    }
  }
  
  
  
  result1.update();
}

ofColor ofApp::repColor(ofImage &image) {
  ofColor clr;
  
  float r;
  float g;
  float b;

  vector <float> rs;
  vector <float> gs;
  vector <float> bs;
  for (int i = 0; i<image.getWidth();i++) {
      for (int j = 0; j<image.getHeight();j++) {
        ofColor c = image.getColor(i, j);
        
        r += c.r;
        g += c.g;
        b += c.b;
        
        // non blacks/greys/whites
        if (c.getSaturation() > -1) {
        // non whites
//        if (c.getBrightness() < 250) {
            rs.push_back(c.r);
            gs.push_back(c.g);
            bs.push_back(c.b);
        }
        
      }
  }
  

  sort(rs.begin(), rs.end());
  sort(gs.begin(), gs.end());
  sort(bs.begin(), bs.end());
  float px = image.getWidth()*image.getHeight();
  r /= px;
  g /= px;
  b /= px;
  clr = ofColor(r,g,b);
//  clr = ofColor(mode(rs),mode(gs),mode(bs));
  return clr;
}


void ofApp::processImages(bool isHSB, vector <ofImage> &images, int w, int h, ofImage &result1, ofImage &result2, ofImage &result3, ofImage &result4, bool processFour) {
  result1.allocate(w,h,OF_IMAGE_COLOR);
  if (processFour) {
    result2.allocate(w,h,OF_IMAGE_COLOR);
    result3.allocate(w,h,OF_IMAGE_COLOR);
    result4.allocate(w,h,OF_IMAGE_COLOR);
  }
  
    
  for(int i = 0; i < int(images.back().getWidth()); i++) {
      for(int j = 0; j < int(images.back().getHeight()); j++) {
        float sumR = 0;
        float sumG = 0;
        float sumB = 0;
        float maxR = 0;
        float maxG = 0;
        float maxB = 0;
        float minR = 255;
        float minG = 255;
        float minB = 255;
        vector <float> rs;
        vector <float> gs;
        vector <float> bs;
        for (int k=0;k<images.size();k++) {
          ofColor color = images[k].getColor(i, j);
          float r = color.r;
          float g = color.g;
          float b = color.b;
          if (isHSB) {
              r = color.getHue();
              g = color.getSaturation();
              b = color.getBrightness();
          }
          
          sumR += r;
          sumG += g;
          sumB += b;
          maxR = fmax(maxR, r);
          maxG = fmax(maxG, g);
          maxB = fmax(maxB, b);
          minR = fmin(minR, r);
          minG = fmin(minG, g);
          minB = fmin(minB, b);
          rs.push_back(r);
          gs.push_back(g);
          bs.push_back(b);
        }
        sumR /= float(images.size());
        sumB /= float(images.size());
        sumG /= float(images.size());
        
        
        // hsb
        ofColor hsb = ofColor(0);
        if (isHSB) {
          hsb.setHsb(sumR,sumG,sumB);
          result1.setColor(i,j,hsb);
          
          if (processFour) {
            hsb.setHsb(maxR,maxG,maxB);
            result2.setColor(i,j,hsb);
            hsb.setHsb(minR,minG,minB);
            result3.setColor(i,j,hsb);
          }
        } else {
        result1.setColor(i,j,ofColor(sumR,sumG,sumB));

          if (processFour) {
          result2.setColor(i,j,ofColor(maxR,maxG,maxB));
          result3.setColor(i,j,ofColor(minR,minG,minB));
          }
        }
        
        if (processFour) {
          sort(rs.begin(), rs.end());
          sort(gs.begin(), gs.end());
          sort(bs.begin(), bs.end());
  //      median
  //        int mid = int(floor(rs.size()/2));
  // result4.setColor(i,j,ofColor(rs[mid],gs[mid],bs[mid]));
         
          if (isHSB) {
            hsb.setHsb(mode(rs), mode(gs), mode(bs));
            result4.setColor(i,j,hsb);
          } else {
         result4.setColor(i,j,ofColor(mode(rs),mode(gs),mode(bs)));
          }
        }
      }
  }
  result1.update();
  if (processFour) {
    result2.update();
    result3.update();
    result4.update();
  }
}

int ofApp::mode(vector <float> &array) {
  int number = array[0];
  int mode = number;
  int count = 1;
  int countMode = 1;

  for (int i=1; i<array.size(); i++)
  {
        if (array[i] == number)
        { // count occurrences of the current number
           ++count;
        }
        else
        { // now this is a different number
              if (count > countMode)
              {
                    countMode = count; // mode is the biggest ocurrences
                    mode = number;
              }
             count = 1; // reset count for the new number
             number = array[i];
    }
  }
  return mode;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  int w = ww;
  int h = hh;
  
  bool four_to_one = true;
  
  if (four_to_one) {
    ofPushMatrix();
  
  
      ofPixels px = result2_2.getPixels();
        px.resize(w*2*1.066666667,h*2*1.116,OF_INTERPOLATE_NEAREST_NEIGHBOR);
//       px.resize(result2_2.getWidth()*2,result2_2.getHeight()*2,OF_INTERPOLATE_NEAREST_NEIGHBOR);
        result2_2.setFromPixels(px);
        result2_2.update();
        result2_2.draw((w*2)-32,-30);
    ofPopMatrix();
    
//    glBegin(GL_QUADS);
//    glColor4f(0.,0.,0.,0.);
//    glVertex2f(w*2., 0.);
//    glColor4f(0.,0.,0.,0.);
//    glVertex2f(w*4., 0.);
//    glColor4f(0.,0.,0.,1.);
//    glVertex2f(w*4., h*2.);
//    glColor4f(0.,0.,0.,1.);
//    glVertex2f(w*2., h*2.);
//    glEnd();
    
    if(bgon) { ofBackgroundGradient(ofColor(ofColor(0),0),ofColor(ofColor(0),255),OF_GRADIENT_LINEAR);
    }
    
    
//    result2_1.draw((w*2)+24,103);
        result2_1.draw((w*2)+(w-(w*scale)),(h-(h*scale)));
  } else {
    ofPushMatrix();
    ofTranslate(w*2,0);
    result2_1.draw(0,0);
    result2_2.draw(w,0);
    result2_3.draw(0,h);
    result2_4.draw(w,h);
    ofPopMatrix();
  }
  
  result1_1.draw(0,0);
  result1_2.draw(w,0);
  result1_3.draw(0,h);
  result1_4.draw(w,h);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'b') {
    bgon = !bgon;
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
