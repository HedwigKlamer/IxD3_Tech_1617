#include "ofApp.h"

void ofApp::setup(){
	db = new SQLite::Database("data/databaseBomen.sql"); 

	mapImage.load("KaartBomen_design.png");

	SQLite::Statement query(*db, "SELECT*FROM databaseBomen WHERE BoomGeslacht=?");
	if (string BoomGeslacht = "Acer") {
		query.bind(1, BoomGeslacht);
		if (query.executeStep()) {
			ofLog() << query.getColumn("BoomGeslacht") << " " << query.getColumn("X-as") << endl;
		}
		query.reset();
	}
	
}

void ofApp::update(){
	boomN = query.getColumn(2).getDouble();
}

void ofApp::draw(){
	mapImage.draw(0, 0);
}

void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}