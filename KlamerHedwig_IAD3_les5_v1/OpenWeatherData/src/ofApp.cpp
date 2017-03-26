#include "ofApp.h"

void ofApp::setup() {

}


void ofApp::update() {

}

void ofApp::draw() {

}

void ofApp::keyPressed(int key) {
    getData();
}


void ofApp::getData() {
	std::string url = "http://api.openweathermap.org/data/2.5/weather?q=hilversum,nl&appid=37f584c9d170b496e7abe382b2237a5a&units=metric";

    bool success = json.open(url);
    if (success) {
		ofLogNotice("ofApp::getData") << json.getRawString(true);
		int elementCount = json["cnt"].asInt();
        ofLog() << json["cnt"].asInt() << " elementen gekregen" << endl;

        for (int i = 0; i < elementCount; i++) {
            ofLog() << "Datum van element #" << i << " : " << json["list"][i]["dt_txt"] << endl;
        }

    } else {
        ofLog() << "Oops. No data!" << endl;
    }
}