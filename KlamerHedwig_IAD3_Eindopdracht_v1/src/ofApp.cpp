#include "ofApp.h"
//Aangeven welke pinnen worden gebruikt.
#define PIN_BUTTONA 11
#define PIN_BUTTONQ 10
#define PIN_BUTTONT 9

void ofApp::setup() {
	// over de database: eerste en tweede kolommen is de X en Y as in pixels van mijn eigen scherm.
	//Derde kolom is de naam van de boom die op dat coordinaat staat. Hier inporteer ik de database.
	db = new SQLite::Database("data/boomTest.db");

	// laden van interface
	mapImage.load("KaartBomen_design.png");
	point.load("point.png");

	//  ladnen van boom portfolio's
	Aesculus.load("Aesculus.png");
	Alnus.load("Alnus.png");
	Quercus.load("Quercus.png");

	//Arduino inalatizeren
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM4");
	arduino.sendFirmwareVersionRequest();
	bSetupArduino = false; // bool om Arduino aan te zetten wanneer hij klaar is
	ofSetLogLevel(OF_LOG_NOTICE);

	//Zorgen dat bij de start van het programma alle bomen zichtbaar op het scherm zijn.
	string statement = "SELECT X_as, Y_as,BoomGeslacht FROM databaseBomen_XY";
	SQLite::Statement query(*db, statement);
	while (query.executeStep()) {
		boomX = query.getColumn(0).getInt();
		boomY = query.getColumn(1).getInt();
		boomGeslacht = query.getColumn(2).getText();
		//ofLog() << selectedN << " " << boomX << endl;

		Xlijst.push_back(boomX); //De X en Y positie van bomen in een lijst zetten
		Ylijst.push_back(boomY);

	}
	query.reset();
}

void ofApp::update() {
	arduino.update();
	//ofLog() << boomN << endl;
	if (boomN != selectedN) { //kijken of de speler op een andere knop drukt
		Xlijst.clear(); //lijst van X en Y positie leeg maken zodat er nieuwe waardes in kunnen komen van de spedifieke boomsoort.
		Ylijst.clear();
		
		selectedN = boomN; //De geselecteerde boom naam laten overeen komen met waar de gebruiker 
		// een statement waar de X en Y positie uit de database worden gehaald die overeen komen met de geselecteerde naam
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
	mapImage.draw(0, 0); //Teken van kaart
	ofLog() << boomN << endl;

	//Het teken van de cirkels op de locatie van de bomen
	for (int i=0; i < Xlijst.size(); i++) {
		point.draw(Xlijst[i]-15, Ylijst[i]-15);
	}

	//Het tekenen van het juiste boom portfolio bij de geselecteerde boom naam
	if (boomN == "Alnus") {
		Alnus.draw(-25, 100);
	}
	if (boomN == "Quercus") {
		Quercus.draw(0, 100);
		
	}
	if (boomN == "Aesculus") {
		Aesculus.draw(-25, 100);
		
	}
	
}

void ofApp::keyPressed(int key) {
	//functie maken zodat ik per boom soort de punten daarvan op het scherm aan en uit kan zetten. 
	// Dit is een test voor wanneer mijn arduino niet aan mijn computer zit.
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

	// boolean om te zorgen dat arduino veilig wordt opgestart
	bSetupArduino = true;
	// Vertellen welke pin van Arduino wat doet
	arduino.sendDigitalPinMode(PIN_BUTTONT, ARD_INPUT);
	arduino.sendDigitalPinMode(PIN_BUTTONQ, ARD_INPUT);
	arduino.sendDigitalPinMode(PIN_BUTTONA, ARD_INPUT);


	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);

}

void ofApp::digitalPinChanged(const int& pin) {
	int value = arduino.getDigital(pin);
	ofLogVerbose() << "Digital pin" << pin << " changed to " << value << endl;
	//De fysiele knoppen checken of ze worden ingedrukt en daaraan de geslecteerde boom naam te veranderen
	if (pin == PIN_BUTTONA) {
		boomN = "Aesculus";
	}
	if (pin == PIN_BUTTONQ) {
		boomN = "Quercus";
	}
	if (pin == PIN_BUTTONT) {
		boomN = "Alnus";
	}

}