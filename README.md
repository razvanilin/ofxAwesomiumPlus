#ofxAwesomium

[Awesomium](http://www.awesomium.com/) is an off-screen bHTML renderer.  This basically means that you can give it a URL and it will give you an ofTexture of the webpage.  You can also "inject" mouse and keyboard events, making it an interactive browser renderer.  Also supports Flash!

## Installation
1. [Download Awesomium](http://www.awesomium.com/download/)  Currently using v1.7.3
1. Install Awesomium
1. Try out the examples to make sure it works!

## Using the Project Generator on OSX
It kind of sucks that there are so many steps required to add Awesomium to oF, but that's just the way it is right now.  Essentially all you are doing is linking against the Awesomium framework and adding it to the application bundle under Executables. It's the same process covered in [Setting Up on Mac OSX](http://wiki.awesomium.com/getting-started/setting-up-on-macosx.html). If you don't know what that means, just follow the steps below.

1. Generate a project using the Project generator.  Make sure to check off ofxAwesomium in the addons list
1. In the Finder, navigate to /Library/Frameworks (this is where the Awesomium installer put some stuff)
1. Locate Awesomium.framework in /Library/Frameworks
![Locate Framework](http://i.imgur.com/nzLjaQb.png)
1. Drag the entire Awesomium.framework into XCode and drop it into the Project Navigator
![Drag and drop](http://i.imgur.com/BCGRM2d.png)
1. In the dialog that appears, click "Finish"
![Finish](http://i.imgur.com/g08S6uB.png)
1. In the Project Navigator, click on the blue icon at the top.  Then click on "Build Phases"
![Build Phases](http://i.imgur.com/tZxd5Ql.png)
1. Drag "Awesomium.framework" from the Project Navigator and drop it on the section called "Link Binary With Libraries"
1. In the Menu bar, go to Editor > Add Build Phase > Add Copy Files Build Phase
1. In the resulting "Copy Files" build phase, change "Destination" to "Executables", and drag Awesomium.framework (again) from the Project Navigator to where it says "Add Files Here"
