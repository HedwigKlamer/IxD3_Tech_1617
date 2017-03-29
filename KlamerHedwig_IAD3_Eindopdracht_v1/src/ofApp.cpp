#include "ofApp.h"
#define PIN_BUTTONA 11
#define PIN_BUTTONQ 10
#define PIN_BUTTONT 9

void ofApp::setup() {
	// over de database: eerste en tweede kolommen is de X en Y as in pixels van mijn eigen scherm.
	//Derde kolom is de naam van de boom die op dat coordinaat staat. Hier inporteer ik de database.
	db = new SQLite::Database("data/boomTest.db");

	mapImage.load("KaartBomen_design.png");
	point.load("point.png");
	esdoorn.load("testText.png");

	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM4");
	arduino.sendFirmwareVersionRequest();
	bSetupArduino = false; // flag so we setup arduino when its ready
	ofSetLogLevel(OF_LOG_NOTICE);


	string statement = "SELECT X_as, Y_as,BoomGeslacht FROM databaseBomen_XY";
	SQLite::Statement query(*db, statement);
	while (query.executeStep()) {
		boomX = query.getColumn(0).getInt();
		boomY = query.getColumn(1).getInt();
		boomGeslacht = query.getColumn(2).getText();
		//ofLog() << selectedN << " " << boomX << endl;

		Xlijst.push_back(boomX);
		Ylijst.push_back(boomY);

	}
	query.reset();
}

void ofApp::update() {
	arduino.update();
	//ofLog() << boomN << endl;
	if (boomN != selectedN) {
		Xlijst.clear();
		Ylijst.clear();
		
		selectedN = boomN;
		// een statement met een gewone, en twee *berekende* kolommen
		string statement = "SELECT X_as, Y_as, BoomGeslacht FROM databaseBomen_XY WHERE BoomGeslacht = ?";

		SQLite::Statement query(*db, statement);
		query.bind(1, selectedN);

		while (query.executeStep()) {
			boomX = query.getColumn(0).getInt();
			boomY = query.getColumn(1).getInt();
			boomGeslacht = query.getColumn(2).getText();
			//ofLog() << selectedN << endl;

			Xlijst.push_back(boomX);
			Ylijst.push_back(boomY);

		}
		query.reset();
	}

}

void ofApp::draw() {
	mapImage.draw(0, 0);

	for (int i=0; i < Xlijst.size(); i++) {
	
		point.draw(Xlijst[i]-15, Ylijst[i]-15);
	}
	if (boomN == "Acer") {
		esdoorn.draw(0, 100);
	}
}

void ofApp::keyPressed(int key) {
	//functie maken zodat ik per boom soort de punten daarvan op het scherm aan en uit kan zetten.
	if (key == 'a') {
		boomN = "Aesculus"; //paardenkastanje
	} 
	if(key == 's') {
		boomN = "Quercus"; //Eik
	}
	if (key == 'd') {
		boomN = "Alnus"; //Els
	}
}

void ofApp::setupArduino(const int& version) {
	ofLogNotice() << "Arduino initialized" << endl;
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// it is now safe to send commands to the Arduino
	bSetupArduino = true;
	// say what kind of output/input each pin has
	arduino.sendDigitalPinMode(PIN_BUTTONT, ARD_INPUT);
	arduino.sendDigitalPinMode(PIN_BUTTONQ, ARD_INPUT);
	arduino.sendDigitalPinMode(PIN_BUTTONA, ARD_INPUT);


	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);

}

void ofApp::digitalPinChanged(const int& pin) {
	int value = arduino.getDigital(pin);
	ofLogVerbose() << "Digital pin" << pin << " changed to " << value << endl;
	if (pin == PIN_BUTTONA && value == 1) {
		boomN = "Acer";
	}
	if (pin == PIN_BUTTONQ) {
		boomN = "Quercus";
	}
	if (pin == PIN_BUTTONT) {
		boomN = "Taxodium";
	}

}