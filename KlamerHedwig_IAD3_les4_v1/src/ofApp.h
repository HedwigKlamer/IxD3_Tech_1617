#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"

class ofApp : public ofBaseApp {

    public:
        void setup();

        void update();

        void draw();

        void keyPressed(int key);

        void keyReleased(int key);

        void mouseMoved(int x, int y);

    private:
        SQLite::Database* db;
		ofImage northP;
		ofImage eastP;
		ofImage southP;
		ofImage westP;
        int selectedYear = 1900;

        int total;
        int north;
        int east;
        int south;
        int west;

		int xPeople;
		int yPeople;

		ofTrueTypeFont myFont;


};
