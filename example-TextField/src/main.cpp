#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
//    ofGLWindowSettings settings;
//    settings.width = 1024;
//    settings.height = 768;
//    settings.windowMode = OF_WINDOW;
//    settings.setGLVersion(4, 1);
//    ofCreateWindow(settings);

	//ofSetupOpenGL(1024, 868, OF_WINDOW);			// <-------- setup the GL context

	//ofGLWindowSettings settings;
	ofGLFWWindowSettings settings;
	settings.setSize(1024, 868);
	//settings.setGLVersion(2, 1); // GL2
	//settings.setGLVersion(3, 2); // GL3
	settings.setGLVersion(4, 6); // GL4
	//settings.redBits = 8;
	//settings.greenBits = 8;
	//settings.blueBits = 8;
	//settings.alphaBits = 8;
	//settings.depthBits = 24;
	settings.stencilBits = 8;
	//settings.numSamples = 1;
	ofCreateWindow(settings);

	ofLog() << "Vendor     : " << glGetString(GL_VENDOR);
	ofLog() << "GPU        : " << glGetString(GL_RENDERER);
	ofLog() << "OpenGL ver : " << glGetString(GL_VERSION);
	ofLog() << "GLSL ver   : " << glGetString(GL_SHADING_LANGUAGE_VERSION);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
