#pragma once

#include "ofMain.h"
class DrawDandelion
{
public:
	void setup(int myWind);

	void update();

	void draw();

	// variables
	float x;
	float y;
	float speedY;
	float speedX;


	ofImage dandelion;
};

