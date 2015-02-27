# All variables and this file are optional, if they are not present the PG and the
# makefiles will try to parse the correct values from the file system.
#
# Variables that specify exclusions can use % as a wildcard to specify that anything in
# that position will match. A partial path can also be specified to, for example, exclude
# a whole folder from the parsed paths from the file system
#
# Variables can be specified using = or +=
# = will clear the contents of that variable both specified from the file or the ones parsed
# from the file system
# += will add the values to the previous ones in the file or the ones parsed from the file 
# system
# 
# The PG can be used to detect errors in this file, just create a new project with this addon 
# and the PG will write to the console the kind of error and in which line it is

meta:
	ADDON_NAME = ofxAwesomium
	ADDON_DESCRIPTION = Awesomium wrapper for openFrameworks
	ADDON_AUTHOR = Jeff Crouse
	ADDON_TAGS = "HTML renderer"
	ADDON_URL = https://github.com/mpcdigital/ofxAwesomium

vs:
	# AWE_DIR variable should be added by the Awesomium SDK installer on Windows
	ADDON_INCLUDES += $(AWE_DIR)/include
	ADDON_LIBS += $(AWE_DIR)/build/lib/awesomium.lib

win_cb:
	# AWE_DIR variable should be added by the Awesomium SDK installer on Windows
	ADDON_INCLUDES += $(AWE_DIR)/include
	ADDON_LIBS += $(AWE_DIR)/build/lib/awesomium.lib

# For other platforms, you will have to add the include directories and libraries manually (see README.md)
