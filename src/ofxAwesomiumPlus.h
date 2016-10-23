// ofxAwesomiumPlus.h
//
// ofxAwesomium: Created by jeff-cr on 11/6/13.
// ofxAwesomiumPlus: created by razvanilin 15/10/15
//

#pragma once
#include "ofMain.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebViewListener.h>
#include <map>
#include "js_delegate.h"

using namespace Awesomium;

class ofxAwesomiumPlus : public ofBaseDraws, JSMethodHandler {
    
public:
    
    class Listener {
    public:
        virtual ~Listener() {}
        
        // Event is fired when app (and WebCore) have been loaded.
        virtual void OnLoaded() = 0;
        
        // Event is fired for each iteration of the Run loop.
        virtual void OnUpdate() = 0;
        
        // Event is fired when the app is shutting down.
        virtual void OnShutdown() = 0;
    };
    
    class MyViewListender : public WebViewListener::View {
        
        void OnChangeTitle(Awesomium::WebView* caller,
                           const Awesomium::WebString& title) {};
        
        void OnChangeAddressBar(Awesomium::WebView* caller,
                                const Awesomium::WebURL& url) {}
        
        void OnChangeTooltip(Awesomium::WebView* caller,
                             const Awesomium::WebString& tooltip) {};
        
        void OnChangeTargetURL(Awesomium::WebView* caller,
                               const Awesomium::WebURL& url) {};
        
        void OnChangeCursor(Awesomium::WebView* caller,
                            Awesomium::Cursor cursor) {};
        
        void OnChangeFocus(Awesomium::WebView* caller,
                           Awesomium::FocusedElementType focused_type) {};
        
        void OnShowCreatedWebView(Awesomium::WebView* caller,
                                  Awesomium::WebView* new_view,
                                  const Awesomium::WebURL& opener_url,
                                  const Awesomium::WebURL& target_url,
                                  const Awesomium::Rect& initial_pos,
                                  bool is_popup){};
        
        void OnAddConsoleMessage(Awesomium::WebView* caller,
                                 const Awesomium::WebString& message,
                                 int line_number,
                                 const Awesomium::WebString& source) {
            
            cout << "Awesomium Console: " << source << ":" << line_number << ": " << message << endl;
        }
    };
    
    typedef std::pair<int, Awesomium::WebString> ObjectMethodKey;
    typedef std::map<ObjectMethodKey, JSDelegate> BoundMethodMap;
    typedef std::map<ObjectMethodKey, JSDelegateWithRetval> BoundMethodWithRetvalMap;
    
    //ofxAwesomiumPlus();
    ~ofxAwesomiumPlus();
    void setup(int width, int height, string appName, bool debug=false);
    void loadURL(string url);
    void reload(bool ignore_cache);
    bool update();
    string getTitle();
    bool getIsLoading();
    JSValue doJavaScript(string js);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseScrolled(float x, float y);
	ofImage getFrame();
    
    void windowResized(int w, int h);
    
    string getState();
    void setScrollSpeed(int modifier);
    void setTransparent(bool flag);
	void setAutomaticResize(bool flag);
	bool isAutomaticResize();
    
    // begin ofBaseDraws
    void draw(float x, float y) const;
    void draw(float x, float y, float w, float h) const;
    void draw(const ofPoint & point) {
        draw(point.x, point.y);
    }
    void draw(const ofRectangle & rect) {
        draw(rect.x, rect.y, rect.width, rect.height);
    }
    void draw(const ofPoint & point, float w, float h) {
        draw(point.x, point.y, w, h);
    }
    float getHeight() const;
    float getWidth() const;
    // end ofBaseDraws
    
    ofImage frame;
    
    static void initCore(string logsPath, string sessionPath, bool debug=false);
    static void updateCore();
    static void shutdownCore();
    
    // Method Binding
    void Bind(Awesomium::JSObject& object,
              const Awesomium::WebString& name,
              JSDelegate callback);
    
    void BindWithRetval(Awesomium::JSObject& object,
                        const Awesomium::WebString& name,
                        JSDelegateWithRetval callback);
    
    void OnMethodCall(Awesomium::WebView* caller,
                      unsigned int remote_object_id,
                      const Awesomium::WebString& method_name,
                      const Awesomium::JSArray& args);
    
    Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView* caller,
                                                   unsigned int remote_object_id,
                                                   const Awesomium::WebString& method_name,
                                                   const Awesomium::JSArray& args);
    
    void set_listener(Listener* listener) { _listener = listener; }
    
    // This is a custom event
    void BindState();
    
    void OnChangeState(WebView* caller, const JSArray& args) {
        // extract the string from the args
        _state = Awesomium::ToString(args[0].ToString());
    }
    // ---------------------
    
protected:
    
    BoundMethodMap bound_methods_;
    BoundMethodWithRetvalMap bound_methods_with_retval_;
    
    WebView* web_view;
    Listener* _listener;
    
    string _appName;
    BitmapSurface* surface;
    
    static bool bCoreInited;
    static WebCore* core;
    static WebSession* session;
    
    string _state;
    int _scrollModifier;

	bool _resizable;
};
