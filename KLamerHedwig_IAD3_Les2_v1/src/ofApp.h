#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h""

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

private:
	SQLite::Database* db;
	int selectedYear;
	float pctSingle;
	float pctMultiple;
		
};
