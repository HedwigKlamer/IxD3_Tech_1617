#include "ofApp.h"

void ofApp::setup(){
	// over de database: eerste en tweede kolommen is de X en Y as in pixels van mijn eigen scherm.
	//Derde kolom is de naam van de boom die op dat coordinaat staat. Hier inporteer ik de database.
	db = new SQLite::Database("data/databaseBomen_XY.csv"); 

	mapImage.load("KaartBomen_design.png");
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
	
	mapImage.draw(0, 0);

	//teken een rood vierkant op de coordinaten van de bomen
	ofNoFill();
	ofSetColor(ofColor::red);
	ofDrawRectangle(10,10,boomX, boomY);


	ofSetColor(ofColor::white);
	
}

void ofApp::keyPressed(int key){
	//functie maken zodat ik per boom soort de punten daarvan op het scherm aan en uit kan zetten.
}

void ofApp::keyReleased(int key){

}