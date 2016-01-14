#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // 'ofxAwesomiumPlus' string passed below is important for binding javascript methods
    // check index.html to see how it's used
    _browser.setup(ofGetWidth(), ofGetHeight(), "ofxAwesomiumPlus");
    _browser.loadURL("file:///" + ofFilePath::getAbsolutePath("index.html"));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    _browser.update();
    
    // get the state from the browser
    // the state is set from the 'onclick' event on the buttons in index.html
    if (_browser.getState().length() > 0)
        _state = _browser.getState();
    
    if(_state == "OPEN_CAMERA") {
        if (!_vidGrabber.isInitialized()) {
            _vidGrabber.setup(640, 360);
        }
        _vidGrabber.update();
    }
    
    if(_state == "DRAW_STRING") {
        _vidGrabber.close();
    }
    
    ofSetWindowTitle(_browser.getTitle());
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    _browser.draw(0, 0);
    
    if (_state == "OPEN_CAMERA") {
        ofSetColor(255);
        _vidGrabber.draw(200, 200, 640, 360);
    }
    
    if (_state == "DRAW_STRING") {
        ofSetColor(ofColor::red);
        ofDrawBitmapString("OpenFrameworks", 100, 200);
    }
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
