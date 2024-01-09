#pragma once
#include "ofMain.h"

class Star {
public:
	ofVec2f shootpos;
	ofVec2f shootvel;
	ofVec2f shootfrc;

	Star(ofVec2f startPos) {
		shootpos = startPos;
		shootvel = ofVec2f(ofRandom(1,4), ofRandom(0, 2));
	}

	void update() {
		shootfrc.x = std::abs(ofSignedNoise(ofRandom(-10000, 10000), shootpos.x * 0.6, ofGetElapsedTimef() * 0.2) * 0.09 + 0.1);
		shootfrc.y = std::abs(ofSignedNoise(shootpos.x * 0.006, shootpos.y * 0.003, ofGetElapsedTimef() * 0.1)) * 0.01;

		shootvel += shootfrc * 10;
		shootpos += shootvel;
	}

	void draw() {
		ofSetColor(255, 255, 0);
		ofDrawCircle(shootpos.x, shootpos.y, 2);
	}

	bool isOffScreen() {
		return shootpos.x < 0 || shootpos.y < 0 || shootpos.x > ofGetWidth() || shootpos.y > ofGetHeight();
	}
};

