#include "ofApp.h"
#include "ofxDeSynthUI.h"

DeUI::UI* UI = nullptr;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(200, 100);
	ofSetFrameRate(60);

	UI = new DeUI::UI();

}

//--------------------------------------------------------------
void ofApp::update(){
	UI->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	UI->draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
