#include "ofxAwesomiumPlus.h"

// ----------------------------------------------------------------
ofxAwesomiumPlus::~ofxAwesomiumPlus() {
    web_view->Destroy();
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::setup(int width, int height, string appName, bool debug) {
    
    if (!bCoreInited) {
        initCore(ofToDataPath("Logs"), ofToDataPath("SessionData"), debug);
    }
    
    web_view = core->CreateWebView(width, height, session, WebViewType::kWebViewType_Offscreen);
    
    _appName = appName;
    
    if (debug) {    // Enable forwarding web console messages to IDE console
        MyViewListender* my_view_listener = new MyViewListender();
        web_view->set_view_listener(my_view_listener);
    }
    
    _scrollModifier = 3;
    
    // Bind the events
    BindState();
    
    frame.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    //texture.allocate(width, height, GL_RGBA);

	// the browser is resizable by default
	_resizable = true;
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::loadURL(string url) {
    web_view->LoadURL(WebURL(WSLit(url.c_str())));
    web_view->Focus();
}

// ----------------------------------------------------------------
JSValue ofxAwesomiumPlus::doJavaScript(string js) {
    return web_view->ExecuteJavascriptWithResult(WSLit(js.c_str()), WSLit(""));
}

// ----------------------------------------------------------------
bool ofxAwesomiumPlus::update() {
    updateCore();
    surface = (BitmapSurface*)web_view->surface();
    
    if (frame.getPixels().size() > 0 && surface && surface->buffer() && surface->is_dirty()) {
        surface->CopyTo(frame.getPixels(), frame.getWidth() * 4, 4, true, false);
        frame.update();
        return true;
    }
    return false;
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::draw(float x, float y) const {
    frame.draw(x, y);
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::draw(float x, float y, float w, float h) const {
    frame.draw(x, y, w, h);
}

// ----------------------------------------------------------------
float ofxAwesomiumPlus::getHeight() const {
    return frame.getHeight();
}

// ----------------------------------------------------------------
float ofxAwesomiumPlus::getWidth() const {
    return frame.getWidth();
}

// ----------------------------------------------------------------
string ofxAwesomiumPlus::getTitle() {
    char buf[1024];
    web_view->title().ToUTF8(buf, 1024);
    return string(buf);
}

// ----------------------------------------------------------------
bool ofxAwesomiumPlus::getIsLoading() {
    return web_view->IsLoading();
}

// ----------------------------------------------------------------
ofImage ofxAwesomiumPlus::getFrame() {
	return frame;
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::keyPressed(int key) {
    web_view->Focus();
    int text = key;
    // get the correct virtual key codes
    int vk = key;
    switch (key)
    {
        case OF_KEY_LEFT:
            vk = KeyCodes::AK_LEFT;
            break;
        case OF_KEY_RIGHT:
            vk = KeyCodes::AK_RIGHT;
            break;
        case OF_KEY_UP:
            vk = KeyCodes::AK_UP;
            break;
        case OF_KEY_DOWN:
            vk = KeyCodes::AK_DOWN;
            break;
        case OF_KEY_DEL:
            vk = KeyCodes::AK_DELETE;
            break;
        case OF_KEY_BACKSPACE:
            vk = KeyCodes::AK_BACK;
            break;
            // this is the 'dot' key. For some reason I had to hard-code this in order to make it work
        case 46:
            vk = KeyCodes::AK_DECIMAL;
            break;
        case -1:
            return;
        case OF_KEY_TAB:
            // don't insert anything when TAB is pressed
            return;
        default:
            break;
    }
    
    Awesomium::WebKeyboardEvent keyDown;
    keyDown.type = Awesomium::WebKeyboardEvent::kTypeKeyDown;
    keyDown.virtual_key_code = (char)vk;
    keyDown.native_key_code = (char)key;
    keyDown.text[0] = (char)text;
    keyDown.unmodified_text[0] = (char)text;
    keyDown.modifiers = (char)OF_KEY_MODIFIER;
    
    web_view->InjectKeyboardEvent(keyDown);
    
    Awesomium::WebKeyboardEvent typeChar;
    typeChar.type = Awesomium::WebKeyboardEvent::kTypeChar;
    typeChar.virtual_key_code = (char)vk;
    typeChar.native_key_code = (char)key;
    typeChar.text[0] = (char)text;
    typeChar.unmodified_text[0] = (char)text;
    typeChar.modifiers = (char)OF_KEY_MODIFIER;
    web_view->InjectKeyboardEvent(typeChar);
    
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::keyReleased(int key) {
    web_view->Focus();
    
    int vk = key;
    int text = key;
    // get the correct virtual key codes
    switch (key)
    {
        case OF_KEY_LEFT:
            vk = KeyCodes::AK_LEFT;
            break;
        case OF_KEY_RIGHT:
            vk = KeyCodes::AK_RIGHT;
            break;
        case OF_KEY_UP:
            vk = KeyCodes::AK_UP;
            break;
        case OF_KEY_DOWN:
            vk = KeyCodes::AK_DOWN;
            break;
        case OF_KEY_DEL:
            vk = KeyCodes::AK_DELETE;
            //return;
            break;
        case OF_KEY_BACKSPACE:
            vk = KeyCodes::AK_BACK;
            break;
            // this is the 'dot' key. For some reason I had to hard-code this in order to make it work
        case 46:
            vk = KeyCodes::AK_DECIMAL;
            break;
        case -1:
            return;
        case OF_KEY_TAB:
            // don't insert anything when TAB is pressed
            return;
        default:
            break;
    }
    
    Awesomium::WebKeyboardEvent evt;
    evt.type = Awesomium::WebKeyboardEvent::kTypeKeyUp;
    
    evt.virtual_key_code = (char)vk;
    evt.native_key_code = (char)key;
    evt.text[0] = (char)text;
    evt.unmodified_text[0] = (char)text;
    evt.modifiers = (char)OF_KEY_MODIFIER;
    web_view->InjectKeyboardEvent(evt);
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::mouseMoved(int x, int y) {
    web_view->InjectMouseMove(x, y);
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::mouseDragged(int x, int y, int button) {
    web_view->InjectMouseMove(x, y);
    
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::mousePressed(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_1)
        web_view->InjectMouseDown(Awesomium::kMouseButton_Left);
    else if (button == OF_MOUSE_BUTTON_2)
        web_view->InjectMouseDown(Awesomium::kMouseButton_Middle);
    else if (button == OF_MOUSE_BUTTON_3)
        web_view->InjectMouseDown(Awesomium::kMouseButton_Right);
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::mouseReleased(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_1)
        web_view->InjectMouseUp(Awesomium::kMouseButton_Left);
    else if (button == OF_MOUSE_BUTTON_2)
        web_view->InjectMouseUp(Awesomium::kMouseButton_Middle);
    else if (button == OF_MOUSE_BUTTON_3)
        web_view->InjectMouseUp(Awesomium::kMouseButton_Right);
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::mouseScrolled(float x, float y) {
    web_view->InjectMouseWheel(y*_scrollModifier, x*_scrollModifier);
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::windowResized(int w, int h) {
	if (_resizable) {
		frame.resize(w, h);
		web_view->Resize(frame.getWidth(), frame.getHeight());
	}
    
    // Might crash on windows - substract a few pixels from width and height to fix it (just in case)
}

//--------------------------------------------------------------
string ofxAwesomiumPlus::getState() {
    return _state;
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::setScrollSpeed(int modifier) {
    _scrollModifier = modifier;
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::setTransparent(bool flag) {
    web_view->SetTransparent(true);
}

//--------------------------------------------------------------
void ofxAwesomiumPlus::setAutomaticResize(bool flag) {
	_resizable = flag;
}

//--------------------------------------------------------------
bool ofxAwesomiumPlus::isAutomaticResize() {
	return _resizable;
}

//--------------------------------------------------------------
//
//	AWESOMIUM JS METHOD HANDLER METHODS
//
//--------------------------------------------------------------

void ofxAwesomiumPlus::BindState() {
    
    JSValue result = web_view->CreateGlobalJavascriptObject(WSLit(_appName.c_str()));
    if (result.IsObject()) {
        // Bind our custom method to it.
        JSObject& app_object = result.ToObject();
        
        // Bind the js function 'changeStaet' to the cpp method 'OnChangeState'
        Bind(app_object,
             WSLit("changeState"),
             JSDelegate(this, &ofxAwesomiumPlus::OnChangeState));
    }
    
    // Bind our method dispatcher to the WebView
    web_view->set_js_method_handler(this);
}

void ofxAwesomiumPlus::Bind(Awesomium::JSObject& object,
                       const Awesomium::WebString& name,
                       JSDelegate callback) {
    // We can't bind methods to local JSObjects
    if (object.type() == Awesomium::kJSObjectType_Local)
        return;
    
    object.SetCustomMethod(name, false);
    
    ObjectMethodKey key(object.remote_id(), name);
    bound_methods_[key] = callback;
}

void ofxAwesomiumPlus::BindWithRetval(Awesomium::JSObject& object,
                                 const Awesomium::WebString& name,
                                 JSDelegateWithRetval callback) {
    // We can't bind methods to local JSObjects
    if (object.type() == Awesomium::kJSObjectType_Local)
        return;
    
    object.SetCustomMethod(name, true);
    
    ObjectMethodKey key(object.remote_id(), name);
    bound_methods_with_retval_[key] = callback;
}

void ofxAwesomiumPlus::OnMethodCall(Awesomium::WebView* caller,
                               unsigned int remote_object_id,
                               const Awesomium::WebString& method_name,
                               const Awesomium::JSArray& args) {
    ofLogNotice("On method call...");
    // Find the method that matches the object id + method name
    std::map<ObjectMethodKey, JSDelegate>::iterator i =
    bound_methods_.find(ObjectMethodKey(remote_object_id, method_name));
    
    // Call the method
    if (i != bound_methods_.end())
        i->second(caller, args);
}

Awesomium::JSValue ofxAwesomiumPlus::OnMethodCallWithReturnValue(Awesomium::WebView* caller,
                                                            unsigned int remote_object_id,
                                                            const Awesomium::WebString& method_name,
                                                            const Awesomium::JSArray& args) {
    // Find the method that matches the object id + method name
    std::map<ObjectMethodKey, JSDelegateWithRetval>::iterator i =
    bound_methods_with_retval_.find(ObjectMethodKey(remote_object_id, method_name));
    
    // Call the method
    if (i != bound_methods_with_retval_.end())
        return i->second(caller, args);
    
    return Awesomium::JSValue::Undefined();
}


// ----------------------------------------------------------------
//  _       __     __    ______
// | |     / /__  / /_  / ____/___  ________
// | | /| / / _ \/ __ \/ /   / __ \/ ___/ _ \
// | |/ |/ /  __/ /_/ / /___/ /_/ / /  /  __/
// |__/|__/\___/_.___/\____/\____/_/   \___/
// ----------------------------------------------------------------

bool ofxAwesomiumPlus::bCoreInited;
WebCore* ofxAwesomiumPlus::core;
WebSession* ofxAwesomiumPlus::session;

// ----------------------------------------------------------------
void ofxAwesomiumPlus::initCore(string logsPath, string sessionPath, bool debug) {
    WebConfig config;
    config.log_path = WSLit(logsPath.c_str());
    config.log_level = kLogLevel_Verbose; //kLogLevel_Normal;
    if (debug) {    // Enable inspector; don't forget to put 'inspector.pak' next to your 'Awesomium.framework'
        config.remote_debugging_host = Awesomium::WSLit("127.0.0.1");
        config.remote_debugging_port = 42424;
    }
    core = WebCore::Initialize(config);
    
    WebPreferences prefs;
    prefs.enable_plugins = true;
    prefs.enable_smooth_scrolling = true;
    
    session = core->CreateWebSession(WSLit(sessionPath.c_str()), prefs);
    
    bCoreInited = true;
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::updateCore() {
    core->Update();
}

// ----------------------------------------------------------------
void ofxAwesomiumPlus::shutdownCore() {
    WebCore::Shutdown();
}