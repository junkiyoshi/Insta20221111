#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetCircleResolution(60);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int len = 600;
	int radius = len * 0.35;

	ofSetColor(32);
	ofNoFill();
	ofDrawCircle(glm::vec2(), radius);
	ofDrawRectangle(glm::vec2(), len, len);

	ofSetColor(255);
	ofFill();

	for (float param = 0; param <= 100; param++) {

		auto noise_value = ofNoise(glm::vec3(this->make_point(len, param) * 0.005, ofGetFrameNum() * 0.015));
		if (noise_value < 0.5) {

			auto location_1 = this->make_point(len, param);
			auto location_2 = this->make_point(len, param + 1);

			ofDrawLine(location_1, location_2);
			ofDrawRectangle(location_1, 6, 6);
			ofDrawRectangle(location_2, 6, 6);
		}
		else if (noise_value > 0.6) {

			auto location_1 = glm::normalize(this->make_point(len, param)) * radius;
			auto location_2 = glm::normalize(this->make_point(len, param + 1)) * radius;

			ofDrawLine(location_1, location_2);
			ofDrawCircle(location_1, 4);
			ofDrawCircle(location_2, 4);
		}
		else {

			auto location_1 = glm::normalize(this->make_point(len, param)) * radius + (this->make_point(len, param) - glm::normalize(this->make_point(len, param)) * radius) * ofMap(noise_value, 0.5, 0.6, 1, 0);
			auto location_2 = glm::normalize(this->make_point(len, param + 1)) * radius + (this->make_point(len, param + 1) - glm::normalize(this->make_point(len, param + 1)) * radius) * ofMap(noise_value, 0.5, 0.6, 1, 0);

			ofDrawLine(location_1, location_2);
			ofDrawCircle(location_1, 4);
			ofDrawRectangle(location_2, 6, 6);
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}