#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"




// uncomment this to read from two kinects simultaneously
#define USE_TWO_KINECTS


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void drawPointCloud();
    void drawAnotherPointCloud();

    
    ofCamera cam;
    ofVec3f camPos;
    
    //create a kinect object
    ofxKinect kinect;
    
#ifdef USE_TWO_KINECTS
	ofxKinect kinect2;
#endif
    
    
    
    ofxCvColorImage colorImg;

    ofxCvGrayscaleImage grayImage;//grayscale depth image
    ofxCvGrayscaleImage grayThreshNear;//the near thresholded image
    ofxCvGrayscaleImage grayThreshFar;//the far thresholded image
    ofxCvContourFinder contourFinder;
    
    
    bool bThresWithOpenCv;
    bool bDrawPointCloud;
    
    int nearThreshold;
    int farThreshold;
    
    int angle;
    
    
		
};
