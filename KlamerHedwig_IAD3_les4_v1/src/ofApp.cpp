#include <SQLiteCpp/include/SQLiteCpp/Database.h>
#include "ofApp.h"

void ofApp::setup() {
    string databasePath = ofToDataPath("bevolking.sqlite", true);
    db = new SQLite::Database(databasePath);
	myFont.load("Amazing Infographic@ Free.otf", 36);
	
	northP.load("images/northPeople.png");
	eastP.load("images/eastPeople.png");
	southP.load("images/southPeople.png");
	westP.load("images/westPeople.png");
	xPeople = 35;
	yPeople = 20;
}

void ofApp::update() {
    int year = ofMap(ofGetMouseX(), 0, ofGetWidth() - 100, 1900, 2016, true);

    if (year != selectedYear) {
        selectedYear = year;
        string sql = "SELECT year, north, east, south, west, north+east+south+west AS total FROM bevolking WHERE year=?";

        SQLite::Statement query(*db, sql);

        query.bind(1, selectedYear); // vervang 1e vraagteken door de waarde van de variabele
        if (query.executeStep()) {
            total = query.getColumn("total").getInt();
            year = query.getColumn("year").getInt();
            north = (query.getColumn("north").getInt())*100/total;
            east = (query.getColumn("east").getInt()) * 100/total;
            south = (query.getColumn("south").getInt()) * 100/total;
            west = (query.getColumn("west").getInt()) * 100/total;
            ofLog() << selectedYear << " " << total << "  north-> "
                    << north << " " << east << " " << south << " " << west
                    << endl;
        }
	    query.reset();
    }
}

void ofApp::draw() {
	ofSetBackgroundColor(93, 93, 93);
	ofSetCircleResolution(100);

	for (int i = 0; i <= north; i++) {
		northP.draw(i * xPeople + xPeople/2, 50);
	}
	for (int i = 0; i <= east; i++) {
		eastP.draw(i * xPeople + xPeople / 2, 170);
	}
	for (int i = 0; i <= south; i++) {
		southP.draw(i * xPeople + xPeople / 2, 290);
	}
	for (int i = 0; i <= west; i++) {
		westP.draw(i * xPeople + xPeople / 2, 410);
	}
	ofSetColor(255, 253, 255);
	myFont.drawString(ofToString(selectedYear), 20, 530);
	myFont.drawString(ofToString("north"), 20, 50);
	myFont.drawString(ofToString("east"), 20, 160);
	myFont.drawString(ofToString("south"), 20, 280);
	myFont.drawString(ofToString("west"), 20, 400);
}

void ofApp::keyPressed(int key) {

}

void ofApp::keyReleased(int key) {

}

void ofApp::mouseMoved(int x, int y) {

}