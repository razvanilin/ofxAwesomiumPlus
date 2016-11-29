#ofxAwesomiumPlus

- [ofxAwesomiumPlus](#ofxawesomiumplus)
- [Installation](#installation)
- [Set it up for openFrameworks](#set-it-up-for-openframeworks)
- [Examples](#examples)

[Awesomium](http://www.awesomium.com/) is an off-screen bHTML renderer.  This basically means that you can give it a URL and it will give you an ofTexture of the webpage.  You can also "inject" mouse and keyboard events, making it an interactive browser renderer.  Also supports Flash!

**ofxAwesomiumPlus** is based on [ofxAwesomium](https://github.com/mpcdigital/ofxAwesomium) and adds the following features:

- Better input control
- Method binding
- Window resizing
- Transparency control

**The code is written for OpenFrameworks v0.9.8 so you might need to modify the code slightly if you're using another version**

# Installation
* [Download Awesomium](http://www.awesomium.com/download/)  Currently using v1.7.5
* Install Awesomium
* Try out the examples to make sure it works!
* Integrate it in your OF project using the [platform specific tutorials](http://wiki.awesomium.com/getting-started/)

# Set it up for OpenFrameworks

* `git clone https://github.com/razvanilin/ofxAwesomiumPlus` to the `addons` folder inside your OpenFrameworks folder
* Use the project generator and add the addon to your project
* Look at the example code to see how you can create the web view in your application

# Examples

There are two examples included in the repository:

* **example-basic** - basic OF application loading google in a window
* **example-binding** - using javascript functions to add functionality to the OF application (open camera and draw a string using javascript and HTML buttons) 

# Troubleshoot

If you are getting a DWORD error make sure you include the `ofxAwesomiumPlus.h` after the other headers. Check [this issue](https://github.com/razvanilin/ofxAwesomiumPlus/issues/3#issuecomment-223098358) for more details.
