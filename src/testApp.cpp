#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
      camPos.set(ofVec3f(ofGetWidth()/2,2900,1400));
    
    
    //ofToggleFullscreen();
   
    kinect.setRegistration();//enable depth -> video image calibration
    kinect.init();
    kinect.open();
    
    if(kinect.isConnected()){
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
#ifdef USE_TWO_KINECTS
    kinect2.init();
    kinect2.open();
#endif
    
//  colorImg.allocate(kinect.width, kinect.height);
//  grayImage.allocate(kinect.width, kinect.height);
//	grayThreshNear.allocate(kinect.width, kinect.height);
//	grayThreshFar.allocate(kinect.width, kinect.height);

//    nearThreshold = 230;
//	farThreshold = 70;
//	bThresWithOpenCv = true;
//	
//	ofSetFrameRate(60);
	
	// zero the tilt on startup
	angle = 0;
    //kinect device head angle
	kinect.setCameraTiltAngle(angle);
	
	// start from the front
	bDrawPointCloud = true;
   
    

}

//--------------------------------------------------------------
void testApp::update(){
    ofBackground(0, 0, 0);
    kinect.update();

    
//    if(kinect.isFrameNew()){
    
       //load grayscale depth image from the kinect source
    
//       grayImage.setFromPixels(kinect.getDepthPixels(),kinect.width,kinect.height);
//        if(bThresWithOpenCv){
//            grayThreshNear = grayImage;
//            grayThreshFar = grayImage;
//            grayThreshNear.threshold(nearThreshold,true);
//            grayThreshFar.threshold(farThreshold);
//            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(),NULL);
//        }
//        
//        
//    }
      //update the cv image
    
//grayImage.flagImageChanged();
    
    
    
    // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    // also, find holes is set to true so we will get interior contours as well....
    
//    contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);

}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    
    ofSetColor(255, 255, 255);
    
    
    if(bDrawPointCloud){
      
        cam.begin();
        ofNoFill();
        ofDrawBox(0, ofGetHeight()/2, -800, 2400,2400,4800 );
        drawPointCloud();
#ifdef USE_TWO_KINECTS
       // ofLog()<<"START DRAW 2ND POINT CLOUD";
        drawAnotherPointCloud();
#endif
        //camPos.set(ofVec3f(0,900,1600));
      
        //cam.resetTransform();
        cam.setPosition(camPos);
        cam.lookAt(ofVec3f(0,-300,0));
       
//        ofLogNotice()<< "near clip is: "<<cam.getNearClip();
//        ofLogNotice()<< "far clip is "<<cam.getFarClip();
        cam.end();
    }
//    else{
//        kinect.drawDepth(10, 10, 400, 300);
//        kinect.draw(420,10,400,300);
//        grayImage.draw(10,320,400,300);
//        contourFinder.draw(10,320,400,300);
//    }
    
    
    

}
//------------------------------------------------------------

void testApp::drawPointCloud() {
	int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	int step = 2;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinect.getDistanceAt(x, y) > 0 && kinect.getDistanceAt(x,y) < 1200) {
				//mesh.addColor(kinect.getColorAt(x,y));
				mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
                
			}
		}
	}
	glPointSize(3);
    
	ofPushMatrix();
	// the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	ofEnableDepthTest();
    ofSetColor(200, 200, 200);
	mesh.drawVertices();
	ofDisableDepthTest();
	ofPopMatrix();
}
#ifdef USE_TWO_KINECTS
void testApp::drawAnotherPointCloud() {
	int w = 640;
	int h = 480;
	ofMesh mesh2;
	mesh2.setMode(OF_PRIMITIVE_POINTS);
	int step = 2;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinect2.getDistanceAt(x, y) > 0 && kinect2.getDistanceAt(x,y) < 800) {
				//mesh.addColor(kinect.getColorAt(x,y));
				mesh2.addVertex(kinect2.getWorldCoordinateAt(x, y));
                
			}
		}
	}
	glPointSize(3);
    
	ofPushMatrix();
	// the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	ofEnableDepthTest();
    ofSetColor(255, 100, 00);
	mesh2.drawVertices();
	ofDisableDepthTest();
	ofPopMatrix();
}
#endif


void testApp::exit(){
   // kinect.setCameraTiltAngle(0);
    kinect.close();
    
#ifdef USE_TWO_KINECTS
    //kinect2.setCameraTiltAngle(0);
	kinect2.close();
#endif
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30)angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30)angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
#ifdef USE_TWO_KINECTS

        case OF_KEY_LEFT:
            angle--;
            if(angle<-30)angle=-30;
            kinect2.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_RIGHT:
            angle++;
            if(angle>30)angle=30;
            kinect2.setCameraTiltAngle(angle);
            break;
            
            
#endif
        
     
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
