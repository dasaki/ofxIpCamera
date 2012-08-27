/*==============================================================================

	ofxIpCamera.h

	ofxIpCamera: an ip camera grabber addon

	Copyright (C) 2010, 2011  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#ifndef _OFX_IP_CAMERA
#define _OFX_IP_CAMERA

#include "ofConstants.h"
#include "ofTexture.h"
#include "ofGraphics.h"
#include "ofTypes.h"

#include "ofThread.h"

#include "Poco/URI.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/HTTPClientSession.h"

/*
	example camera uri: http://192.168.5.85/operator/basic.shtml

	References:
    http://pocoproject.org/docs/
    http://freeimage.sourceforge.net/fip/index.html
    http://www.cplusplus.com/reference/iostream/istream/get/
    http://www.openframeworks.cc/forum/viewtopic.php?f=8&t=3545

	OF forum post:
	http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=4087&hilit=ip+camera+axis
*/

class ofxIpCamera : public ofBaseVideo, protected ofThread {

	public :

		ofxIpCamera();
		virtual ~ofxIpCamera();

		/// is the current frame new after a call to update()?
        /// only valid when the thread is running
		bool isFrameNew();

        /// open the connection and start grabbing images
        void open();

        /// close the connection and stop grabbing images
		void close();

        /// initialize resources, must be called before open()
		bool init(int w, int h, bool bTexture=true);

        /// clear resources
        void clear();

        /// get the raw pixels of the most recent frame
		unsigned char 	* getPixels();

        /// get the pixel reference
        ofPixels& getPixelsRef();

        ofTexture &		getTextureReference();

        void 			setVerbose(bool bTalkToMe);

        /**
        	\brief	set the camera host address
            \param	host	the address or ip of the camera

            builds the uri automatically using the given width and height,
            call after init

			example uri:

            http://192.168.5.85/demo/demo.shtml?type=jpg&size=320x180&videoFormat=mjpeg&color=0&clock=0

            the uri is of type:

            http://host/axis-cgi/jpg/image.cgi?resolution=320x180
        */
        void setHost(string host);

        /**
        	\brief	set the camera uri including query manually
            \param	uri	the camera uri

            overrides the prebuilt uri set by setHost

			example uri:

			http://192.168.5.85/axis-cgi/jpg/image.cgi?resolution=320x180
        */
		void setUri(string uri);

        /**
        	\brief	set the access credentials to the camera (if any)
            \param	user	username
            \param	password	password

            sets HTTP Authorization: Basic username:password
            from http://en.wikipedia.org/wiki/Basic_access_authentication

            see also
            http://www.motobit.com/util/base64-decoder-encoder.asp
        */
        void setCredentials(string user, string password);

        bool sendRequest(string theRequest);
        bool sendRequest(string theRequest, string &theResponse);


		void 			setUseTexture(bool bUse);
		void 			draw(float x, float y, float w, float h);
		void 			draw(float x, float y);

        /**
        	\brief	updates the texture from the pixels

            call this function when using the the texture, otherwise the
            texture will not be updated from the grabbed pixels

            use isFrameNew to check is a new frame was grabbed after the update
        */
        void update();

        /**
        	\brief	grab a frame manually
            \return	true if frame grabbed successfully

        	non-threaded, do not use while thread is running
        */
        bool grabFrame();


		//the anchor is the point the image is drawn around.
		//this can be useful if you want to rotate an image around a particular point.
        void			setAnchorPercent(float xPct, float yPct);	//set the anchor as a percentage of the image width/height ( 0.0-1.0 range )
        void			setAnchorPoint(int x, int y);				//set the anchor point in pixels
        void			resetAnchor();								//resets the anchor to (0, 0)


		float 			getHeight();
		float 			getWidth();

		int			height;
		int			width;

	   Poco::Net::HTTPClientSession client;

	protected:

		Poco::URI 						uri;			// full path uri
    	Poco::Net::HTTPBasicCredentials credentials;	// encodes user name and pass


        istream*                responseBody;
        string                  contentType;

		bool					bUseTexture;
		ofTexture 				tex;				// the user tex
		bool 					bVerbose;
		bool 					bGrabberInited;
	    ofPixels                pixels;
        bool                    bIsFrameNew;
        bool                    bIsBufferEmpty;



    private:

        // setup a session object with host, etc
        void setupSession(Poco::Net::HTTPClientSession& client);

        // grab one frame using the given session object
        bool grabOneFrame(Poco::Net::HTTPClientSession& client);
        bool getJpgFromBuffer(int bufferSize);
        // thread function
        void threadedFunction();

        bool                    bNeedsUpdate;   // update the pixels?
        ofPixels                pixelsTemp;     // threaded copy
        int                     timeLapse;
        int                     lastMillis;
};

#endif
