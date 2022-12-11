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
	UI->onEvent({ DeUI::EventType::keyPressed, key });
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	UI->onEvent({ DeUI::EventType::keyReleased, key });
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	UI->onEvent({ DeUI::EventType::mouseMoved, x, y});
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	UI->onEvent({ DeUI::EventType::mouseDragged, x, y, button });
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	UI->onEvent({ DeUI::EventType::mousePressed, x, y, button });
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	UI->onEvent({ DeUI::EventType::mouseReleased, x, y, button });
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
