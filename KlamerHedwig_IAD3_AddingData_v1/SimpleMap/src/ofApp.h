#pragma once

#include "ofMain.h"

#define HOTSPOT_COUNT 4

class ofApp : public ofBaseApp {

    public:
        void setup();

        void update();

        void draw();

        void keyPressed(int key);

        void mouseMoved(int x, int y);

    private:
        ofImage mapImage;
        ofRectangle hotSpots[HOTSPOT_COUNT];
        bool drawHotspots;
};
