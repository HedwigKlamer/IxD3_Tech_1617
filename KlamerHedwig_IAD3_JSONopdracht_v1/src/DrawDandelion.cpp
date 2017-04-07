#include "DrawDandelion.h"



void DrawDandelion::setup(int myWind) {
	x = 0;        // give some random position
	y = ofRandom(0, (ofGetHeight()));

	speedX = myWind;           // and random speed and direction
	speedY = myWind/4;

	dandelion.load("Dandelion1.png");
}

void DrawDandelion::update() {
	//if (x < 0) {
	//	x += speedX;
	//}
	if (x >= 0) {
		x += speedX;
		y += speedY;
	}

}

void DrawDandelion::draw() {
	//for (int i = 0; i <= ofRandom(8, 12); i++) {
		dandelion.draw(x, y);
	//}
}
