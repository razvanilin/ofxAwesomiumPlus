#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	browser.setup(800, 600);
	browser.loadURL("http://www.google.com");

}

//--------------------------------------------------------------
void testApp::update(){
	ofxAwesomium::updateCore();
	browser.update();

	ofSetWindowTitle(browser.getTitle());
}

//--------------------------------------------------------------
void testApp::draw(){
	if(browser.getIsLoading()) {
		ofSetColor(0);
		ofDrawBitmapString("Loading...", 10, 15);
	}
	ofSetColor(255);
	browser.draw(10, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	browser.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	browser.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	browser.mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	browser.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	browser.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	browser.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	browser.windowResized(w, h);
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
