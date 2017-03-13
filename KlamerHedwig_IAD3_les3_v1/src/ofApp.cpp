#include "ofApp.h"

void ofApp::setup() {
	db = new SQLite::Database("data/bevolking.sqlite");
	groupX = 50;
	groupY = 670;
	myFont.load("Amazing Infographic@ Free.otf", 16);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	int year = ofMap(ofGetMouseX(), 0, ofGetWidth() - 100, 1900, 2016, true);
	ofLog() << selectedYear << " " << radius << endl;
	
	if (year != selectedYear) {
		selectedYear = year;
		// een statement met een gewone, en twee *berekende* kolommen
		string statement = "SELECT age_0to20/50, age_20to45/50, age_45to65/50, age_65to80/50 FROM bevolking WHERE year = ?";

	
		SQLite::Statement query(*db, statement);
		query.bind(1, selectedYear);
	
		if (query.executeStep()) {
			youngR = query.getColumn(0).getDouble();
			middleR = query.getColumn(1).getDouble();
			oldR = query.getColumn(2).getDouble();
			dyingR = query.getColumn(3).getDouble();
			ofLog() << selectedYear << " " << radius << endl;
		}
		query.reset();	
		//if (groupX != ofGetWindowWidth()) {
		//	groupX = groupX + 1;
		//}
		groupX = ofGetMouseX();
	}

	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//radius = 20;
	ofSetBackgroundColor(0, 0, 0);
	ofSetCircleResolution(100);
	
	ofFill();
	
	ofSetColor(255, 153, 51);
	ofDrawCircle(groupX, groupY, youngR);
	ofDrawCircle(groupX, groupY-200, middleR);
	ofDrawCircle(groupX, groupY-400, oldR);
	ofDrawCircle(groupX, groupY-600, dyingR);

	ofSetColor(255, 253, 255);
	myFont.drawString("0 to 20", groupX - youngR / 2, groupY);
	myFont.drawString("20 to 45", groupX - middleR / 2, groupY-200);
	myFont.drawString("45 to 60", groupX - oldR / 2, groupY-400);
	myFont.drawString("60 to 80", groupX - dyingR / 2, groupY-600);
	myFont.drawString (ofToString(selectedYear), 50, 50);

}


