#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

private:
	SQLite::Database* db;
	ofImage mapImage;
	ofImage point;
	ofImage esdoorn;

	ofArduino arduino;
	void setupArduino(const int& version);
	void digitalPinChanged(const int& pin);
	bool bSetupArduino;

	int boomX;
	int boomY;

	string boomGeslacht;
	string selectedN;
	string boomN;

	vector<int> Xlijst;
	vector<int> Ylijst;
	vector<string> NaamB;
		
};
