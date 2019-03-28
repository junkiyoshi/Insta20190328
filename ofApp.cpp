#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5 + 80);
	ofRotate(270);

	int len = 75;
	for (int radius = 160; radius <= 400; radius += 80) {

		vector<glm::vec2> outer;
		vector<glm::vec2> inner;
		int start = ofRandom(360) + ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.003), 0, 1, 0, 360);
		for (int deg = start; deg <= start + 360; deg++) {

			outer.push_back(this->make_point(radius, deg));
			inner.push_back(this->make_point(radius - len, deg));

			if (ofRandom(100) < 10) {

				if (outer.size() > 25) {

					this->draw_piece(outer, inner);
				}
			}
		}

		if (outer.size() > 0) {

			this->draw_piece(outer, inner);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_piece(vector<glm::vec2>& outer, vector<glm::vec2>& inner) {

	ofColor random_color;
	random_color.setHsb(ofRandom(255), 200, 255);

	reverse(inner.begin(), inner.end());

	ofFill();
	ofSetColor(39);

	ofBeginShape();
	ofVertices(outer);
	ofVertices(inner);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(239);

	ofBeginShape();
	ofVertices(outer);
	ofVertices(inner);
	ofEndShape(true);

	outer.clear();
	inner.clear();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int radius, int deg) {

	deg = deg % 360;

	int deg_a = (deg / 120) * 120;
	int deg_b = deg_a + 120;

	int remainder = deg % 120;
	int diff = deg - deg_a;

	auto point_a = glm::vec2(radius * cos(deg_a * DEG_TO_RAD), radius * sin(deg_a * DEG_TO_RAD));
	auto point_b = glm::vec2(radius * cos(deg_b * DEG_TO_RAD), radius * sin(deg_b * DEG_TO_RAD));
	auto distance = point_b - point_a;

	return point_a + (distance / 120) * diff;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}