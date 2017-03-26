#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"


class ofApp : public ofBaseApp {

public:
	void setup();

	void update();

	void draw();

	void keyPressed(int key);

	void mouseMoved(int x, int y);

	void mousePressed(int x, int y, int button) override;

private:
	SQLite::Database* db;

	ofImage mapImage;
	map<int, ofRectangle> hotspots;

	bool drawHotspots = true;
	bool requery = true;
};
