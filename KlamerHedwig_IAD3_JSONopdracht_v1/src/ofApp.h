#pragma once

#include "DrawDandelion.h"

#include "ofxJSON.h"
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		

		vector<DrawDandelion> ddandelion;

		ofxJSONElement json;
		bool parsingSuccessful;
		int wind;
	
};
