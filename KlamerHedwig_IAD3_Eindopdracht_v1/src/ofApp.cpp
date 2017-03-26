#include "ofApp.h"

void ofApp::setup(){
	db = new SQLite::Database("data/databaseBomen_XY.csv"); 

	mapImage.load("KaartBomen_design.png");
	
	/*SQLite::Statement query(*db, "SELECT*FROM databaseBomen WHERE BoomGeslacht=?");
	for (string BoomGeslacht = "Acer") {
		query.bind(1, BoomGeslacht);
		if (query.executeStep()) {
			ofLog() << query.getColumn("BoomGeslacht") << " " << query.getColumn("X-as") << endl;
		}
		query.reset();
	}
	*/
}

void ofApp::update(){
	boomN = "Acer";
	selectedN = "Acer";

	if (boomN != selectedN) {
		selectedN = boomN;
		// een statement met een gewone, en twee *berekende* kolommen
		string statement = "X-as, Y-as FROM databaseBomen_XY WHERE BoomGeslacht = ?";


		SQLite::Statement query(*db, statement);
		query.bind(1, selectedN);

		if (query.executeStep()) {
			int boomX = query.getColumn(0).getDouble();
			int boomY = query.getColumn(1).getDouble();
			ofLog() << selectedN << " " << boomX << endl;
		}
		query.reset();
	}

}

void ofApp::draw(){
	//mapImage.draw(0, 0);

	ofNoFill();
	ofSetColor(ofColor::red);
	ofDrawRectangle(10,10,boomX, boomY);


	ofSetColor(ofColor::white);
	
}

void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}