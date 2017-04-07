#include "ofApp.h"


void ofApp::setup(){
	// Getting the weatherinfo from the internet
	std::string url = "http://api.openweathermap.org/data/2.5/weather?q=hilversum,nl&appid=37f584c9d170b496e7abe382b2237a5a&units=metric";

	// printing the info we got from the link if we succeed
	bool parsingSuccessful = json.open(url);
	if (parsingSuccessful) {
		ofLogNotice("weatherCheck::setup") << json.getRawString(true);
		//ofLogNotice("weatherCheck::setup") << "Succes to parse JSON.";

	}
	else {
		ofLogNotice("weatherCheck::setup") << "Failed to parse JSON.";
	}
}


void ofApp::update() {
	ofLog() << wind << endl;
	for (unsigned int i = 0; i < ddandelion.size(); i++) {
		ddandelion[i].update();
		//if (ddandelion[i].x > ofGetWindowWidth()) {
		//	ddandelion._Pop_back_n(8);
		//}
	}
	
}


void ofApp::draw(){
	ofBackground(130, 130, 130);

	wind = json["wind"]["speed"].asInt();
	//ofToInt(wind);

	for (unsigned int i = 0; i < ddandelion.size(); i++) {
		ddandelion[i].draw();
	}
	
	
}

void ofApp::keyPressed(int key) {
	
	if (key= ' '){
		for (int i = 0; i <= ofRandom(8, 12); i++) {
			DrawDandelion newDrawDandelion;
			newDrawDandelion.setup(wind);
			ddandelion.push_back(newDrawDandelion);
		}
	}
}
