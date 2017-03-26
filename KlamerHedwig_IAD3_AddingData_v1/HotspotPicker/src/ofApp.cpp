#include "ofApp.h"

void ofApp::setup() {
	string databasePath = ofToDataPath("hotspots.sqlite", true);
	db = new SQLite::Database(databasePath, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
	if (!db->tableExists("hotspots")) {
		db->exec("CREATE TABLE hotspots (id INTEGER PRIMARY KEY, x INTEGER, y INTEGER, width INTEGER, height INTEGER)");
	}

	mapImage.load("KaartBomen_BeeldVerhouding.png");
	//mapImage.load("KaartBomen_Design.png");
}

void ofApp::update() {
	if (requery) {
		hotspots.clear();
		requery = false;

		SQLite::Statement query(*db, "SELECT * FROM hotspots");
		while (query.executeStep()) {
			int rowid = query.getColumn("id");
			int x = query.getColumn("x");
			int y = query.getColumn("y");
			int width = query.getColumn("width");
			int height = query.getColumn("height");

			hotspots[rowid] = ofRectangle(x, y, width/2, height/2);
		}
	}
}

void ofApp::draw() {
	ofSetColor(ofColor::white);
	mapImage.draw(0, 0);

	ofSetColor(ofColor::black);
	ofDrawBitmapString("MouseX:" + ofToString(mouseX), 700, 20);
	ofDrawBitmapString("MouseY:" + ofToString(mouseY), 700, 40);

	auto it = hotspots.begin();
	while (it != hotspots.end()) {
		if (drawHotspots) {
			ofFill();
			ofSetColor(ofColor::red, 30);
			ofDrawRectangle(it->second);

			ofNoFill();
			ofSetColor(ofColor::red);
			ofDrawRectangle(it->second);

			ofSetColor(ofColor::white);
		}

		if (it->second.inside(mouseX, mouseY)) {
			ofDrawBitmapString("Hotspot " + ofToString(it->first), 700, 100);
		}
		it++;
	}
}

void ofApp::keyPressed(int key) {
	
	if (key == '1') {
		drawHotspots = !drawHotspots;
	}
	else if (key == '2') {
		auto it = hotspots.begin();
		while (it != hotspots.end()) {
			if (it->second.inside(mouseX, mouseY)) {

				stringstream statement;
				statement << "DELETE FROM hotspots WHERE id=" << it->first;
				db->exec(statement.str());
				requery = true;
			}
			it++;
		}
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_LEFT) {
		stringstream statement;
		statement << "INSERT INTO hotspots (x,y,width,height) VALUES (" << x << "," << y << ",50,50)";
		db->exec(statement.str());
		requery = true;
	}
}

void ofApp::mouseMoved(int x, int y) {
}