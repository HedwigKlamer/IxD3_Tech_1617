#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

private:
	SQLite::Database* db;
	ofImage mapImage;

	int boomX;
	int boomY;

	string boomN;
		
};
