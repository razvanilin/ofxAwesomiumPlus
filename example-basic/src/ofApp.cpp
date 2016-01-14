#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    _browser.setup(ofGetWidth(), ofGetHeight(), "ofxAwesomiumPlus");
    _browser.loadURL("http://www.google.com");

}

//--------------------------------------------------------------
void ofApp::update(){
    _browser.update();

    ofSetWindowTitle(_browser.getTitle());
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    _browser.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    _browser.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    _browser.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    _browser.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    _browser.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    _browser.mousePressed(x, x, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    _browser.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(float x, float y) {
    _browser.mouseScrolled(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    _browser.windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
