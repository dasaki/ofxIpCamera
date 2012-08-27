#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxIpCamera.h"

//#define AXIS
//#define DLINK
#define VIVOTEK

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

        ofxIpCamera	cam;

        ofxCvColorImage		colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;


        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
};

#endif
