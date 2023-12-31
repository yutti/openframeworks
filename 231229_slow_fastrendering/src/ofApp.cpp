#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackgroundHex(0x57554c);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	ofEnableAlphaBlending();
	image_heart0.load("image/heart_yellow.png");
	image_heart1.load("image/heart_baiored.png");
	image_heart2.load("image/heart_blue.png");
	image_heart3.load("image/heart_blue2.png");
	image_heart4.load("image/heart_green.png");
	image_heart5.load("image/heart_green2.png");
	image_heart6.load("image/heart_pink.png");
	image_heart7.load("image/heart_red.png");
	ofDisableAlphaBlending();
	// slow       = 1
	// faster     = 2
	// super fast = 3
	mode = 1;

}

//--------------------------------------------------------------
void ofApp::update() {
	// add points all the time
	if (points.size() < 400) {
		for (int i = 0; i < 30; i++) {
			addPoint(ofGetWidth() / 2, ofGetHeight() / 2);
		}
	}

	// move all the points around
	for (unsigned int i = 0; i < points.size(); i++) {

		speeds[i].y += 0.04; // some grav
		points[i] += speeds[i];
		speeds[i] *= 0.98;

		// move from the mouse
		glm::vec2 mouseVec = glm::vec2(ofGetMouseX(), ofGetMouseY()) - points[i];
		if (glm::length(mouseVec) < 100) {
			mouseVec = glm::normalize(mouseVec);
			speeds[i] -= mouseVec;
		}

		// wrap the screen
		if (points[i].x > ofGetWidth())    points[i].x = 1;
		if (points[i].x < 0)               points[i].x = ofGetWidth() - 1;
		if (points[i].y > ofGetHeight())   points[i].y = 1;
		if (points[i].y < 0)               points[i].y = ofGetHeight() - 1;
	}
	img = ofRandom(0, 63);
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	pos.z = 0;
	obj_scale = 0;
}

//--------------------------------------------------------------
void ofApp::draw() {

	// draw the points the slow way
	if (mode == 1) {
#ifdef TARGET_OPENGLES
		ofSetColor(255);
		ofDrawBitmapString("OpenGL immediate mode not available in OpenGL ES. Press 2 or 3.", ofGetWidth() / 2.0f - 300, ofGetHeight() / 2.0f);
#else 
		ofSetColor(255);
		for (unsigned int i = 0; i < points.size(); i++) {
			if (i % 8 == 0) { image_heart0.draw(points[i].x, points[i].y, 15.0, 15.0); }
			if (i % 8 == 1) { image_heart1.draw(points[i].x, points[i].y, 15.0, 15.0); }
			if (i % 8 == 2) { image_heart2.draw(points[i].x, points[i].y, 15.0, 15.0); }
			if (i % 8 == 3) { image_heart3.draw(points[i].x, points[i].y, 15.0, 15.0); }
			if (i % 8 == 4) { image_heart4.draw(points[i].x, points[i].y, 15.0, 15.0); }
			if (i % 8 == 5) { image_heart5.draw(points[i].x, points[i].y, 15.0, 15.0); }
			if (i % 8 == 6) { image_heart6.draw(points[i].x, points[i].y, 15.0, 15.0); }
			if (i % 8 == 7) { image_heart7.draw(points[i].x, points[i].y, 15.0, 15.0); }
		}
#endif
	}

	// a bit faster
	else if (mode == 2) {
		obj_scale = 2;
		ofBackground(0); 
		ofSetColor(255, 0, 0);
		for (unsigned int j = 0; j <30; j++) {
		ofBeginShape();  // Record the shape start
			for (int i = 0; i < 360; i++) {
				float rad = ofDegToRad(i);  
				// Heart Equation
				float x = 16 * pow(sin(rad), 3);
				float y = -(13 * cos(rad) - 5 * cos(2 * rad) - 2 * cos(3 * rad) - cos(4 * rad));
				x *= obj_scale;
				y *= obj_scale;
				x += points[j].x;// x position
				y += points[j].y;// y position
				ofVertex(x, y);
			}
		ofEndShape();  // Record the shape finished
		}
	}

	// super fast (vbo)
	else if (mode == 3) {
		peral_number = 4;
		pi = 3.141592;
		obj_scale = 10;
		alpha = 2 * pi / peral_number;
		tmin = -pi / 2;
		tmax = 3 * pi / 2;
		dt = (tmax - tmin) / 1000;
		radius = 0;
		ofBackground(0);
		ofSetColor(255, 0, 0);  
		for (unsigned int i = 0; i < 30; i++) {
			ofBeginShape();
			for (int j = 1;j <= peral_number;j++) //number of petals
			{
				for (t = tmin;t <= tmax + dt;t = t + dt)
				{
					if (t > (3 * pi / 2 - dt) && t < (3 * pi / 2 + dt))
					{
						r = 0;
						z = -pi / 2;
					}
					else
					{
						if (t > (-pi / 2 - dt) && t < (-pi / 2 + dt))
						{
							r = 0.;
							z = pi / 2;
						}
						else
						{
							r = obj_scale * sqrt((5 - 3 * sin(t)) * (1 + sin(t)));
							z = asin(obj_scale * (1 - sin(t)) * cos(t) / r);
						}
					}
					f = -alpha * z / pi + pi / 2 + 2 * pi * (j - 1) / peral_number;
					xx = (r + radius) * cos(f) + points[i].x;
					yy = (r + radius) * sin(f) + points[i].y;
					ofVertex(xx, yy);
				}
			}
			ofEndShape();
		}
	}

	ofSetColor(0);
	ofDrawRectangle(0, 0, 250, 90);
	ofSetColor(255);
	ofDrawBitmapString("Mode " + ofToString(mode), 20, 20);
	ofDrawBitmapString("FPS " + ofToString(ofGetFrameRate(), 0), 20, 40);
	ofDrawBitmapString("Total Points " + ofToString((int)points.size()), 20, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == '1') mode = 1;
	if (key == '2') mode = 2;
	if (key == '3') mode = 3;


	// clear all the points
	if (key == 'c') {
		points.clear();
		speeds.clear();
	}

	// add crazy amount
	if (key == 'z') {
		for (int i = 0; i < 400; i++) {
			addPoint(ofRandomWidth(), ofRandomHeight());
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	// add a bunch as you drag
	if (points.size() > 600) {
		points.erase(points.begin(), points.begin() + 200);
		speeds.erase(speeds.begin(), speeds.begin() + 200);
	}
	for (int i = 0; i < 200; i++) {
		addPoint(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
