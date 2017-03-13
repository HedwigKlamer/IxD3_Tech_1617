#include <SQLiteCpp/include/SQLiteCpp/Database.h>
#include "ofApp.h"

void ofApp::setup() {
    string databasePath = ofToDataPath("bevolking.sqlite", true);
    db = new SQLite::Database(databasePath);
	
	northP.load("images/northPeople.png");
	eastP.load("images/eastPeople.png");
	southP.load("images/southPeople.png");
	westP.load("images/westPeople.png");

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
            ofLog() << selectedYear << " " << total << " "
                    << north << " " << east << " " << south << " " << west
                    << endl;
        }

        query.reset();
    }
	


}

void ofApp::draw() {
	ofSetBackgroundColor(93, 93, 93);
	ofSetCircleResolution(100);

	northP.draw(20, 20);
	eastP.draw(20, 100);
	southP.draw(20, 180);
	westP.draw(20, 260);
    //ofDrawCircle(ofGetWidth() / 2 * 0.5, ofGetHeight() / 2 * 0.5, west * 1.0f / total * 200);
    //ofDrawCircle(ofGetWidth() / 2 * 1.5, ofGetHeight() / 2 * 0.5, east * 1.0f / total * 200);
    //ofDrawCircle(ofGetWidth() / 2 * 0.5, ofGetHeight() / 2 * 1.5, north * 1.0f / total * 200);
    //ofDrawCircle(ofGetWidth() / 2 * 1.5, ofGetHeight() / 2 * 1.5, south * 1.0f / total * 200);
}

void ofApp::keyPressed(int key) {

}

void ofApp::keyReleased(int key) {

}

void ofApp::mouseMoved(int x, int y) {

}