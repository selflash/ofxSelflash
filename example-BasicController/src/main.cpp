#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofLogToConsole();

	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	ofGLFWWindowSettings settings;
	settings.setSize(1024, 768);
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

    cout << "Vendor     : " << glGetString(GL_VENDOR) << '\n';
    cout << "GPU        : " << glGetString(GL_RENDERER) << '\n';
    cout << "OpenGL ver : " << glGetString(GL_VERSION) << '\n';
    cout << "GLSL ver   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
