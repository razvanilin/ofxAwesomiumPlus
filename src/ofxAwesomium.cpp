//
//  ofxAwesomium.cpp
//  basic
//
//  Created by jeff-cr on 11/6/13.
//
//

#include "ofxAwesomium.h"

// ----------------------------------------------------------------
ofxAwesomium::~ofxAwesomium(){
	web_view->Destroy();
}

// ----------------------------------------------------------------
void ofxAwesomium::setup(int width, int height) {
	if(!bCoreInited) {
		initCore(ofToDataPath("Logs"), ofToDataPath("SessionData"));
	}
	web_view = core->CreateWebView(width, height, session);
	frame.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    //texture.allocate(width, height, GL_RGBA);
}

// ----------------------------------------------------------------
void ofxAwesomium::loadURL(string url) {
	web_view->LoadURL(WebURL(WSLit(url.c_str())));
    web_view->Focus();
	
}

// ----------------------------------------------------------------
JSValue ofxAwesomium::doJavaScript(string js) {
	return web_view->ExecuteJavascriptWithResult(WSLit(js.c_str()), WSLit(""));
}

// ----------------------------------------------------------------
bool ofxAwesomium::update() {
    surface = (BitmapSurface*)web_view->surface();
    
    if(surface && surface->buffer() && surface->is_dirty()) {
		surface->CopyTo(frame.getPixels(), frame.getWidth()*4, 4, true, false);
		frame.update();
		return true;
    }
	return false;
}

// ----------------------------------------------------------------
void ofxAwesomium::draw(float x, float y) const {
	frame.draw(x, y);
}

// ----------------------------------------------------------------
void ofxAwesomium::draw(float x, float y, float w, float h) const {
	frame.draw(x, y, w, h);
}

// ----------------------------------------------------------------
float ofxAwesomium::getHeight() const {
	return frame.getHeight();
}

// ----------------------------------------------------------------
float ofxAwesomium::getWidth() const {
	return frame.getWidth();
}

// ----------------------------------------------------------------
string ofxAwesomium::getTitle(){
	char buf[1024];
    web_view->title().ToUTF8( buf, 1024 );
	return string(buf);
}

// ----------------------------------------------------------------
bool ofxAwesomium::getIsLoading(){
	return web_view->IsLoading();
}

// ----------------------------------------------------------------
void ofxAwesomium::keyPressed(int key) {
	web_view->Focus();

	// get the correct virtual key codes
	int vk = key;
	switch (key)
	{
	case OF_KEY_LEFT:
		vk = VK_LEFT;
		break;
	case OF_KEY_RIGHT:
		vk = VK_RIGHT;
		break;
	case OF_KEY_UP:
		vk = VK_UP;
		break;
	case OF_KEY_DOWN:
		vk = VK_DOWN;
		break;
	case OF_KEY_DEL:
		vk = VK_DELETE;
		break;
	// this is the 'dot' key. For some reason I had to hard-code this in order to make it work
	case 46:
		vk = VK_DECIMAL;
		break;
	default:
		break;
	}

    Awesomium::WebKeyboardEvent keyDown;
    keyDown.type = Awesomium::WebKeyboardEvent::kTypeKeyDown;
    keyDown.virtual_key_code = (char)vk;
    keyDown.native_key_code = (char)key;
    keyDown.text[0] = (char)key;
    keyDown.unmodified_text[0] = (char)key;
    keyDown.modifiers = (char)OF_KEY_MODIFIER;
	
    web_view->InjectKeyboardEvent( keyDown );
    
	Awesomium::WebKeyboardEvent typeChar;
	typeChar.type = Awesomium::WebKeyboardEvent::kTypeChar;
	typeChar.virtual_key_code = (char)vk;
	typeChar.native_key_code = (char)key;
	typeChar.text[0] = (char)key;
	typeChar.unmodified_text[0] = (char)key;
	typeChar.modifiers = (char)OF_KEY_MODIFIER;
	web_view->InjectKeyboardEvent(typeChar);

}

// ----------------------------------------------------------------
void ofxAwesomium::keyReleased(int key) {
	web_view->Focus();

	int vk = key;
	
	// get the correct virtual key codes
	switch (key)
	{
	case OF_KEY_LEFT:
		vk = VK_LEFT;
		break;
	case OF_KEY_RIGHT:
		vk = VK_RIGHT;
		break;
	case OF_KEY_UP:
		vk = VK_UP;
		break;
	case OF_KEY_DOWN:
		vk = VK_DOWN;
		break;
	case OF_KEY_DEL:
		vk = VK_DELETE;
		break;
	// this is the 'dot' key. For some reason I had to hard-code this in order to make it work
	case 46:
		vk = VK_DECIMAL;
		break;
	default:
		break;
	}

    Awesomium::WebKeyboardEvent evt;
    evt.type = Awesomium::WebKeyboardEvent::kTypeKeyUp;

    evt.virtual_key_code = (char)vk;
    evt.native_key_code = (char)key;
    evt.text[0] = (char)key;
    evt.unmodified_text[0] = (char)key;
    evt.modifiers = (char)OF_KEY_MODIFIER;
    web_view->InjectKeyboardEvent( evt );
}

//--------------------------------------------------------------
void ofxAwesomium::mouseMoved(int x, int y ){
    web_view->InjectMouseMove( x, y );
}

//--------------------------------------------------------------
void ofxAwesomium::mouseDragged(int x, int y, int button){
    web_view->InjectMouseMove( x, y );
}

//--------------------------------------------------------------
void ofxAwesomium::mousePressed(int x, int y, int button){
    if( button ==  OF_MOUSE_BUTTON_1)
        web_view->InjectMouseDown( Awesomium::kMouseButton_Left );
    else if( button == OF_MOUSE_BUTTON_2 )
        web_view->InjectMouseDown( Awesomium::kMouseButton_Middle );
    else if( button== OF_MOUSE_BUTTON_3 )
        web_view->InjectMouseDown( Awesomium::kMouseButton_Right );
}

//--------------------------------------------------------------
void ofxAwesomium::mouseReleased(int x, int y, int button){
    if( button ==  OF_MOUSE_BUTTON_1)
        web_view->InjectMouseUp( Awesomium::kMouseButton_Left );
    else if( button == OF_MOUSE_BUTTON_2 )
        web_view->InjectMouseUp( Awesomium::kMouseButton_Middle );
    else if( button== OF_MOUSE_BUTTON_3 )
        web_view->InjectMouseUp( Awesomium::kMouseButton_Right );
}

//--------------------------------------------------------------
void ofxAwesomium::windowResized(int w, int h) {
	frame.resize(w, h);
	web_view->Resize(w, h);
}


// ----------------------------------------------------------------
//  _       __     __    ______
// | |     / /__  / /_  / ____/___  ________
// | | /| / / _ \/ __ \/ /   / __ \/ ___/ _ \
// | |/ |/ /  __/ /_/ / /___/ /_/ / /  /  __/
// |__/|__/\___/_.___/\____/\____/_/   \___/
// ----------------------------------------------------------------

bool ofxAwesomium::bCoreInited;
WebCore* ofxAwesomium::core;
WebSession* ofxAwesomium::session;

// ----------------------------------------------------------------
void ofxAwesomium::initCore(string logsPath, string sessionPath) {
	WebConfig config;
    config.log_path = WSLit(logsPath.c_str());
    config.log_level = kLogLevel_Verbose; //kLogLevel_Normal;
    
    core = WebCore::Initialize(config);
    
    WebPreferences prefs;
    prefs.enable_plugins = true;
    prefs.enable_smooth_scrolling = true;
    
    session = core->CreateWebSession(WSLit(sessionPath.c_str()), prefs);
	
	bCoreInited = true;
}

// ----------------------------------------------------------------
void ofxAwesomium::updateCore() {
	core->Update();
}

// ----------------------------------------------------------------
void ofxAwesomium::shutdownCore() {
	WebCore::Shutdown();
}

