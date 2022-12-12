#include "ofApp.h"
#include "ofxDeSynthUI.h"

DeUI::UI* UI = nullptr;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(1024, 768);
	ofSetFrameRate(60);

	UI = new DeUI::UI();
	UI->setup();
	UI->load_json();

}

//--------------------------------------------------------------
void ofApp::exit() {
	UI->save_json();
}

//--------------------------------------------------------------
void ofApp::update(){
	UI->update();
	UI->LED1 = UI->PAD1;
	UI->LED2 = UI->PAD2;
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
	UI->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	UI->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	UI->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	UI->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	UI->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	UI->mouseReleased(x, y, button);
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
