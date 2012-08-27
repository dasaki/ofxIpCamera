#include "testApp.h"

#ifdef VIVOTEK
    #define IMAGE_W 720
    #define IMAGE_H 576
#endif
#ifdef AXIS
    #define IMAGE_W 640
    #define IMAGE_H 480
#endif
#ifdef DLINK
    #define IMAGE_W  640 // 1280
    #define IMAGE_H 360 //720 //
#endif

//--------------------------------------------------------------
void testApp::setup(){

    cam.init(IMAGE_W, IMAGE_H);
    //cam.setUri("http://visitor:pointedubluff@nbbc.dyndns-web.com:80/image/jpeg.cgi");
    //cam.setCredentials("user", "dlink");
  //  ofSetLogLevel( OF_LOG_VERBOSE);
   // cam.setUri("http://dlink:dlink@203.125.227.73:80/video2.mjpg");// D-Link DCS-2130
//  cam.setUri("http://mu.webcam.oregonstate.edu/axis-cgi/mjpg/video.cgi");

//  //  cam.setUri("http://203.125.227.73:80/image/jpeg.cgi");// D-Link DCS-2130
  //  cam.setCredentials("dlink", "dlink");
  // rtsp://root:m1011wpass@10.42.43.10:554/axis-media/media.amp?videocodec=mpeg4


// // cam.setUri("http://admin@192.168.1.20:80/video/mjpg.cgi?profileid=2");// D-Link DCS-2130
  //  cam.setCredentials("admin", "");

 //   cam.setUri("http://192.168.1.30:80/video2.mjpg");// D-Link DCS-2230


  // FUNCIONANDO
 //   cam.setUri("http://admin@192.168.1.20:80/image/jpeg.cgi");// D-Link DCS-2230
 //   cam.setCredentials("admin", "");

#ifdef AXIS
  // AXIS m1011w
    cam.setUri("http://192.168.1.40:80/axis-cgi/mjpg/video.cgi");
  //  cam.setUri("http://192.168.1.40/axis-cgi/jpg/image.cgi");
    cam.setCredentials("axis", "12345");
#endif
#ifdef DLINK
  //  cam.setUri("http://192.168.1.20:80/image/jpeg.cgi");// una sola imagen estática
    cam.setUri("http://192.168.1.20:80/video/mjpg.cgi?profileid=1");// stream video
    cam.setCredentials("admin", "");
#endif
#ifdef VIVOTEK
    cam.setUri("http://192.168.1.30:80/video2.mjpg");
    cam.setCredentials("", "");
#endif
    cam.setVerbose(true);
    cam.open();
    cam.resetAnchor();

    colorImg.allocate(IMAGE_W, IMAGE_H);
	grayImage.allocate(IMAGE_W, IMAGE_H);
	grayBg.allocate(IMAGE_W, IMAGE_H);
	grayDiff.allocate(IMAGE_W, IMAGE_H);

	bLearnBakground = true;
	threshold = 80;

	//ofSetFrameRate(30);

}

//--------------------------------------------------------------
void testApp::update()
{
	ofBackground(100,100,100);
	cam.update();

    //colorImg.setFromPixels(cam.getPixels(), IMAGE_W, IMAGE_H);
   /* grayImage = colorImg;
    if (bLearnBakground == true){
        grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
        bLearnBakground = false;
    }

    // take the abs value of the difference between background and incoming and then threshold:
    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(threshold);

    // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    // also, find holes is set to true so we will get interior contours as well....
    contourFinder.findContours(grayDiff, 10, (IMAGE_W*IMAGE_H)/2, 20, false);	// find holes
*/}

//--------------------------------------------------------------
void testApp::draw(){


    int ypos = 0;
    // draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
	ofPushMatrix();
	cam.draw(20,ypos);
	ofPopMatrix();
	//grayImage.draw(IMAGE_H,20, 320, 240);
	//grayBg.draw(20,280, 320, 240);
	/*grayDiff.draw(660, 20, 320, 240);

	// then draw the contours:

	//ofFill();
	//ofSetHexColor(0x333333);
	//ofRect(IMAGE_H,540,320,240);
	ofSetHexColor(0xffffff);

	// we could draw the whole contour finder
	contourFinder.draw(20, 20);//IMAGE_H,540);
*/
	// or, instead we can draw each blob individually,
	// this is how to get access to them:
    /*
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(IMAGE_H,540);
    }*/

	// finally, a report:

   // ypos += 100;
	ofSetHexColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i, fps: %f", threshold, contourFinder.nBlobs, ofGetFrameRate());
	ofDrawBitmapString(reportStr, IMAGE_W+40, ypos);
}

//--------------------------------------------------------------
void testApp::exit(){

	cam.close();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;

        case 'o':
        	cam.open();
            break;

        case 'c':
        	cam.close();
            break;

        case 'g':
        	cam.grabFrame();
            break;
	}
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

