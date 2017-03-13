#pragma once
#include "SQLiteCpp.h"
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		SQLite::Database* db;
		int selectedYear;
		float radius;
		float youngR;
		float middleR;
		float oldR;
		float dyingR;


		int groupX;
		int groupY;
		ofTrueTypeFont myFont;
};
