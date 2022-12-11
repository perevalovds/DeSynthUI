#include "ofApp.h"
#include "ofxDeSynthUI.h"

DeUI::UI* UI = nullptr;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(1024, 768);
	ofSetFrameRate(60);

	UI = new DeUI::UI();
	UI->setup();

}

//--------------------------------------------------------------
void ofApp::update(){
	UI->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	float W = ofGetWidth();
	float H = ofGetHeight();
	UI->draw(W, H);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	UI->onEvent({ DeUI::EventType::keyPressed, glm::vec2(0,0), 0, key });
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	UI->onEvent({ DeUI::EventType::keyReleased, glm::vec2(0,0), 0, key });
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	UI->onEvent({ DeUI::EventType::mouseMoved, glm::vec2(x, y), 0, 0 });
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	UI->onEvent({ DeUI::EventType::mouseDragged, glm::vec2(x, y), button, 0 });
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	UI->onEvent({ DeUI::EventType::mousePressed, glm::vec2(x, y), button, 0 });
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	UI->onEvent({ DeUI::EventType::mouseReleased, glm::vec2(x, y), button, 0 });
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
